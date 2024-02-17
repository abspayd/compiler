#include "token.h"

char* tokenName(token_t token) {
	switch (token) {
		case TOKEN_END: return "TOKEN_END";
		case TOKEN_UNKNOWN: return "TOKEN_UNKNOWN";
		case TOKEN_COMMENT: return "TOKEN_COMMENT";
		case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
		case TOKEN_NUMBER: return "TOKEN_NUMBER";
		case TOKEN_KEYWORD_CHAR: return "TOKEN_KEYWORD_CHAR";
		case TOKEN_KEYWORD_INT: return "TOKEN_KEYWORD_INT";
		case TOKEN_KEYWORD_RETURN: return "TOKEN_KEYWORD_RETURN";
		case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";
		case TOKEN_OPEN_PAREN: return "TOKEN_OPEN_PAREN";
		case TOKEN_CLOSE_PAREN: return "TOKEN_CLOSE_PAREN";
		case TOKEN_OPEN_BRACE: return "TOKEN_OPEN_BRACE";
		case TOKEN_CLOSE_BRACE: return "TOKEN_CLOSE_BRACE";
		case TOKEN_OPEN_BRACKET: return "TOKEN_OPEN_BRACKET";
		case TOKEN_CLOSE_BRACKET: return "TOKEN_CLOSE_BRACKET";
		case TOKEN_EQUAL: return "TOKEN_EQUAL";
		case TOKEN_COMMA: return "TOKEN_COMMA";
		default: return "Undefinded";
	}
}
