#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"

const token SEPARATORS[] = {
	{.type = TOKEN_OPEN_PAREN, .value = "("},
	{.type = TOKEN_CLOSE_PAREN, .value = ")"},
	{.type = TOKEN_OPEN_BRACE, .value = "{"},
	{.type = TOKEN_CLOSE_BRACE, .value = "}"},
	{.type = TOKEN_OPEN_BRACKET, .value = "["},
	{.type = TOKEN_CLOSE_BRACKET, .value = "]"},
	{.type = TOKEN_COMMA, .value = ","},
	{.type = TOKEN_SEMICOLON, .value = ";"},
};
const size_t SEPARATOR_COUNT = sizeof(SEPARATORS) / sizeof(token);

const token KEYWORDS[] = {
	{.type = TOKEN_KEYWORD_INT, .value = "int"},
	{.type = TOKEN_KEYWORD_IF, .value = "if"},
	{.type = TOKEN_KEYWORD_CHAR, .value = "char"},
	{.type = TOKEN_KEYWORD_ELSE, .value = "else"},
	{.type = TOKEN_KEYWORD_WHILE, .value = "while"},
	{.type = TOKEN_KEYWORD_VOID, .value = "void"},
	{.type = TOKEN_KEYWORD_RETURN, .value = "return"},
};
const size_t KEYWORD_COUNT = (int) sizeof(KEYWORDS) / sizeof(token);

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

token lexer_next(FILE *fp) {
	lexer_consume(fp);

	if (lexer_end(fp).type == TOKEN_END) { 
		return (token) {.type = TOKEN_END, .line = line};
	}

	token t = lexer_spacer(fp);
	if (t.type != TOKEN_UNKNOWN)
		return t;
	t = lexer_keyword(fp);
	if (t.type != TOKEN_UNKNOWN)
		return t;
	t = lexer_start_identifier(fp);
	if (t.type != TOKEN_UNKNOWN)
		return t;
	t = lexer_number(fp);
	if (t.type != TOKEN_UNKNOWN)
		return t;
	t = lexer_operator(fp);
	if (t.type != TOKEN_UNKNOWN)
		return t;
	
	fgetc(fp); // consume unknown
	return t;
}

token lexer_end(FILE *fp) {
	int c = fgetc(fp);
	if (c == EOF) {
		return (token) {.type = TOKEN_END, .line = line};
	}
	ungetc(c, fp);
	return (token) {.type = TOKEN_UNKNOWN, .line = line};
}

token lexer_spacer(FILE *fp) {
	int c = fgetc(fp);
	for (int i = 0; i < (int) SEPARATOR_COUNT; i++) {
		if (c == *SEPARATORS[i].value) {
			return (token) { .type = SEPARATORS[i].type, .line = line };
		}
	}
	ungetc(c, fp);
	return (token) {.type = TOKEN_UNKNOWN, .line = line};
}

token lexer_operator(FILE *fp) {
	int c = fgetc(fp);

	if (c == '=') {
		c = fgetc(fp);
		if (c == '=') {
			return (token) {.type = TOKEN_EQUAL_TO, .line = line};
		} else {
			ungetc(c, fp);
			return (token) {.type = TOKEN_EQUAL, .line = line};
		}
	} else if (c == '!') {
		c = fgetc(fp);
		if (c == '=') {
			return (token) {.type = TOKEN_NOT_EQUAL, .line = line};
		} else {
			ungetc(c, fp);
			return (token) {.type = TOKEN_NOT, .line = line};
		}
	} else if (c == '<') {
		c = fgetc(fp);
		if (c == '=') {
			return (token) {.type = TOKEN_LESS_THAN_EQUAL, .line = line};
		} else {
			ungetc(c, fp);
			return (token) {.type = TOKEN_LESS_THAN, .line = line};
		}
	} else if (c == '>') {
		c = fgetc(fp);
		if (c == '=') {
			return (token) {.type = TOKEN_GREATER_THAN_EQUAL, .line = line};
		} else {
			ungetc(c, fp);
			return (token) {.type = TOKEN_GREATER_THAN, .line = line};
		}
	}

	ungetc(c, fp);
	return (token) {.type = TOKEN_UNKNOWN, .line = line};
}

token lexer_keyword(FILE *fp) {
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
				return (token) { .type = TOKEN_KEYWORD_INT, .line = line };
			} else {
				off_t pos = ftello(fp);
				return lexer_identifier(fp, start, pos-start);
			}
		} else if (c == 'f') {
			return (token) { .type = TOKEN_KEYWORD_IF, .line = line };
		} else {
			off_t pos = ftello(fp);
			return lexer_identifier(fp, start, pos-start);
		}
	}else if (valid_ident_start(c)) {
		off_t pos = ftello(fp);
		return lexer_identifier(fp, start, pos-start);
	}
	
	ungetc(c, fp);
	return (token) {.type = TOKEN_UNKNOWN, .line = line};
}

int valid_ident_start(int c) {
	return isalpha(c) || c == '_';
}

int valid_ident_body(int c) {
	return isalpha(c) || isdigit(c) || c == '_';
}

token lexer_start_identifier(FILE *fp) {
	int c = fgetc(fp);
	if (valid_ident_start(c)) {
		off_t start = ftello(fp) - 1;
		return lexer_identifier(fp, start, 1);
	}

	ungetc(c, fp);
	return (token) {.type = TOKEN_UNKNOWN, .line = line};
}

token lexer_number(FILE *fp) {
	off_t start = ftello(fp);
	int c = fgetc(fp);

	if (isnumber(c)) {
		token number = { .type = TOKEN_NUMBER, .line = line };
		c = fgetc(fp);
		while (isnumber(c)) {
			c = fgetc(fp);
		}
		ungetc(c, fp);
		off_t end = ftello(fp);
		size_t length = end - start;

		number.value = lexer_analyze(fp, start, length);
		return number;
	}

	ungetc(c, fp);
	return (token) {.type = TOKEN_UNKNOWN, .line = line};
}

token lexer_identifier(FILE *fp, off_t start, size_t length) {
	int c = fgetc(fp);
	token ident = { .type = TOKEN_IDENTIFIER, .line = line };
	while (valid_ident_body(c)) {
		length++;
		c = fgetc(fp);
	}
	ident.value = lexer_analyze(fp, start, length);
	ungetc(c, fp);
	return ident;
}

char* lexer_analyze(FILE *fp, off_t start, size_t length) {
	off_t restore = ftello(fp);

	fseeko(fp, start, SEEK_SET);
	char* value = (char*) malloc(sizeof(char) * length + 1);
	for (int i = 0; i < (int) length; i++) {
		value[i] = fgetc(fp);
	}
	value[length] = '\0';

	fseeko(fp, restore, SEEK_SET);
	return value;
}

token_stream lexer(FILE *fp) {
	token_stream ts = token_stream_init();

	token t = lexer_next(fp);
	while (t.type != TOKEN_END) {
		token_stream_push(&ts, &t);
		t = lexer_next(fp);
	}

	ts.cursor = 0;
	return ts;
}

// int main(int argc, char** argv) {
// 	if (argc < 2) {
// 		printf("lexer <file.cmm>\n");
// 		return 1;
// 	}
// 
// 	FILE *fp = fopen(argv[1], "r");
// 
// 	lexer(fp);
// 
// 	fclose(fp);
// 
// 	return 0;
// }
