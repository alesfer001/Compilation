#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "types.h"

struct type *create_tree(struct type *params, int nb_params);
struct type *copy_type(struct type tbc);
void copy_range(struct range tbc, struct range *copy);

int main(){
  struct type* my_empty = create_empty();

  // --------------
  // Creation Tests
  // --------------
  struct type* my_int = create_integer();
  print_type(*my_int);
  printf("\n");

  struct type* my_ptr_int = create_pointer(my_int);
  print_type(*my_ptr_int);
  printf("\n");
  struct type* my_ptr_ptr_int = create_pointer(my_ptr_int);
  print_type(*my_ptr_ptr_int);
  printf("\n");

  struct type* array_int = create_array(my_int, 0, 10);
  print_type(*array_int);
  printf("\n");
  struct type* array_array_int = create_array(array_int, 0, 5);
  print_type(*array_array_int);
  printf("\n");
  struct type* array_ptr_int = create_array(my_ptr_int, 0, 3);
  print_type(*array_ptr_int);
  printf("\n");

  struct type* func;
  struct type parameters[5];
  parameters[0] = *my_int;
  parameters[1] = *my_ptr_int;
  parameters[2] = *array_int;
  parameters[3] = *my_int;
  parameters[4] = *my_int;

  func = create_function(my_empty, NULL, 0);
  print_type(*func);
  printf("\n");
  destroy_type(func);
  func = create_function(my_int, parameters, 1);
  print_type(*func);
  printf("\n");
  destroy_type(func);
  func = create_function(my_int, parameters, 2);
  print_type(*func);
  printf("\n");
  destroy_type(func);
  func = create_function(my_int, parameters, 3);
  print_type(*func);
  printf("\n");
  destroy_type(func);
  func = create_function(my_int, parameters, 4);
  print_type(*func);
  printf("\n");
  destroy_type(func);
  func = create_function(my_int, parameters, 5);
  print_type(*func);
  printf("\n");

  // ----------------
  // Comparison Tests
  // ----------------
  struct type *func2 = create_function(my_empty, NULL, 0);
  struct type *func3 = create_function(my_int, parameters, 4);
  assert(compare_type(*my_int, *my_int));
  assert(compare_type(*my_ptr_int, *my_ptr_int));
  assert(!compare_type(*my_int, *my_ptr_int));
  assert(!compare_type(*my_ptr_int, *my_ptr_ptr_int));
  assert(compare_type(*array_int, *array_int));
  assert(!compare_type(*my_ptr_int, *array_int));
  assert(!compare_type(*array_int, *array_array_int));
  assert(compare_type(*func, *func));
  assert(!compare_type(*array_int, *func));
  assert(!compare_type(*func, *func2));
  assert(!compare_type(*func, *func3));
  printf("--- Comparison tests passed ---\n");

  // ------------
  // Memory Tests
  // ------------
  destroy_type(my_int);
  print_type(*my_ptr_int);
  printf("\n");

  destroy_type(my_empty);
  destroy_type(my_ptr_int);
  destroy_type(my_ptr_ptr_int);
  destroy_type(array_int);
  destroy_type(array_array_int);
  destroy_type(array_ptr_int);
  destroy_type(func);
  destroy_type(func2);
  destroy_type(func3);

  //  Memory Usage :
  //  75 allocs, 75 frees, 3,392 bytes allocated

  return 0;
}


struct type* create_empty(){
  return create_type(empty, NULL, NULL, NULL, NULL, 0);
}
struct type* create_integer(){
  return create_type(integer, NULL, NULL, NULL, NULL, 0);
}
struct type* create_boolean(){
  return create_type(boolean, NULL, NULL, NULL, NULL, 0);
}
struct type* create_character(){
  return create_type(character, NULL, NULL, NULL, NULL, 0);
}
struct type* create_pointer(struct type* pointsto){
  return create_type(pointer, NULL, pointsto, NULL, NULL, 0);
}
struct type* create_array(struct type *arrayof, int min, int max){
  struct range my_range;
  my_range.min = min;
  my_range.max = max;
  return create_type(array, &my_range, arrayof, NULL, NULL, 0);
}
struct type* create_function(struct type *returnf, struct type *params, int nb_params){
  return create_type(function, NULL, NULL, returnf, params, nb_params);
}

struct type* create_type(enum Nature nat, struct range *my_range, struct type *left, struct type *right, struct type *params, int nb_params){
  assert(nb_params >= 0);

  struct type *new_type = malloc(sizeof(struct type));
  new_type->nature = nat;

