#ifndef __types_h__
#define __types_h__

struct type;

enum Nature{
  empty,
  integer,
  boolean,
  character,
  pointer,
  array,
  function,
  prod
};

struct range{
  int min;
  int max;
};

struct type{
  enum Nature nature;
  struct range range;
  struct type *left;
  struct type *right;
};

struct type* create_type(enum Nature nat, struct range *my_range, struct type *left, struct type *right, struct type *params, int nb_params);
void print_type(struct type my_type);
int compare_type(struct type type_alpha, struct type type_beta);
void destroy_type(struct type *my_type);

#endif
