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

    if( freTok->type == INVALID_TOKEN || freTok ->type == IDENT_TOKEN ){
        free(freTok->val.string);
    }

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
        case INT_TOKEN:
            printf( "<INT, %ld> \n",  currToken->val.integer );
            break;
        case FLOAT_TOKEN:
            printf( "<FLOAT, %f> \n", currToken->val.floating_point );
            break;
        case ADDOP_TOKEN:
            printf( "<ADD_OP, %c> \n",  currToken->val.op);
            break;
        case MULTOP_TOKEN:
            printf( "<MULT_OP, %c> \n", currToken->val.op);
            break;
        case RPAREN_TOKEN:
            printf( "<RPAREN>\n" );
            break;
        case LPAREN_TOKEN:
            printf( "<LPAREN>\n" );
            break;
        case ASSIGN_TOKEN:
            printf( "<ASSIGN>\n" );
            break;
        case SEMICOLON_TOKEN:
            printf( "<SEMICOLON>\n" );
            break;
        case EOF_TOKEN:
            printf( "<EOF> ");
            break;
        case IDENT_TOKEN:
            printf( "<IDENT, %s> \n", currToken->val.string );
            break;
        case REPEAT_TOKEN:
            printf( "<REPEAT>\n" );
            break;
        case PRINT_TOKEN:
            printf( "<PRINT>\n" );
            break;
        case INVALID_TOKEN:
            printf( "<INVALID, %s>\n", currToken->val.string );
            break;
        default:
            puts( "bloop" );

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

 char *identifierStr;

 if( strcmp( str, "print") == 0 ){
     // set type to print
     token->type = PRINT_TOKEN;
 } else if ( strcmp( str, "repeat") == 0 ){
     //set type to repeat
     token->type = REPEAT_TOKEN;

 } else{
     //set type to identifier
     token->type =IDENT_TOKEN;
      identifierStr = calloc(sizeof(char ), strlen( str) + 1);
     //enter null terminated at the end
     strcpy( identifierStr, str);
     token->val.string = identifierStr;

 }

    /*
     * TODO(done)
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

    //counters
    bool acceptToken = false;

    while (currentChar != EOF && token->type == UNASSIGNED) {
        currentChar = (char) getchar();


        //IF WE DO NOT ENCOUNTER A SPACE
        if (currentChar != ' ' ) {

            /**********************************************************************/

            //NORMAL LETTERS

            if (state != INVALID_STATE && ( currentChar == 'a' || currentChar == 'b' || currentChar == 'c'
                || currentChar == 'd' || currentChar == 'e'
                || currentChar == 'f' || currentChar == 'g' || currentChar == 'h' || currentChar == 'i'
                || currentChar == 'j' || currentChar == 'k' || currentChar == 'l' || currentChar == 'm'
                || currentChar == 'n' || currentChar == 'o' || currentChar == 'p'
                || currentChar == 'q' || currentChar == 'r' || currentChar == 's' || currentChar == 't'
                || currentChar == 'u' || currentChar == 'v' || currentChar == 'w' || currentChar == 'x'
                || currentChar == 'y' || currentChar == 'z' || currentChar == '_'
                || currentChar == '$' || currentChar == 'A' || currentChar == 'B' || currentChar == 'C'
                || currentChar == 'D' || currentChar == 'E' || currentChar == 'F' || currentChar == 'G'
                || currentChar == 'H' || currentChar == 'I' || currentChar == 'J' || currentChar == 'K'
                || currentChar == 'L' || currentChar == 'M' || currentChar == 'N' || currentChar == 'O'
                || currentChar == 'P' || currentChar == 'Q' || currentChar == 'R' || currentChar == 'S'
                || currentChar == 'T' || currentChar == 'U' || currentChar == 'V' || currentChar == 'W'
                || currentChar == 'X' || currentChar == 'Y' || currentChar == 'Z')) {

                if( state == START_STATE ){
                    state = IDENTIF_STATE;
                }

                if( state != IDENTIF_STATE ){
                    state = INVALID_STATE;
                    stringValue[stringValueIndex] = currentChar;
                    stringValueIndex++;

                } else{
                    stringValue[stringValueIndex] = currentChar;
                    stringValueIndex++;
                }


            /**********************************************************************/

            //INTEGERS AND FLOATS

        } else if ( state != INVALID_STATE && (currentChar == '0'|| currentChar == '1' || currentChar == '2' || currentChar == '3' || currentChar == '4'
                || currentChar == '5' || currentChar == '6' || currentChar == '7' || currentChar == '8'
                || currentChar == '9' || currentChar == '.' )) {

                if (state == START_STATE) {
                    state = INT_STATE;
                }

                if (state == INT_STATE || state == FLOAT_STATE){

                    //if '.' and already contains a digit
                    if (currentChar == '.' && (stringValue[0] == '0' || stringValue[0] == '1'
                       || stringValue[0] == '2' || stringValue[0] == '3' ||
                       stringValue[0] == '4' || stringValue[0] == '5' || stringValue[0] == '6' ||
                       stringValue[0] == '7' || stringValue[0] == '8'|| stringValue[0] == '9' )) {

                        // it is a float
                        state = FLOAT_STATE;
                        stringValue[stringValueIndex] = currentChar;
                        stringValueIndex++;
                    }
                    //if we have not encountered a float
                    else if( state != FLOAT_STATE) {
                            stringValue[stringValueIndex] = currentChar;
                            stringValueIndex++;
                        }

                    //adding to the float the next time around
                    else if (state == FLOAT_STATE && currentChar != '.') {
                            stringValue[stringValueIndex] = currentChar;
                            stringValueIndex++;
                    }

             //adding onto identifier
            } else if( state == IDENTIF_STATE ){
                    stringValue[stringValueIndex] = currentChar;
                    stringValueIndex++;
                }

           /**********************************************************************/

           //EVERYTHING ELSE


            }  else if ( currentChar == '+' || currentChar == '-') { //done
                if( state == INVALID_STATE ){
                    acceptToken = true;
                    ungetc(currentChar, stdin);
                } else{
                    //addOp
                    state = ADDOP_STATE;
                    token->type = ADDOP_TOKEN;
                    token->val.op = currentChar;

                }


            } else if ( currentChar == '*' || currentChar == '%' || currentChar == '/') { //done
                if( state == INVALID_STATE ){
                    acceptToken = true;
                    ungetc(currentChar, stdin);
                } else{
                    //multOp
                    state = MULTOP_STATE;
                    token->type = MULTOP_TOKEN;
                    token->val.op = currentChar;

                }

            } else if( currentChar == '='){ //done
                if( state == INVALID_STATE){
                    acceptToken = true;
                    ungetc(currentChar, stdin);
                } else{
                    //assign
                    state = ASSIGN_STATE;
                    token->type = ASSIGN_TOKEN;
                }

            }
            else if ( currentChar == '(') { //done
                if( state == INVALID_STATE ){
                    acceptToken = true;
                    ungetc(currentChar, stdin);
                } else{
                    //lparen
                    state = LPAREN_STATE;
                    token->type = LPAREN_TOKEN;

                }

            } else if ( currentChar == ')') { //done
                if( state == INVALID_STATE|| state == INT_STATE || state == IDENTIF_STATE){
                    acceptToken= true;
                    ungetc(currentChar, stdin);
                } else{
                    //rparen
                    state = RPAREN_STATE;
                    token->type = RPAREN_TOKEN;

                }

            } else if( currentChar == ';' ){
                if( state == INVALID_STATE || state == INT_STATE || state == IDENTIF_STATE || state == FLOAT_STATE){
                    acceptToken = true;
                    ungetc(currentChar, stdin);
                } else{
                    state = SEMICOL_STATE;
                    token->type = SEMICOLON_TOKEN;
                }

            } else if ( currentChar == EOF ){
                state = EOF_STATE;
                token->type = EOF_TOKEN;
            }
            //IF TOKEN HASNT BEEN DECLARED INVALID YET
            else if ( state == START_STATE && currentChar != ' ' && currentChar != '\t'
                        && currentChar != '\n' && currentChar != '\r'){
                state = INVALID_STATE;
                acceptToken = true;
                stringValue[stringValueIndex] = currentChar;
                stringValueIndex++;
            }
            //IF TOKEN HAS ALREADY BEEN DECLARED IN VALID
            else if( state == INVALID_STATE ){
             stringValue[stringValueIndex] = currentChar;
             stringValueIndex++;

         }



    }

        /**********************************************************************/

        //If currentChar is a space and type is still unassigned OR if we are accepting an invalid token

        if ( currentChar == ' ' && token->type == UNASSIGNED && state != START_STATE || acceptToken){

            //THEN we handle INTS, FLOATS, IDENTIFIERS, and INVALIDS
            switch( state ){
                case INT_STATE:
                    token->type = INT_TOKEN;
                    long finalInteger = strtol(&stringValue[0], NULL, 10 );
                    token->val.integer = finalInteger;

                    break;
                case FLOAT_STATE:
                    token->type = FLOAT_TOKEN;
                    double finalFloat = strtod(&stringValue[0], NULL);
                    token->val.floating_point = finalFloat;

                    break;
                case IDENTIF_STATE:
                    setKeywordOrID( token, &stringValue[0]);

                    break;

                case INVALID_STATE:
                    token->type = INVALID_TOKEN;
                    token->val.string = malloc( strlen( &stringValue[0]) + 1 );
                    strcpy( token->val.string, &stringValue[0]);

                    break;
                default:
                    puts( "bloop");

            }

        }


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
        if (stringValueIndex >= bufferSize - 1) {
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

