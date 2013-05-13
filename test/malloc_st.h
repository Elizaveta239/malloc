#include <stdlib.h>
#include <malloc.h>


#ifndef MAL_STAT
#define MAL_STAT
static inline void show_stat(void);
static inline void *malloc_st(size_t size);
static inline void free_st(void *ptr);

static inline void show_stat(void) {
  struct mallinfo stat = mallinfo();
  double fragm;

  if (stat.fordblks == 0) {
    fragm = 100;
  } else {
    fragm = ((double)(stat.fordblks - stat.keepcost) * 100) / stat.fordblks;
  }
  printf(" %d %3d %3d %3d %3d %3d %3d %7d %7d %7d %.3f\n", stat.arena, stat.ordblks, stat.smblks, stat.hblks, stat.hblkhd, stat.usmblks,
 stat.smblks, stat.uordblks, stat.fordblks, stat.keepcost, fragm);
}

static inline void *malloc_st(size_t size) {
  void *result = malloc(size); 
  show_stat();
  return result;
}

static inline void free_st(void *ptr) {
  free(ptr);
  show_stat();
  /*return free(ptr);*/
}
#endif
