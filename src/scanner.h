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
    // TODO complete the enum
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
    // TODO complete the enum
    // Recall that identifiers and keywords share a state.
} FSM_STATE;

TOKEN *scanner();
void freeToken(TOKEN **);
void printToken(TOKEN **);

#endif