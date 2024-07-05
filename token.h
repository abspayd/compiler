#ifndef TOKEN_H_
#define TOKEN_H_

#include <ctype.h>

typedef enum {
	TOKEN_END=0,
	TOKEN_UNKNOWN,

	TOKEN_COMMENT,

	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,

	// keywords
	TOKEN_KEYWORD_CHAR,
	TOKEN_KEYWORD_INT,
	TOKEN_KEYWORD_RETURN,
	TOKEN_KEYWORD_VOID,
	TOKEN_KEYWORD_IF,
	TOKEN_KEYWORD_ELSE,
	TOKEN_KEYWORD_WHILE,
	TOKEN_KEYWORD_TRUE,
	TOKEN_KEYWORD_FALSE,

	// non-value literal
	TOKEN_SEMICOLON,
	TOKEN_COMMA,
	TOKEN_OPEN_PAREN,
	TOKEN_CLOSE_PAREN,
	TOKEN_OPEN_BRACE,
	TOKEN_CLOSE_BRACE,
	TOKEN_OPEN_BRACKET,
	TOKEN_CLOSE_BRACKET,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_STAR,
	TOKEN_FORWARD_SLASH,

	// operators
	TOKEN_EQUAL,
	TOKEN_EQUAL_TO,
	TOKEN_NOT,
	TOKEN_NOT_EQUAL,
	TOKEN_LESS_THAN,
	TOKEN_LESS_THAN_EQUAL,
	TOKEN_GREATER_THAN,
	TOKEN_GREATER_THAN_EQUAL,
} token_t;

typedef struct {
	token_t type;
	char* value;
	int line;
} token;

typedef struct {
	token* tokens;
	size_t length;
	size_t capacity;
	size_t cursor;
} token_stream;

#define INIT_STREAM_CAPACITY 1024

token_stream token_stream_init(void);
void token_stream_push(token_stream *ts, token *t);
token *token_stream_next(token_stream *ts);
void token_stream_resize(token_stream *ts, size_t size);
void token_stream_close(token_stream *ts);

char* tokenName(token *token);

#endif // TOKEN_H_
