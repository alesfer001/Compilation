#ifndef __memory_h__
#define __memory_h__

#include "types.h"
#include "synt.h"

enum env{
  Static,
  Stack,
  Heap
};

struct s_block{
  struct s_block *prev;
  int size;
  struct node *params;
  int nb_params;
  struct node *locals;
  int nb_locals;
  struct node *ret;
};

struct stack{
  struct block *actual;
  int size;
};

struct static_env{
  struct node *nodes;
  int size;
};

struct h_block{
  struct h_block *prev;
  struct h_block *next;
  int frozen;
  int size;
  struct node *data;
};

struct heap{
  struct h_block *head;
  int size;
};

int create_s_block(struct stack *my_stack, struct node* func, struct node *params, int nb_params);
int static_add(struct static_env *my_static_env, struct node *my_node);
int create_h_block(struct heap *my_heap, struct node* data);
int remove_h_block(struct heap *my_heap, struct node* data);
int garbage_collector(struct heap *my_heap);

#endif
