#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stddef.h>

#ifndef USE_MUTEX
    #define USE_MUTEX 0
#endif

#ifndef MALLOC_DEBUG
    #define MALLOC_DEBUG 1
#endif

//-------- Strategies ---------
#ifdef FIRST_FIT
    #define ALLOC_STRATEGY
    #define FITTING
#endif

#ifdef WORST_FIT
    #define ALLOC_STRATEGY
    #define FITTING
#endif

#ifdef BEST_FIT
    #define ALLOC_STRATEGY
    #define FITTING
#endif

#ifndef ALLOC_STRATEGY
    #define ALLOC_STRATEGY
    #define FIRST_FIT
    #define FITTING
#endif
//------------------------------

#define ALIGN_LOG 3
#define SBRK_AL_LOG 12

#define AA (1 << ALIGN_LOG)
#define SBRKA (1 << SBRK_AL_LOG)

#define sbrk_align(s) (((((s) - 1) >> SBRK_AL_LOG) << SBRK_AL_LOG) + SBRKA)
#define alloc_align(s) (((((s) - 1) >> ALIGN_LOG) << ALIGN_LOG) + AA)

#endif

