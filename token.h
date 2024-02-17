#ifndef TOKEN_H_
#define TOKEN_H_

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

	// non-value literal
	TOKEN_SEMICOLON,
	TOKEN_COMMA,
	TOKEN_OPEN_PAREN,
	TOKEN_CLOSE_PAREN,
	TOKEN_OPEN_BRACE,
	TOKEN_CLOSE_BRACE,
	TOKEN_OPEN_BRACKET,
	TOKEN_CLOSE_BRACKET,

	// operators
	TOKEN_EQUAL,
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
} token_identifier;

typedef struct {
	token_identifier token;
	int line;
} token;

typedef struct {
	token_t type;
	char value;
} token_separator;


char* tokenName(token_t token);

#endif // TOKEN_H_