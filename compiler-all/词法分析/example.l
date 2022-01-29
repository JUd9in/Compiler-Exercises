%{
  /* definitions of manifest constants
  LT, LE, EQ, NE, GT, GE,
  IF, THEN, ELSE, ID, NUMBER, RELOP */
#include <stdio.h>
#define LT 1
#define LE 2
#define EQ 3
#define NE 4
#define GT 5
#define GE 6

#define IF 7
#define THEN 8
#define ELSE 9

#define ID 10
#define NUMBER 11
#define RELOP 12

int yylval;
int installID();
int installNum();
%}

/* regular definitions */
delim [ \t\n]
ws {delim}+
letter [A-Za-z]
digit [0-9]
id {letter}({letter}|{digit})*
number {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%

{ws} {/* no action and no return */}
if {printf("(IF, %s)", yytext); return (IF);}
then {printf("(THEN, %s)", yytext); return (THEN);}
else {printf("(ELSE, %s)", yytext); return (ELSE);}
{id} {yylval = (int) installID(); printf("(ID, %s)", yytext); return (ID);}
{number} {yylval = (int) installNum(); printf("(NUMBER, %s)", yytext); return (NUMBER);}
"<" {yylval = LT; printf("(RELOP, %s)", yytext); return (RELOP);}
"<=" {yylval = LE; printf("(RELOP, %s)", yytext); return (RELOP);}
"=" {yylval = EQ; printf("(RELOP, %s)", yytext); return (RELOP);}
"<>" {yylval = NE; printf("(RELOP, %s)", yytext); return (RELOP);}
">" {yylval = GT; printf("(RELOP, %s)", yytext); return (RELOP);}
">=" {yylval = GE; printf("(RELOP, %s)", yytext); return (RELOP);}

%%

int installID() {
  return ID;
}

int installNum() {
  return NUMBER;
}

