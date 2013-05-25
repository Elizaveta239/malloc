
#ifndef MY_MAL_STAT
#define MY_MAL_STAT

#include "config.h"
#if MY_MALLOC_STAT == 1 
    #include <stdio.h>
    #include "mallinfo.h"
/*int arena;
    int freemem;
    int usdmem;
    int freeblks;
    int usdblks;
    int maxfreeblk;
*/ 

static inline void my_show_stat(void) {
    struct myinfo stat = myinfo();
    double fragm;
    double fullness;
    if (stat.freemem == 0) {
        fragm = 0;
        fullness = 100;
    } else {
    	fragm = ((double)(stat.freemem - stat.maxfreeblk) * 100) / stat.freemem;
        fullness = (1 - (double)stat.freemem / stat.arena) * 100; 
    }
    printf("%d %d %d %d %d %d %.3f %.3f ", stat.arena, stat.freemem, stat.usdmem, stat.freeblks, stat.usdblks,
 stat.maxfreeblk, fragm, fullness);
    /*printf("%.3f\n",  fragm);*/
    /*printf("%d %d %d\n", stat.arena, stat.freemem, stat.maxfreeblk);*/
}

    #define MYSTAT() my_show_stat(); printf("%ld\n", time_st)
#else
    #define MYSTAT() (void) 0
#endif

#endif

