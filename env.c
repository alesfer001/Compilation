#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "env.h"

struct elm* create_elm(const char *str, void *data, struct type *elm_type, struct elm *next){
  struct elm* new_elm = malloc(sizeof(struct elm));
  if(str){
    new_elm->str = malloc(sizeof(str));
    strcpy(new_elm->str, str);
  }
  new_elm->data = malloc(sizeof(data));
  new_elm->elm_type = malloc(sizeof(struct type));
  new_elm->next = malloc(sizeof(struct elm));
  new_elm->data = data;
  new_elm->elm_type = elm_type;
  new_elm->next = next;

  return new_elm;
}

struct env* create_env(){
  struct env* new_env = malloc(sizeof(struct env));

  return new_env;
}

void add_env(struct env *my_env, char *str, void *data, struct type *elm_type){
  struct elm* new_elm = malloc(sizeof(struct elm));
  if(str){
    new_elm->str = malloc(sizeof(str));
    strcpy(new_elm->str, str);
  }
  new_elm->data = malloc(sizeof(data));
  new_elm->elm_type = malloc(sizeof(struct type));
  new_elm->next = malloc(sizeof(struct elm));
  new_elm->data = data;
  new_elm->elm_type = elm_type;

  if(!my_env->first){
    my_env->first = malloc(sizeof(struct elm));
    my_env->first = new_elm;
  }
  else{
    struct elm* current = my_env->first;
    struct elm* next = current->next;
    while(next){
      current = current->next;
      next = current->next;
    }
    current->next = malloc(sizeof(struct elm));
    current->next = new_elm;
  }
}

struct elm* find_env(struct env *my_env, char* str){
  struct elm* my_elm = my_env->first;
  if(my_elm){
    while(my_elm){
      if(strcmp(my_elm->str, str) == 0){
        return my_elm;
      }
      my_elm = my_elm->next;
    }
  }
  return NULL;
}

void destroy_elm(struct elm* my_elm){

}
void destroy_env(struct env* my_env){
  
}
