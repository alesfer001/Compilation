#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "synt.h"

int main(){

  return 0;
}

struct stm* create_assignement(struct stm* left, struct stm* right){
  struct stm *new_stm = create_stm(Assignment, NULL, left, right);
  return new_stm;
}
struct stm* create_if(struct stm* condition, struct stm* thenstm, struct stm* elsestm){
  struct stm *thenelsestm = create_stm(ThenElse, NULL, thenstm, elsestm);
  struct stm *new_stm = create_stm(If, NULL, condition, thenelsestm);
  return new_stm;
}
struct stm* create_while(struct stm* condition, struct stm* dostm){
  struct stm *new_stm = create_stm(While, NULL, condition, dostm);
  return new_stm;
}
struct stm* create_procedure(struct elm* function, struct stm* proc){
  struct stm *new_stm = create_stm(Procedure, function, proc, NULL);
  return new_stm;
}
struct stm* create_return(struct stm* returnstm){
  struct stm *new_stm = create_stm(Return, NULL, returnstm, NULL);
  return new_stm;
}
struct stm* create_not(struct stm* my_stm){
  struct stm *new_stm = create_stm(Not, NULL, my_stm, NULL);
  return new_stm;
}
struct stm* create_new(struct stm* my_stm){
  struct stm *new_stm = create_stm(New, NULL, my_stm, NULL);
  return new_stm;
}
struct stm* create_dispose(struct stm* my_stm){
  struct stm *new_stm = create_stm(Dispose, NULL, my_stm, NULL);
  return new_stm;
}
struct stm* create_variable(struct elm* my_elm){
  struct stm *new_stm = create_stm(Variable, my_elm, NULL, NULL);
  return new_stm;
}
struct stm* create_literal(struct type* literal_type, void* data){
  struct elm* literal_elm = create_elm(NULL, data, literal_type, NULL);
  struct stm *new_stm = create_stm(Literal, literal_elm, NULL, NULL);
  return new_stm;
}
struct stm* create_operation(enum stmNature nature, struct stm* left, struct stm* right){
  struct stm *new_stm = create_stm(nature, NULL, left, right);
  return new_stm;
}

struct stm* create_stm(enum stmNature nature, struct elm *element, struct stm *left, struct stm *right){
  struct stm* new_stm = malloc(sizeof(struct stm));
  new_stm->nature = nature;

  switch(nature){
    case Assignment:
    case If:
    case ThenElse:
    case While:
      new_stm->left = malloc(sizeof(struct stm));
      new_stm->right = malloc(sizeof(struct stm));
      new_stm->left = left;
      new_stm->right = right;
      break;
    case Procedure:
      new_stm->stm_type = malloc(sizeof(struct type));
      new_stm->element = malloc(sizeof(struct elm));
      new_stm->left = malloc(sizeof(struct stm));
      new_stm->element = element;
      new_stm->left = left;
      break;
    case Return:
    case Not:
      new_stm->stm_type = malloc(sizeof(struct type));
      new_stm->left = malloc(sizeof(struct stm));
      new_stm->left = left;
      break;
    case New:
    case Dispose:
      new_stm->left = malloc(sizeof(struct stm));
      new_stm->left = left;
      break;
    case Variable:
    case Literal:
      new_stm->stm_type = malloc(sizeof(struct type));
      new_stm->element = malloc(sizeof(struct elm));
      new_stm->stm_type = element->elm_type;
      new_stm->element = element;
      break;
    case Plus:
    case Mult:
    case Minus:
    case Divide:
    case Or:
    case And:
    case Inf:
    case Infeq:
    case Sup:
    case Supeq:
    case Eq:
    case Noteq:
      new_stm->stm_type = malloc(sizeof(struct type));
      new_stm->left = malloc(sizeof(struct stm));
      new_stm->right = malloc(sizeof(struct stm));
      new_stm->left = left;
      new_stm->right = right;
      break;
  }

  return new_stm;
}

void print_stm(struct stm my_stm){
  switch(my_stm.nature){
    case Assignment:
      print_stm(*my_stm.left);
      printf(" := ");
      print_stm(*my_stm.right);
      printf(";");
      break;
    case If:
      printf("if(");
      print_stm(*my_stm.left);
      printf("){\n");
      print_stm(*my_stm.right);
      printf("\n}");
      break;
    case ThenElse:
      print_stm(*my_stm.left);
      printf("}\nelse{\n");
      print_stm(*my_stm.right);
      printf("\n}");
      break;
    case While:
      printf("while(");
      print_stm(*my_stm.left);
      printf("){\n");
      print_stm(*my_stm.right);
      printf("\n}");
      break;
    case Procedure:
      break;
    case Return:
      printf("return ");
      print_stm(*my_stm.left);
      printf(";");
      break;
    case Not:
      printf("!");
      print_stm(*my_stm.left);
      break;
    case New:
      printf("new(");
      print_stm(*my_stm.left);
      printf(");");
      break;
    case Dispose:
      printf("dispose(");
      print_stm(*my_stm.left);
      printf(");");
      break;
    case Variable:
    case Literal:
      break;
    case Plus:
      print_stm(*my_stm.left);
      printf(" + ");
      print_stm(*my_stm.right);
      break;
    case Mult:
      print_stm(*my_stm.left);
      printf(" * ");
      print_stm(*my_stm.right);
      break;
    case Minus:
      print_stm(*my_stm.left);
      printf(" - ");
      print_stm(*my_stm.right);
      break;
    case Divide:
      print_stm(*my_stm.left);
      printf(" / ");
      print_stm(*my_stm.right);
      break;
    case Or:
      print_stm(*my_stm.left);
      printf(" || ");
      print_stm(*my_stm.right);
      break;
    case And:
      print_stm(*my_stm.left);
      printf(" && ");
      print_stm(*my_stm.right);
      break;
    case Inf:
      print_stm(*my_stm.left);
      printf(" < ");
      print_stm(*my_stm.right);
      break;
    case Infeq:
      print_stm(*my_stm.left);
      printf(" <= ");
      print_stm(*my_stm.right);
      break;
    case Sup:
      print_stm(*my_stm.left);
      printf(" > ");
      print_stm(*my_stm.right);
      break;
    case Supeq:
      print_stm(*my_stm.left);
      printf(" >= ");
      print_stm(*my_stm.right);
      break;
    case Eq:
      print_stm(*my_stm.left);
      printf(" = ");
      print_stm(*my_stm.right);
      break;
    case Noteq:
      print_stm(*my_stm.left);
      printf(" != ");
      print_stm(*my_stm.right);
      break;
  }
}

void destroy_stm(struct stm *my_stm){

}
