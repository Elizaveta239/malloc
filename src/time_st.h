#include <sys/times.h>  

/*struct timeval tv1, tv2, dtv;*/
  static clock_t st_time;
  static clock_t en_time;
  static struct tms st_cpu;
  static struct tms en_cpu;

  void time_start() {
    st_time = times(&st_cpu);
  }

  unsigned long time_stop() {
    /*int i = 0, k = 0;
    for(i = 0; i < 100000000; i++) {
    	k = k + i;
    }
    printf("k = %d\n", k);*/
    en_time = times(&en_cpu);
    /*
    dtv.tv_sec = tv2.tv_sec - tv1.tv_sec;
    dtv.tv_usec = tv2.tv_usec - tv1.tv_usec;
    if(dtv.tv_usec < 0) {
      dtv.tv_sec--;
      dtv.tv_usec += 1000000;
    }*/
    /*printf("%ld\n", st_time);
    printf("%ld\n", en_time);
    printf("%ld\n", st_cpu.tms_utime);
    printf("%ld\n", en_cpu.tms_utime);*/
    return (unsigned long)(en_cpu.tms_utime - st_cpu.tms_utime);
  }
