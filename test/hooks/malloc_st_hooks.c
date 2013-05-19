
#ifndef MAL_STAT
#define MAL_STAT

#include <stdlib.h>
#include <malloc.h>
#include "time_st.h"

static inline void show_stat(void);

/* Prototypes for our hooks.  */
static inline void my_init_hook (void);
static inline void *my_malloc_hook (size_t, const void *);
static inline void my_free_hook (void*, const void *);

static inline void *(*old_malloc_hook) (size_t, const void *);
static inline void *(*old_free_hook) (void*, const void *);
static inline long time_st;

/* Override initializing hook from the C library. */
inline void (*__MALLOC_HOOK_VOLATILE __malloc_initialize_hook) (void) = my_init_hook;

static inline void show_stat(void) {
  struct mallinfo stat = mallinfo();
  double fragm;
  double fullness;
  /*if (stat.fordblks == 0) {
    fragm = 100;
  } else {
    fragm = ((double)(stat.fordblks - stat.keepcost) * 100) / stat.fordblks;
  }*/
  
  if (stat.fordblks == 0) {
    fullness = 0;
  } else {
    fullness = (1 - (double) stat.fordblks / stat.arena) * 100;
  }

  printf(" %d %3d %3d %3d %3d %3d %3d %7d %7d %7d %7d %7.3f\n", stat.arena, stat.ordblks, stat.smblks, stat.hblks, stat.hblkhd, stat.usmblks,
 stat.smblks, stat.uordblks, stat.fordblks, stat.keepcost, time_st, fullness);
}



static inline void
my_init_hook (void) {
    old_malloc_hook = __malloc_hook;
    old_free_hook = __free_hook;
    __malloc_hook = my_malloc_hook;
    __free_hook = my_free_hook;
}
     
static inline void *my_malloc_hook (size_t size, const void *caller) {
    void *result;
    /* Restore all old hooks */
    __malloc_hook = old_malloc_hook;
    __free_hook = old_free_hook;
    /* Call recursively */
    time_start();
    result = malloc (size);
    time_st = time_stop();
    /* Save underlying hooks */
    old_malloc_hook = __malloc_hook;
    old_free_hook = __free_hook;
    /* printf might call malloc, so protect it too. */
    /*printf ("malloc (%u) returns %p\n", (unsigned int) size, result);*/
    show_stat();
    /* Restore our own hooks */
    __malloc_hook = my_malloc_hook;
    __free_hook = my_free_hook;
    return result;
}

static inline void my_free_hook (void *ptr, const void *caller) {
    /* Restore all old hooks */
    __malloc_hook = old_malloc_hook;
    __free_hook = old_free_hook;
    /* Call recursively */
    time_start();
    free (ptr);
    time_st = time_stop();
    /* Save underlying hooks */
    old_malloc_hook = __malloc_hook;
    old_free_hook = __free_hook;
    /* printf might call free, so protect it too. */
    /*printf ("freed pointer %p\n", ptr);*/
    show_stat();
    /* Restore our own hooks */
    __malloc_hook = my_malloc_hook;
    __free_hook = my_free_hook;
}

     

#endif
