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

struct type{
  Nature type_nature;
  struct range type_range;
  struct node *right;
  struct node *left;
};

struct range{
  int min;
  int max;
};

#endif
