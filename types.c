#include <stdio.h>
#include <stdlib.h>

#include "types.h"

int main(){

  return 0;
}

struct type* create_type(Nature nat, Nature pointsto, struct range my_range, Nature *params, int nb_params){
  struct type *new_type;
  new_type->type_nature = nat;

  switch(nat){
    case integer:
    case boolean:
    case character:
      break;
    case pointer:
      new_type->pointsto = pointsto;
      break;
    case array:
      new_type->pointsto = pointsto;
      new_type->type_range.min = my_range.min;
      new_type->type_range.max = my_range.max;
      break;
    case function:
      new_type->right = malloc(sizeof(struct node));
      new_type->left = malloc(sizeof(struct node));
  }
  new_type
}

void print_type(struct type my_type);
int compare_type(struct type type_alpha, struct type type_beta);
void destroy_type(struct type *my_type);
