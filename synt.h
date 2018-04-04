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

struct stm{
  enum stmNature nature;
  struct node *variable;
  struct exp *expression;
  struct stm *statement;
  struct stm *elsestm;
};

struct exp{
  enum expNature nature;
  struct exp *alpha;
  struct exp *beta;
};

#endif
