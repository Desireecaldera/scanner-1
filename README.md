# COMP 232 - Scanner 1

## Overview

In this lab, you will implement a scanner (lexer) for the following grammar:

<a name="grammar"></a>

```
<program> ::= <statement> <EOF> | <statement> <program>

<statement> ::= <assignStmt> | <printStmt> | <repeatStmt>
<assignStmt> ::= <ident> = <expr> ;
<printStmt> ::= print <expr> ;
<repeatStmt> ::= repeat ( <expr> ) <statement>

<expr> ::= <term> | <expr> <addOp> <term>
<term> ::= <factor> | <term> <multOp> <factor>
<factor> ::= <ident> | <number> | <addOp> <factor> | ( <expr> )

<ident> ::= <letter> | <ident> <letter> | <ident> <digit>

<number> ::= <integer> | <float>

<integer> ::= <digit> | <integer> <digit>
<float> ::= <digit> . | <digit> <float> | <float> <digit>

<addOp> ::= + | -
<multOp> ::= * | / | %

<letter> ::= a-z | A-Z | _ | $
<digit> ::= 0-9
```

Note that the `|` characters in the grammar mean "or"; for instance, the production `<letter> ::= a-z | A-Z | _ | $` indicates that a `<letter>` can be any of the following:

* a lowercase english alphabet letter `a-z`
* an uppercase english alphabet letter `A-Z`
* an underscore `_`
* a dollar sign `$`

## Tokens and Lexing

Your first task is to decide which elements of the grammar above are the lexical tokens (from here on to be referred to simply as "tokens"). You have likely encountered a more formal definition for tokens and lexing; here we will think of the tokens in a simpler, more intuitive way: tokens are to statements as words and punctuation are to sentences.

For example, if we were to tokenize the following english sentence:

`Nick, that is not a sentence.`

The result would be the following tokens:

```
< NOUN Nick >
< PUNCUTATION , >
< PRONOUN that >
< VERB is >
< ADVERB not >
< ARTICLE a >
< NOUN sentence >
< PUNCTUATION . >
```

Note that lexing is disjoint from syntax; a sequence of random words which make absolutely no sense as a sentence could still be lexed correctly, but issues would arise when parsing as an invalid sentence cannot parsed find any coherent meaning. Here, we are not looking to parse the input, only to lex it.