  switch(nat){
    case empty:
    case integer:
    case boolean:
    case character:
      break;
    case pointer:
      assert(left != NULL);
      new_type->left = copy_type(*left);
      break;
    case array:
      assert(left != NULL);
      new_type->left = copy_type(*left);
      copy_range(*my_range, &new_type->range);
      break;
    case function:
      assert(right != NULL);
      new_type->right = copy_type(*right);
      new_type->left = create_tree(params, nb_params);
      break;
    default:
      printf("Error: Type Nature Unrecognized!\n");
      break;
    }

    return new_type;
}

struct type *create_tree(struct type *params, int nb_params){
  assert(nb_params >= 0);

  struct type *root;

  if(nb_params <= 1){
    if(nb_params == 0){
      root = malloc(sizeof(struct type));
      root->nature = empty;
    }
    else{
      root = copy_type(params[0]);
    }
  }
  else{
    root = malloc(sizeof(struct type));
    if(nb_params == 2){
      root->nature = prod;
      root->left = copy_type(params[0]);
      root->right = copy_type(params[1]);
    }
    else if(nb_params == 3){
      root->nature = prod;
      root->right = copy_type(params[nb_params-1]);
      root->left = create_tree(params, nb_params-1);
    }
    else{
      root->nature = prod;
      root->left = create_tree(params, nb_params/2 + nb_params%2);
      root->right = create_tree(params + nb_params/2 + nb_params%2, nb_params/2);
    }
  }
}

struct type *copy_type(struct type tbc){
  struct type *new_type = malloc(sizeof(struct type));
  new_type->nature = tbc.nature;

  switch(new_type->nature){
    case empty:
    case integer:
    case boolean:
    case character:
      break;
    case pointer:
      new_type->left = copy_type(*tbc.left);
      break;
    case array:
      new_type->left = copy_type(*tbc.left);
      copy_range(tbc.range, &new_type->range);
      break;
    case prod:
      new_type->left = copy_type(*tbc.left);
      new_type->right = copy_type(*tbc.right);
      break;
    default:
      printf("Error: Type Nature Unrecognized!\n");
      break;
    }

    return new_type;
}

void copy_range(struct range tbc, struct range *copy){
  copy->min = tbc.min;
  copy->max = tbc.max;
}

void print_type(struct type my_type){
  switch(my_type.nature){
    case empty:
      printf("Void");
      break;
    case integer:
      printf("Int");
      break;
    case boolean:
      printf("Boolean");
      break;
    case character:
      printf("Character");
      break;
    case pointer:
      printf("Pointer of ");
      print_type(*my_type.left);
      break;
    case array:
      printf("Array of range [%d, %d] of ", my_type.range.min, my_type.range.max);
      print_type(*my_type.left);
      break;
    case prod:
      print_type(*my_type.left);
      printf(", ");
      print_type(*my_type.right);
      break;
    case function:
      printf("Function foo (");
      print_type(*my_type.left);
      printf(") : ");
      print_type(*my_type.right);
      break;
    default:
      printf("Error: Type Nature Unrecognized!\n");
      break;
    }
}

int compare_type(struct type alpha, struct type beta){
  if(alpha.nature != beta.nature){
    return 0;
  }
  else{
    switch(alpha.nature){
      case empty:
      case integer:
      case boolean:
      case character:
        return 1;
      case pointer:
        assert(alpha.left != NULL && beta.left != NULL);
        return compare_type(*alpha.left, *beta.left);
      case array:
        assert(alpha.left != NULL && beta.left != NULL);
        if(alpha.range.min == beta.range.min && alpha.range.max == beta.range.max){
          return compare_type(*alpha.left, *beta.left);
        }
        return 0;
      case prod:
      case function:
        assert(alpha.left != NULL && beta.left != NULL);
        assert(alpha.right != NULL && beta.right != NULL);
        if(compare_type(*alpha.right, *beta.right)){
          return compare_type(*alpha.left, *beta.left);
        }
        return 0;
      default:
        printf("Error: Type Nature Unrecognized!\n");
        return 0;
      }
  }
}

void destroy_type(struct type *my_type){
  assert(my_type != NULL);

  switch(my_type->nature){
    case empty:
    case integer:
    case boolean:
    case character:
      free(my_type);
      break;
    case pointer:
    case array:
      assert(my_type->left != NULL);
      destroy_type(my_type->left);
      free(my_type);
      break;
    case prod:
    case function:
      assert(my_type->left != NULL);
      assert(my_type->right != NULL);
      destroy_type(my_type->left);
      destroy_type(my_type->right);
      free(my_type);
      break;
    default:
      printf("Error: Type Nature Unrecognized!\n");
      break;
    }
}
