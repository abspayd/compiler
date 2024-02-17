#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>
#include "token.h"

void lexer(FILE *fp);
void lexer_consume(FILE *fp);
token_t lexer_next(FILE *fp);

token_t lexer_end(FILE *fp);
token_t lexer_next_literal(FILE *fp);
token_t lexer_spacer(FILE *fp);
token_t lexer_keyword(FILE *fp);
token_t lexer_start_identifier(FILE *fp);
token_t lexer_identifier(FILE *fp, off_t start, size_t length);
token_t lexer_number(FILE *fp);

int valid_ident_start(int c);
int valid_ident_body(int c);

#endif // LEXER_H_