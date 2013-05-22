#include <stdio.h>
#include <malloc.h>
#include <sys/times.h>

int main(void) {
  //struct mallinfo stat;
  printf("Выделение памяти:\n");
  int i;
  int n = 10;
  int *a[n];
  for (i = 0; i < n; i++) {
    a[i] = malloc(sizeof(int));
    //show_stat();
  }  
  printf("Очистка памяти:\n");
  for (i = n - 1; i >= 0; i--) {
    free(a[i]);
//    print_heap_dump();
//    show_stat();
  }
  /*printf("%ld", CLOCKS_PER_SEC);*/
  return 0;
}



