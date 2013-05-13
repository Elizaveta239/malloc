#include "config.h"
#include "debug.h"

#ifdef FITTING
    #include "fit_malloc.h"
#endif

#ifdef COMPACTING
    #include "selfcompact.h"
#endif

#ifndef MAL_STAT
    #include "malloc_st.h"
#endif

#ifndef MY_MAL_STAT
    #include "my_malloc_st.h"
    #include "time_st.h"
    long time_st;
#endif

struct mallinfo mallinfo() {
    return __mallinfo();
}

struct myinfo myinfo() {
    return __myinfo();
}

void *malloc(size_t size)
{
    MDEBUG("Allocate %d byte\n", size);
    time_start();
    void* ans = __malloc(size);
    time_st = time_stop();
    MYSTAT();
    return ans;
}

void free(void *ptr)
{
    if (!ptr)
        return;
    MDEBUG("free %p\n", ptr);
    /*MSTAT();
    MYSTAT();*/
    time_start();
    __free(ptr);
    time_st = time_stop();
    MYSTAT();

}

void *calloc(size_t nmemb, size_t lsize)
{
    time_start();
    void* result;
    size_t size = nmemb * lsize;
    if (nmemb && (size / nmemb) != lsize)
    {
        time_st = time_stop();
        MYSTAT();
        return NULL;
    }
    if ((result = __malloc(size)) != NULL) {
        memset(result, 0, size);
    }
    time_st = time_stop();
    MYSTAT();
    return result;
}

void *realloc(void *ptr, size_t size)
{
    time_start();
    if (!size)
    { 
        __free(ptr);
        void* ans = __malloc(size);
        time_st = time_stop();
        MYSTAT();
        return  ans;
    }
    if (!ptr)
    {
        void* ans = __malloc(size);
        time_st = time_stop();
        MYSTAT();
        return  ans;
    }
    __free(ptr);
    void* ans = __malloc(size);
    time_st = time_stop();
    MYSTAT();
    return  ans;
}
