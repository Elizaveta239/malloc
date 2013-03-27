#include <assert.h>

#include "config.h"
#include "debug.h"
#include "heap.h"
#include "morecore.h"
#include "fit_malloc.h"


#if USE_MUTEX == 1
    #include <pthread.h>
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    #define heap_lock(lock) pthread_mutex_lock(&lock)
    #define heap_unlock(lock) pthread_mutex_unlock(&lock)
#else
    #define heap_lock(lock) (void) 0
    #define heap_unlock(lock) (void) 0
#endif

header_p heap = NULL;
header_p first_block = NULL;
header_p last_block = NULL;

void init_heap()
{
#if USE_MUTEX == 666
    pthread_mutexattr_t mta;
    pthread_mutexattr_init(&mta);
    pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&lock, &mta);
    pthread_mutexattr_destroy(&mta);
#endif
}

void print_heap_dump()
{
    MDEBUG("========= HEAP DUMP ============\n");
    header_p curr = heap;
    header_p last = NULL;
    for (; curr != last; curr = curr->next)
    {
        MDEBUG("%p-%p %c %4db at %p-%p\n", curr, (void*)(footer(curr)) + FOOTER_SIZE - 1,
        (is_free(curr)) ? 'f' : 'u', block_size(curr), payload(curr), ((void*)footer(curr)) - 1);       
    }
    MDEBUG("================================\n");
}

void split_block(header_p h, size_t size)
{
    header_p new_block = payload(h) + size + FOOTER_SIZE;
    set_size(new_block, block_size(h) - size - META_SIZE);
    set_size(h, size);
    insert_block(&heap, new_block, h, h->next);
    set_free(new_block);
    if (last_block == h)
        last_block = new_block;
    MDEBUG("split block %p to %p(%d) and %p(%d)\n", h, h, size, new_block, block_size(new_block)); 
}

void merge_block(header_p h)
{
    if (!is_free(h))
        return;
    if (h != last_block)
    {
        header_p next = ((void *) h) + block_size(h) + META_SIZE;
        MDEBUG("merge: next - %p\n", next);
        if (is_free(next)) 
        {
            h->next = next->next;
            set_size(h, block_size(h) + block_size(next) + META_SIZE);
            set_free(h);
            if (next == last_block)
                last_block = h;
            MDEBUG("merge blocks %p and %p\n", h, next);
        }
    }
    if (h != first_block)
    {
        footer_p prev_foot = ((void *) h) - FOOTER_SIZE;
        header_p prev = ((void*) prev_foot) - prev_foot->size - HEADER_SIZE;
        MDEBUG("merge: prev - %p\n", prev);
        if (is_free(prev))
        {
            prev->next = h->next;
            set_size(prev, block_size(prev) + block_size(h) + META_SIZE);
            set_free(prev);
            if (h == last_block)
                last_block = prev;
            MDEBUG("merge blocks %p and %p\n", prev, h);
        }
    }
}

header_p find_fit_block(size_t size)
{
    header_p curr = heap;
    header_p last = NULL;
    int find_one = 0;
    header_p our_choose = NULL;
    int fitting_param;
    while (curr != NULL)
    {
        if (is_free(curr) && block_size(curr) >= size)
        {
            #ifdef BEST_FIT
            if (!find_one || fitting_param > block_size(curr))
            #endif
            #ifdef WORST_FIT
            if (!find_one || fitting_param < block_size(curr))
            #endif
            {
                our_choose = curr;
                fitting_param = block_size(curr);
            }
            #ifdef FIRST_FIT
            break;
            #endif
            find_one = 1; 
        }
        if (curr->next == last && !find_one)
        {
            header_p new_block = morecore(size + META_SIZE);
            last_block = new_block;
            insert_block(&heap, new_block, curr, last);
            if (is_free(curr))
            {
                merge_block(curr);
                continue;
            }
        }
        curr = curr->next;
    }
    return our_choose;
}

void* fit_malloc(size_t size)
{
    MDEBUG("fit_malloc: size= %d\n", size); 
    size_t s = alloc_align(size + META_SIZE);   
    size = alloc_align(size);
    header_p block;
    heap_lock(lock);
    if (heap == NULL)
    {
        init_heap();
        block = morecore(s);
        if (block == NULL)
        {
            heap_unlock(lock);
            return NULL;
        }
        insert_block(&heap, block, NULL, NULL);
        first_block = block;
        last_block = block;
    } else {
        block = find_fit_block(s);
        if (block == NULL) 
        {
            heap_unlock(lock);
            return NULL;
        }
    }

    set_used(block);
    if (block_size(block) > size + META_SIZE)
        split_block(block, size);
    heap_unlock(lock);
    MDEBUG("fit_malloc: returning %p\n", payload(block));
    
    assert(block_size(block) >= size);
    assert(payload(block) >= (void*)first_block);
    assert((void*) footer(block) <= sbrk(0));

    return payload(block);
}

void fit_free(void* ptr)
{
    heap_lock(lock);
   // MDEBUG("fit_free: ptr= %p\n", ptr);
    header_p last = NULL;
    header_p curr = heap;
    for(; curr != last; curr = curr->next)
        if (payload(curr) == ptr)
        {
//            MDEBUG("fit_free: set block %p with size=%d as free\n", curr, block_szie(curr));
            set_free(curr);
            merge_block(curr);
            heap_unlock(lock);
            return;
        }
    MDEBUG("Invalid pointer!!! %p\n", ptr);
    print_heap_dump();
    exit(1);
}

