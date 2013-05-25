#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define COUNT 10000

struct node {
  int x;
  struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;
int n = 0;

void add_node(int num) {
   if (head == NULL) {
     head = malloc(sizeof(struct node));
     head -> x = num;
     head -> next = NULL;
     tail = head;
   } else {
     struct node *ptr = malloc(sizeof(struct node));
     ptr -> x = num;
     ptr -> next = NULL;
     tail -> next = ptr;
     tail = ptr;
   }
   n++;   
}


void delete_list(void) {
  struct node *ptr = head;
  struct node *ptr_prev = ptr;
  ptr = ptr_prev -> next;  

  while(ptr != NULL) {
     free(ptr_prev);
     ptr_prev = ptr;
     ptr = ptr -> next;
  }
  free(ptr_prev);
  n = 0;
}

void show_list(void) {
  struct node *ptr = head;
  int i = 0;
  /*for (i = 0; i < n - 1; i++) {*/
  while (ptr != NULL) {
     printf("%d ", ptr -> x);
     ptr = ptr -> next;
  }
  /*printf("%d ", ptr -> x);*/
  printf("\n");
}


void sort_list(void) {
  int sorted = 0, i = 0;
  for (sorted = 0; sorted < n; sorted++) {
    struct node *max = head;
    struct node *curnode = head;
    struct node *prev_curnode = curnode;
    struct node *prev_max = max;
    i = 1;
    while (i < n - sorted) {
      /*printf("%d %d i = %d, sorted = %d, n = %d\n", curnode -> x, max -> x, i, sorted, n);*/
      prev_curnode = curnode;
      curnode = curnode -> next;
      if ((curnode -> x) > (max -> x)) {
        prev_max = prev_curnode;
        max = curnode;
      }
      i++;
    }
    if (i != 1) {
    	struct node *new_max = malloc(sizeof(struct node));
    	new_max -> x = max -> x;  
    	new_max -> next = curnode -> next;  
    	curnode -> next = new_max;
   	if (max != head) { 
    	  prev_max -> next = max -> next;
    	  free(max);
        } else {
          struct node *cur = head;
          head = head -> next;
          free(cur);
        }
     }
     /*printf("\nlist:");
     show_list();*/
  }
}


int main(void) {
   int i = 1;
   srand(time(NULL));
   for (i = 0; i < COUNT; i++) {
      int r = rand() % 10000;
      add_node(r);
   }
   /*struct node *ptr = head;*/
   /*show_list();*/
   sort_list();
   /*show_list();*/
   delete_list();

   return 0;
}
