#ifndef __env_h__
#define __env_h__

#include "types.h"

struct env{
  struct elm *first;
};

struct elm{
  char *str;
  void *data;
  struct type *elm_type;
  /*int memoffset;
  enum env memenv;*/
  struct elm *next;
};

struct elm* create_elm(const char *str, void *data, struct type *elm_type, struct elm *next);
struct env* create_env();
void add_env(struct env *my_env, char *str, void *data, struct type *elm_type);
struct elm* find_env(struct env *my_env, char* str);
void destroy_elm(struct elm* my_elm);
void destroy_env(struct env* my_env);

#endif
