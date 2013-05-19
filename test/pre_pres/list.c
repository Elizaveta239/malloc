#include <stdio.h>
#include <stdlib.h>

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
  for (i = 0; i < n; i++) {
     printf("%d ", ptr -> x);
     ptr = ptr -> next;
  }
  printf("\n");
}


int main(void) {
   int i = 1;
   add_node(1);
   add_node(2);
   struct node *ptr = head;
   show_list();
   delete_list();   

   return 0;
}
