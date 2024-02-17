#include <ctype.h>
#include <stdio.h>
#include "token.h"
#include "lexer.h"

const token_separator SEPARATORS[] = {
	{.type = TOKEN_OPEN_PAREN, .value = '('},
	{.type = TOKEN_CLOSE_PAREN, .value = ')'},
	{.type = TOKEN_OPEN_BRACE, .value = '{'},
	{.type = TOKEN_CLOSE_BRACE, .value = '}'},
	{.type = TOKEN_OPEN_BRACKET, .value = '['},
	{.type = TOKEN_CLOSE_BRACKET, .value = ']'},
	{.type = TOKEN_COMMA, .value = ','},
	{.type = TOKEN_SEMICOLON, .value = ';'},
};
const size_t SEPARATOR_COUNT = sizeof(SEPARATORS) / sizeof(token_separator);

const token_identifier KEYWORDS[] = {
	{.type = TOKEN_KEYWORD_INT, .value = "int"},
	{.type = TOKEN_KEYWORD_CHAR, .value = "char"},
	{.type = TOKEN_KEYWORD_RETURN, .value = "return"},
};
const size_t KEYWORD_COUNT = sizeof(KEYWORDS) / sizeof(token_identifier);

int line = 1;

void lexer_consume(FILE *fp) {
	int c = fgetc(fp);
	while (isspace(c)) {
		if (c == '\n') {
			line++;
		}
		c = fgetc(fp);
	}
	ungetc(c, fp);
}

token_t lexer_next(FILE *fp) {
	lexer_consume(fp);

	if (lexer_end(fp) == TOKEN_END)
		return TOKEN_END;

	token_t t;
	if ((t = lexer_spacer(fp)) && t != TOKEN_UNKNOWN)
		return t;
	if ((t = lexer_keyword(fp)) && t != TOKEN_UNKNOWN)
		return t;
	if ((t = lexer_start_identifier(fp)) && t != TOKEN_UNKNOWN)
		return t;
	if ((t = lexer_number(fp)) && t != TOKEN_UNKNOWN)
		return t;
	
	return TOKEN_UNKNOWN;
}

token_t lexer_end(FILE *fp) {
	int c = fgetc(fp);
	if (c == EOF) {
		return TOKEN_END;
	}
	ungetc(c, fp);
	return TOKEN_UNKNOWN;
}

token_t lexer_spacer(FILE *fp) {
	int c = fgetc(fp);
	for (int i = 0; i < SEPARATOR_COUNT; i++) {
		if (c == SEPARATORS[i].value) {
			return SEPARATORS[i].type;
		}
	}
	ungetc(c, fp);
	return TOKEN_UNKNOWN;
}

token_t lexer_keyword(FILE *fp) {
	off_t start = ftello(fp);

	int c = fgetc(fp);
	if (c == 'i') {
		c = fgetc(fp);
		if (c == 'n') {
			c = fgetc(fp);
			if (c == 't') {
				c = fgetc(fp);
				if (valid_ident_body(c)) {
					off_t pos = ftello(fp);
					return lexer_identifier(fp, start, pos-start);
				}
				ungetc(c, fp);
				return TOKEN_KEYWORD_INT;
			} else {
				off_t pos = ftello(fp);
				return lexer_identifier(fp, start, pos-start);
			}
		} else {
			off_t pos = ftello(fp);
			return lexer_identifier(fp, start, pos-start);
		}
	} else if (valid_ident_start(c)) {
		off_t pos = ftello(fp);
		return lexer_identifier(fp, start, pos-start);
	}
	
	fputc(c, fp);
	return TOKEN_UNKNOWN;
}

int valid_ident_start(int c) {
	return isalpha(c) || c == '_';
}

int valid_ident_body(int c) {
	return isalpha(c) || isdigit(c) || c == '_';
}

token_t lexer_start_identifier(FILE *fp) {
	int c = fgetc(fp);
	if (valid_ident_start(c)) {
		off_t start = ftello(fp) - 1;
		return lexer_identifier(fp, start, 1);
	}

	ungetc(c, fp);
	return TOKEN_UNKNOWN;
}

token_t lexer_number(FILE *fp) {
	int c = fgetc(fp);

	if (isnumber(c)) {
		off_t start = ftello(fp);
		c = fgetc(fp);
		while (isnumber(c)) {
			c = fgetc(fp);
		}
		ungetc(c, fp);
		off_t pos = ftello(fp);
		size_t length = pos - start;

		return TOKEN_NUMBER;
	}

	ungetc(c, fp);
	return TOKEN_UNKNOWN;
}

token_t lexer_identifier(FILE *fp, off_t start, size_t length) {
	int c = fgetc(fp);
	while (valid_ident_body(c)) {
		length++;
		c = fgetc(fp);
	}
	// TODO: get identifier value
	ungetc(c, fp);
	return TOKEN_IDENTIFIER;
}

// TODO: make all lex_ functions return token structs, NOT raw token_t values
//			(we want to know what the token contains)
void lexer(FILE *fp) {
	token_t t = lexer_next(fp);
	while (t != TOKEN_END)
	{
		printf("%d: %s\n", line, tokenName(t));
		t = lexer_next(fp);
	}
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("compiler <file.cmm>\n");
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	lexer(fp);

	fclose(fp);

	return 0;
}
