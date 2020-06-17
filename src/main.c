//
//  main.c (driver for a scanner test)
//
//  Created by Bieszczad, A.J. on 9/20/17.
//  Copyright (c) 2017 CSUCI. All rights reserved.
//
//  ASSUMES: Lecture 1, 2, 3, 4

#include "scanner.h"

int main(int argc, char **argv)
{
    freopen(argv[1], "r", stdin);

    TOKEN *token = NULL;
    printf("\n");

    do
    {
        freeToken(&token);
        token = scanner();
        printToken(&token);
        fflush(stdout);
    }
    while (token->type != EOF_TOKEN);

    freeToken(&token);

    printf("\n");
    exit(EXIT_SUCCESS);
}