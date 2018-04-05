#ifndef __synt_h__
#define __synt_h__

enum stmNature{
  Assignment,
  Test,
  Loop,
  Return,
  New,
  Dispose
};

enum expNature{
  Plus,
  Mult,
  Minus,
  Divide,
  ...
};

struct node{
  struct type node_type;
  int memoffset;
  enum env memenv;
};

struct stm{
  enum stmNature nature;
  struct type *stm_type;
  struct node *variable;
  struct exp *expression;
  struct stm *statement;
  struct stm *elsestm;
};

struct exp{
  enum expNature nature;
  struct type exp_type;
  struct exp *alpha;
  struct exp *beta;
};

struct node* create_node(struct type node_type);

#endif
