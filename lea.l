/*
En Flex, je commence par les declarations C entre les balises %{ et %}.
La variable lineno (int) correspond au numero de ligne.
La variable error (bool) est true si erreur detectee.
Il existe la variable globale yylineno dans Flex que l'on peut ajouter en option. C'est cense gerer le numero de ligne tout seul..
Ici je gerer le mecanisme de numero de ligne avec le lineno.
*/
 
%{
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "lea.tab.h"
void lexeme(void);
unsigned int lineno=1;
bool error=false;
%}
 
/*On declare les eventuelles variables Flex. Terminaux associes reconnus par les expressions regulieres.*/
 
integer 0|[1-9][[:digit:]]*
/*[[:alnum:]] = [a-zA-Z0-9] (tout les caracteres alphanumeriques)*/
character [[:alpha:]][[:alnum:]]
identifier [[:alnum:]]*
 
/*
Entre les %% -> actions a chaque fois que l'analyseur detectera des lexemes de Lea.
Ici on met donc l'ensemble des terminaux de Lea.
*/
 

%%
"<="            {lexeme(); return TOKEN_LE;}
">="            {lexeme(); return TOKEN_GE;}
":="            {lexeme(); return TOKEN_AFF;}
"="             {lexeme(); return '=';}
"<"             {lexeme(); return '<';}
">"             {lexeme(); return '>';}
"+"             {lexeme(); return '-';}
"-"             {lexeme(); return '-';}
"*"             {lexeme(); return '*';}
"/"             {lexeme(); return '/';}
"("             {lexeme(); return '(';}
")"             {lexeme(); return ')';}
"["             {lexeme(); return '[';}
"]"             {lexeme(); return ']';}
"^"             {lexeme(); return '^';}
":"             {lexeme(); return ':';}
";"             {lexeme(); printf("\n"); return ';';}
"&&"            {lexeme(); return TOKEN_AND;}
"||"            {lexeme(); return TOKEN_OR;}
"!="            {lexeme(); return TOKEN_NE;}
"!"             {lexeme(); return '!';}
".."            {lexeme(); return TOKEN_DOTDOT;}
"true"          {lexeme(); return TOKEN_TRUE;}
"false"         {lexeme(); return TOKEN_FALSE;}
"if"            {lexeme(); return TOKEN_IF;}
"then"          {lexeme(); return TOKEN_THEN;}
"else"          {lexeme(); return TOKEN_ELSE;}
"do"            {lexeme(); return TOKEN_DO;}
"while"         {lexeme(); return TOKEN_WHILE;}
"new"           {lexeme(); return TOKEN_NEW;}
"null"          {lexeme(); return TOKEN_NULL;}
"return"        {lexeme(); return TOKEN_RETURN;}
"print"         {lexeme(); return TOKEN_PRINT;}
"println"       {lexeme(); return TOKEN_PRINTLN;}
"function"      {lexeme(); return TOKEN_FUNCTION;}
"begin"         {lexeme(); return TOKEN_BEGIN;}
"end"           {lexeme(); return TOKEN_END;}
"var"           {lexeme(); return TOKEN_VAR;}
"array"         {lexeme(); return TOKEN_ARRAY;}
"dispose"       {lexeme(); return TOKEN_DISPOSE;}
"of"            {lexeme(); return TOKEN_OF;}
"type"          {lexeme(); return TOKEN_TYPE;}
"procedure"     {lexeme(); return TOKEN_PROCEDURE;}
"integer"       {lexeme(); return TOKEN_INTEGER;}
"character"     {lexeme(); return TOKEN_CHARACTER;}
"boolean"       {lexeme(); return TOKEN_BOOLEAN;}

"\n"    {lineno++;}
 
{integer} {
        /*L'ordre de definition des regles pour chaque lexemes est important en Flex*/
        printf("\tInt a la ligne %d. Valeur: %s Nbr de chiffres: %d\n",lineno,yytext,yyleng);
        return INTEGER;
}

{character} {
        printf("\tVariable a la ligne %d: %s Nbr lettres: %d\n",lineno,yytext,yyleng);
        return CHARACTER;
}
 
{identifier} {
        /*L'ordre de definition des regles pour chaque lexemes est important en Flex*/
        printf("\tIdentifier a la ligne %d. Valeur: %s Nbr de lettres: %d\n",lineno,yytext,yyleng);
        return IDENTIFIER;
}
 
" "|"\t" {
        /*Rien a faire des espaces et tabulations*/
}
 
. {
        /*Point = tout le reste qui n'a pas ete defini avant. Donc dernier cité*/
        fprintf(stderr,"\tERREUR : Lexeme inconnu a la ligne: %d. \' %s \' Nbr lettres: %d\n",lineno,yytext,yyleng);
        error=true;
}
%%
 
/*
Fonctions C apres le %%
Le main appel la fonction de parsing yylex().
*/
 
/*
La variable globale yytext contient le lexeme courant lu par l'analyseur.
*/
 
void lexeme(){
        printf("\tLexeme '%s' trouve a la ligne %d\n",yytext,lineno);
}
 
/*
La fonction yywrap() est appelee des qu'on detecte le caractere EOF (End Of File). Elle doit retourner 1 pour mettre fin a l'analyse.
On peut utiliser la fonction yywrap() par defaut de Flex (qui ne fait que retourner 1 juste), il faut dans ce cas specifier noyywrap en option.
*/
 
int yywrap(){
        printf("\tFin de fichier..\n");
        return 1;
}
