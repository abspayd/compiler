#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>
#include "token.h"

void lexer(FILE *fp);
char* lexer_analyze(FILE *fp, off_t start, size_t length);
void lexer_consume(FILE *fp);
token lexer_next(FILE *fp);

token lexer_end(FILE *fp);
token lexer_next_literal(FILE *fp);
token lexer_spacer(FILE *fp);
token lexer_keyword(FILE *fp);
token lexer_start_identifier(FILE *fp);
token lexer_identifier(FILE *fp, off_t start, size_t length);
token lexer_number(FILE *fp);

int valid_ident_start(int c);
int valid_ident_body(int c);

#endif // LEXER_H_
