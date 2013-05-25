#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stddef.h>

#define WORST_FIT

/*#define MAX_HEAP_SIZE 4096*/
#define FIT_DELETE_USED
#define ROUND_ROBIN
#define ALLOW_MERGE

#define ALIGN_LOG 2

#define MALLOC_DEBUG 0
#define MALLOC_STAT 0
#define MY_MALLOC_STAT 1
#include "default.h"
#endif
