#ifndef __SCANNER_H
#define __SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    UNASSIGNED,
    INVALID_TOKEN,
    EOF_TOKEN,
    REPEAT,
    ASSIGN,    // =
    FLOAT,
    INT,
    IDENT,
    RPAREN,
    LPAREN,
    MULT_OP,    // * /
    ADD_OP,
    SEMICOLON,
    PRINT,

    // TODO complete the enum (I believe this is done)
    // there are 11 more...
} TOKEN_TYPE;

typedef union
{
    long integer;
    double floating_point;
    char *string;
    char op;
} TOKEN_VALUE;

typedef struct token
{
    TOKEN_TYPE type;
    TOKEN_VALUE val;
} TOKEN;

typedef enum
{
    START_STATE,
    INVALID_STATE,
    SEMICOL_STATE,  // ;
    ASSIGN_STATE,  // = assign
    LPAREN_STATE, // lparen
    RPAREN_STATE,  //rparen
    ADDOP_STATE,   //addOP + -
    MULTOP_STATE,  // multOp * / %
    IDENTIF_STATE,  //indentifier [a-z]+  [0-9]+
    INT_STATE,   // int [0-9]+
    FLOAT_STATE,   // float [0-9]+ [.][0-9]+
    EOF_STATE,  //EOF

     //each keyword such as print and repeat has its own type



    // TODO complete the enum(almost done)
    // Recall that identifiers and keywords share a state.
} FSM_STATE;

TOKEN *scanner();
void freeToken(TOKEN **);
void printToken(TOKEN **);

#endif