#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 32

//
// clean up the referenced token (if it isn't NULL).
//
void freeToken(TOKEN **token)
{

    if( *token == NULL ){
        return;
    }
    TOKEN *freTok = *token;

     free(freTok->val.string);
     free( freTok );
     freTok = NULL;

    /*
     * TODO (done)
     * free the referenced TOKEN*, and any data in
     * the referenced TOKEN which requires freeing
     * (not in that order).
     *
     * Then, set the referenced TOKEN* to NULL.
     */
}

void printToken (TOKEN **token)
{

   TOKEN *currToken = *token;
    switch ( currToken->type ) {
        case INT:
            printf( "< %s > , %ld", currToken->type, currToken->val.integer );
            break;
        case FLOAT:
            printf( "< %s > , %f ", currToken->type, currToken->val.floating_point );
            break;
        case ADD_OP:
            printf( "< %s >, %c ", currToken->type, currToken->val.op);
            break;
        case MULT_OP:
            printf( "< %s >, %c ", currToken->type, currToken->val.op);
            break;
        case RPAREN:
            printf( "< %s > ", currToken->type );
            break;
        case LPAREN:
            printf( "< %s > ", currToken->type );
            break;
        case ASSIGN:
            printf( "< %s > ", currToken->type );
            break;
        case SEMICOLON:
            printf( "< %s > ", currToken->type );
            break;
        case EOF_TOKEN:
            printf( "< %s > ", currToken->type );
            break;
        case IDENT:
            printf( "< %s > , %s ",currToken->type, currToken->val.string );
            break;

    }
    /*
     * TODO
     * Print the referenced token in a readable format.
     * Displayed information should include the token's type,
     * and also the token's value if applicable.
     *
     * Check the sample runs for an example format.
     */
}

void setKeywordOrID(TOKEN *token, char *str)
{
    /*
     * TODO
     * For use in the scanner function, to differentiate between keywords
     * and identifiers (which are treated identically by the state machine).
     *
     * Check if the collected token is a keyword by comparing the string
     * value arg to the string values of the keywords (print and repeat).
     * If the string value denotes is a print or repeat token, change its
     * type to the corresponding TOKEN_TYPE.
     *
     * If the token is not a keyword, then it is an identifier. Change its
     * type accordingly, and store its string value. Note that the str
     * argument is the scanner's buffer, so it should not be assigned
     * directly, but copied; the buffer will be freed before the token
     * is returned (see the bottom of the scanner function).
     *
     * Recall, to copy a string:
     * 1. Allocate enough space to store the string (including the null terminator).
     * 2. Copy the characters into this new space from the original.
     */
}

TOKEN *scanner()
{
    // buffer to store a token's contained characters while it is being tokenized
    size_t bufferSize = BUFFER_SIZE;
    char *stringValue = calloc(sizeof(char), bufferSize);
    int stringValueIndex = 0;

    // allocate space for the new token
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));

    // initialize the token type to denote that the token is in progress
    token->type = UNASSIGNED;

    // set state machine to starting state
    FSM_STATE state = START_STATE;

    char currentChar = '\0';

    while (currentChar != EOF && token->type == UNASSIGNED)
    {
        currentChar = (char) getchar();
        /*
         * TODO
         * Given the current state of the state machine
         * and the next character, update the state machine
         * (and the string value of the token being built,
         * if applicable).
         *
         * DO NOT return anything here. The only return is the
         * one at the end of this function. Note that the while
         * loop stops iterating once token->type is updated, so
         * token->type should only be updated once the token is
         * ready to be returned.
         */

        // if the buffer is full, quadruple its size (do not edit)
        if (stringValueIndex >= bufferSize-1)
        {
            bufferSize *= 4;
            char *temp = calloc(sizeof(char), bufferSize);
            strcpy(temp, stringValue);
            free(stringValue);
            stringValue = temp;
        }
    }

    free(stringValue);
    return token;
}

