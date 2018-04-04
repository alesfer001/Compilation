#ifndef __types_h__
#define __types_h__

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

struct type* create_empty();
struct type* create_integer();
struct type* create_boolean();
struct type* create_character();
struct type* create_pointer(struct type* pointsto);
struct type* create_array(struct type* arrayof, int min, int max);
struct type* create_function(struct type *returnf, struct type *params, int nb_params);
struct type* create_type(enum Nature nat, struct range *my_range, struct type *left, struct type *right, struct type *params, int nb_params);
void print_type(struct type my_type);
int compare_type(struct type type_alpha, struct type type_beta);
void destroy_type(struct type *my_type);

#endif
