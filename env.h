#ifndef __env_h__
#define __env_h__

struct env{
  struct elm *first;
}

struct elm{
  char *str;
  void *data;
  struct env *next;
}

struct env *create_env();
int add_env(struct env *my_env, char* str, void* data);
void* find_env(struct env *my_env, char* str);

#endif