Look through the [grammar](#grammar) and list the token types.

HINTS:

* There are 13 token types, including `INVALID` and `EOF` (end of file).
* `number`, `digit` and `letter` are **not** token types.
* Left and right parenthesis are separate types.
* There are two keywords. Each keyword has its own type. There is no `keyword` type.
* The different types of statements are not tokens; we'll make them out of sequences of tokens when we start parsing in a future lab.
* Tokens are **not nestable**; a token cannot be comprised of elements containing other tokens.

## Finite State Machine

Now that you've identified all of the token types, you can create a finite state machine for tokenization. The state machine has been started below, and you must complete it:

![start_fsa](./figures/start_fsa.png)

The machine should have a single starting state. The machine's transitions depend on the value of the next character. For example, given the input `123`, we would start in the `START` state,  Whenever a character is read for which there is no transition out of the current state, the implication is that this character is the start of the next token, so the current token (whose type is determined by the state the machine is in) is complete.

Your state machine should treat keywords and identifiers identically; in our implementation, we will do some post-processing to differentiate between keywords and identifiers.

Draw a state machine to construct all of the tokens as described in the grammar. Your state machine must be included in your lab submission.

## Lexer Implementation

You've now finished the theoretical foundation of the lexer to be implemented. Use the provided code as a starting point to complete a lexer for the provided grammar.

Open `scanner.h`, and complete the `TOKEN_TYPE` enum and the `FSM_STATE` enum. These will list the types of tokens the scanner will return, and the states in the scanner's underlying finite state machine.

Read the `TOKEN_VALUE` union. For each `TOKEN_TYPE`, decide what member of the `TOKEN_VALUE` union (if any) should be populated. Note that `TOKEN_TYPE`s for which the type conveys all necessary information about the token do not need to store any `TOKEN_VALUE`; for instance, storing the `"("` string in a left-parenthesis token would be redundant.

Once you are comfortable with the code in `scanner.h`, move on to `main.c`. This main is relatively simple; it essentially lexes in a loop until the resulting token is an `EOF` token, printing and freeing each token in the process.

Note the first line in the `main` function:

```c
freopen(argv[1], "r", stdin);
```

By now we should be familiar with `freopen`; we know this line is overwriting the `stdin` so input can be more easily gathered from elsewhere. `argv[1]` is the string value of the first program argument; it should be the name of the file we wish to use as input.

We have a provided input file, `input.txt`. We need `argv[1]` to be the path to `input.txt` in order for the input from `input.txt` to be used.

CLion allows us to provide program arguments in the Run Configurations; open the `Run` menu, select `Edit Configurations`, select the `scanner` executable and in the `Program arguments` box enter `../input.txt`.

Once you are comfortable with both `scanner.h` and `main.c`, you're ready to work on your lexer!

Open `scanner.c`. There are four `TODO`s in the file.

The intended functionality for `freeToken` and `printToken` should be intuitive, and we will not discuss them further here; they are described in their `TODO` comments.

The `scanner` function should emulate your state machine to tokenize inputs, character by character, to create and return a single token. It will do so by reading 1 new character in each iteration of a while loop. It must use these characters (along with the current state of the finite state machine) to determine what state transitions to take, and to determine when to assign value to the token being constructed.

When a token is composed of multiple characters, you'll generally know it's "done" when you encounter a character that is not part of the token being composed. For instance, if your state machine is in the `INTEGER_STATE` and you encounter a semicolon, that semicolon is clearly not part of the integer-in-progress, so it must be part of the **next** token; the integer is complete and can be returned. When this happens, you'll want to first put the unused character back on the input stream so it can be reconsidered as the beginning of the following token. Check out the manual entry for `ungetc`.

There is an exception to this rule: if a letter is encountered while an integer or float is under construction, then whole thing (including the preceeding digits and decimal point) is an invalid token.

When a token-in-progress is deemed invalid, the state machine should keep adding characters into this invalid token until a character which is neither a `<letter>` nor a `<digit>` is encountered, and then this whole sequence of characters should be stored as the string value for an invalid token. For an example, see the first line of as shown in `input.txt` and the start of the [sample run](#sample_run) below.

Don't forget to deal with characters which aren't included in the grammar (see how `&` tokenization in the sample run below), and to consider allow white space characters (space, newline, carriage return and tab) to be used as separators between tokens.

## Sample Run <a name="sample_run"></a>

The following is a successful sample run for the provided [`input.txt`](./lab_4_scanner/input.txt):

```
<INT, 123>
<IDENT, abc>
<INVALID, 123._abc>
<INVALID, 456$>
<RPAREN>
<INVALID, &>
<IDENT, firstvar>
<ASSIGN>
<INT, 123>
<SEMICOLON>
<IDENT, secondVar>
<ASSIGN>
<FLOAT, 21.000000>
<SEMICOLON>
<IDENT, var3>
<ASSIGN>
<FLOAT, 1.500000>
<SEMICOLON>
<REPEAT>
<LPAREN>
<INT, 10>
<RPAREN>
<IDENT, var3>
<ASSIGN>
<INT, 2>
<MULT_OP, *>
<LPAREN>
<IDENT, firstvar>
<ADD_OP, +>
<IDENT, secondVar>
<RPAREN>
<MULT_OP, />
<LPAREN>
<IDENT, firstvar>
<ADD_OP, +>
<INT, 2>
<RPAREN>
<SEMICOLON>
<REPEAT>
<LPAREN>
<IDENT, firstvar>
<ADD_OP, +>
<INT, 2>
<MULT_OP, *>
<IDENT, secondVar>
<RPAREN>
<PRINT>
<IDENT, firstvar>
<SEMICOLON>
<EOF>


Process finished with exit code 0

```

## Submission Checklist

In your final push, don't forget to:
 
* include a clearly labelled picture of your state machine
* test your program with Valgrind Memcheck and fix any memory errors
* create inputs to more rigorously test your lexer (`input.txt` doesn't test everything)
* include documentation with sample runs (matching your inputs) in your submission (you may replace this README with your documentation or append your documentation to it, if desired).
