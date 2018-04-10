#ifndef __synt_h__
#define __synt_h__

#include "types.h"
#include "env.h"

enum stmNature{
  Assignment,
  Procedure,
  If,
  ThenElse,
  While,
  Return,
  New,
  Dispose,
  Variable,
  Literal,
  Plus,
  Mult,
  Minus,
  Divide,
  Or,
  And,
  Not,
  Inf,
  Infeq,
  Sup,
  Supeq,
  Eq,
  Noteq
};
/*
struct node{
  //struct type node_type;
  int memoffset;
  enum env memenv;
};
*/
struct stm{
  enum stmNature nature;
  struct type *stm_type;
  struct elm *element;
  struct stm *left;
  struct stm *right;
};

struct stm* create_assignement(struct stm* left, struct stm* right);
struct stm* create_if(struct stm* condition, struct stm* thenstm, struct stm* elsestm);
struct stm* create_while(struct stm* condition, struct stm* dostm);
struct stm* create_procedure(struct elm* function, struct stm* proc);
struct stm* create_return(struct stm* returnstm);
struct stm* create_not(struct stm* my_stm);
struct stm* create_new(struct stm* my_stm);
struct stm* create_dispose(struct stm* my_stm);
struct stm* create_variable(struct elm* my_elm);
struct stm* create_literal(struct type* literal_type, void* data);
struct stm* create_operation(enum stmNature nature, struct stm* left, struct stm* right);

struct stm* create_stm(enum stmNature nature, struct elm *element, struct stm *left, struct stm *right);
void print_stm(struct stm my_stm);
void destroy_stm(struct stm *my_stm);

#endif
