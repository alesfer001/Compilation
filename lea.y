%{
#include  <stdio.h>
extern int yylex();
int yyerror(char *s);
%}

%token '!' '(' ')' '*' '+' ',' '-' '/' ':' ';' '<' '=' '>' '[' ']' '^' 
TOKEN_AFF TOKEN_AND TOKEN_ARRAY TOKEN_BEGIN TOKEN_CHARACTER TOKEN_DISPOSE TOKEN_DO TOKEN_DOTDOT TOKEN_ELSE TOKEN_END TOKEN_FALSE TOKEN_FUNCTION TOKEN_GE TOKEN_IF TOKEN_LE TOKEN_NEW TOKEN_NE TOKEN_NULL TOKEN_OF TOKEN_OR TOKEN_PRINT TOKEN_PRINTLN TOKEN_PROCEDURE TOKEN_THEN TOKEN_TYPE TOKEN_BOOLEAN TOKEN_INTEGER TOKEN_RETURN TOKEN_TRUE TOKEN_VAR TOKEN_WHILE IDENTIFIER CHARACTER INTEGER


%nonassoc TOKEN_THEN
%nonassoc TOKEN_ELSE



%left TOKEN_OR
%left  TOKEN_AND
%nonassoc '!'

%nonassoc '<' TOKEN_LE '>' TOKEN_GE '=' TOKEN_NE


%left '+' '-'
%left '*' '/'
%nonassoc UNMINUS


%%

program:
 type_declaration_part variable_declaration_part  procedure_and_function_definition_part  TOKEN_BEGIN  statement_part TOKEN_END
 ;

type_declaration_part:
 TOKEN_TYPE type_declaration_list
 | /* empty */
 ;

type_declaration_list:
 type_declaration_list type_declaration
 | type_declaration
 ;


type_declaration:
 IDENTIFIER  '=' type ';'
 ;

variable_declaration_part:
 TOKEN_VAR variable_declaration_list
 | /* empty */
 ;

variable_declaration_list:
 variable_declaration_list variable_declaration
 | variable_declaration
 ;

variable_declaration:
 identifier_list ':' type ';'
 ;

identifier_list:
 identifier_list ',' IDENTIFIER
 | IDENTIFIER
 ;

type:
 simple_type
 | named_type
 | index_type
 | structured_type
 | pointer_type
 ;

simple_type:
 TOKEN_CHARACTER
 | TOKEN_BOOLEAN
 | TOKEN_INTEGER
 ;

named_type:
 IDENTIFIER
 ;

index_type:
 enumerated_type
 | subrange_type
 ;

enumerated_type:
 '('  enumerated_type_list ')'
 ;

enumerated_type_list:
 enumerated_type_list ',' enumerated_type_arg
 | enumerated_type_arg
 ;

enumerated_type_arg:
 IDENTIFIER
 ;

subrange_type:
 constant TOKEN_DOTDOT constant
 ;

constant:
 INTEGER
 | IDENTIFIER
 ;

structured_type:
 array_type
 ;

array_type:
 TOKEN_ARRAY '[' range_type ']' TOKEN_OF type
 ;

range_type:
 subrange_type
 | named_type
 ;

pointer_type:
 '^' type
 ;

procedure_and_function_definition_part:
 procedure_and_function_definition_list
 | /* empty */
 ;

procedure_and_function_definition_list:
 procedure_and_function_definition_list procedure_and_function_definition
 | procedure_and_function_definition
 ;

procedure_and_function_definition:
 procedure_and_function_definition_head variable_declaration_part  block
 | procedure_and_function_definition_head ';'
 ;

block:
 TOKEN_BEGIN statement_part TOKEN_END
 ;

procedure_and_function_definition_head:
 TOKEN_PROCEDURE  IDENTIFIER '(' argt_part ')'
 ;

procedure_and_function_definition_head: 
 TOKEN_FUNCTION  IDENTIFIER '(' argt_part ')' ':' type
 ;

argt_part:
 argt_list
 | /* empty */
 ;

argt_list:
 argt_list ',' argt
 | argt
 ;

argt:
 IDENTIFIER ':' type
 ;

statement_part:
 statement_list
 | /* empty */
 ;

statement_list:
 statement_list statement
 | statement
 ;

statement:
 simple_statement
 | structured_statement
 ;

simple_statement:
 assignment_statement
 | procedure_expression ';'
 | TOKEN_NEW '(' variable_access ')' ';'
 | TOKEN_DISPOSE '(' variable_access ')' ';'
 | TOKEN_RETURN '(' expression ')' ';'
 | print_statement
 ;

assignment_statement:
 variable_access TOKEN_AFF expression ';'
 ;

procedure_expression:
 IDENTIFIER  '(' expression_part ')'
 ;

expression_part:
 expression_list
 | /* empty */
 ;

expression_list:
 expression_list ',' expression
 | expression
 ;

print_statement:
 TOKEN_PRINT '(' expression ')' ';'
 | TOKEN_PRINTLN '(' expression ')' ';'
 ;

structured_statement:
 block
 | if_statement
 | while_statement
 ;

if_statement:
 TOKEN_IF expression TOKEN_THEN statement
 | TOKEN_IF expression TOKEN_THEN statement TOKEN_ELSE statement
 ;

while_statement:
 TOKEN_WHILE expression TOKEN_DO statement
 ;

variable_access:
 IDENTIFIER
 | indexed_variable
 | variable_access '^'
 ;

indexed_variable:
 variable_access '[' expression ']'
 ;

expression:
 variable_access
 | expression '+' expression
 | expression '*' expression
 | expression '-' expression
 | expression '/' expression
 | expression TOKEN_OR expression
 | expression TOKEN_AND expression
 | '-' expression %prec UNMINUS
 | '!' expression
 | expression '<' expression
 | expression TOKEN_LE expression
 | expression '>' expression
 | expression TOKEN_GE expression
 | expression '=' expression
 | expression TOKEN_NE expression
 | '(' expression ')'
 | procedure_expression
 | procedure_expression '^'
 | literal
 ;

literal:
 INTEGER
 | CHARACTER
 | TOKEN_TRUE
 | TOKEN_FALSE
 | TOKEN_NULL
 ;

%%
 
 int main(int argn, char **argv){
   printf("Debut analyse syntaxique :\n");
   yyparse();
   printf("Fin analyse !\n");
   /*printf("Resultat :\n");
   if(error){
     printf("\tEchec : Des lexemes n\'appartiennet pas lexique du langage !\n");
   }
   else{
     printf("\tOK !\n");
     }*/
   return 0;
   //EXIT_SUCCESS;
 }
 
int yyerror(char *msg){
  fprintf(stderr, "*** error: %s\n", msg);
}
