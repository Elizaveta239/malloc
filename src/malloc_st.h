
#ifndef MAL_STAT
#define MAL_STAT

#include "config.h"
#if MALLOC_STAT == 1 
    #include <stdio.h>
	#include "mallinfo.h"
	static inline void show_stat(void) {
  		struct mallinfo stat = mallinfo();
  		double fragm;

  		if (stat.fordblks == 0) {
    			fragm = 100;
  		} else {
    			fragm = ((double)(stat.fordblks - stat.keepcost) * 100) / stat.fordblks;
  		}
  		printf(" %d %3d %3d %3d %3d %3d %3d %7d %7d %7d %.3f\n", stat.arena, stat.ordblks, stat.smblks, stat.hblks,
 stat.hblkhd, stat.usmblks, stat.smblks, stat.uordblks, stat.fordblks, stat.keepcost, fragm);
	}

    #define MSTAT() show_stat()
#else
    #define MSTAT() (void) 0
#endif

#endif

