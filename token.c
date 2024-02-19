#include "token.h"
#include <stdio.h>
#include <stdlib.h>

char* tokenName(token *token) {
	switch (token->type) {
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
		case TOKEN_EQUAL_TO: return "TOKEN_EQUAL_TO";
		case TOKEN_NOT: return "TOKEN_NOT";
		case TOKEN_NOT_EQUAL: return "TOKEN_NOT_EQUAL";
		case TOKEN_LESS_THAN: return "TOKEN_LESS_THAN";
		case TOKEN_LESS_THAN_EQUAL: return "TOKEN_LESS_THAN_EQUAL";
		case TOKEN_GREATER_THAN: return "TOKEN_GREATER_THAN";
		case TOKEN_GREATER_THAN_EQUAL: return "TOKEN_GREATER_THAN_EQUAL";
		case TOKEN_KEYWORD_VOID: return "TOKEN_KEYWORD_VOID";
		case TOKEN_KEYWORD_IF: return "TOKEN_KEYWORD_IF";
		case TOKEN_KEYWORD_ELSE: return "TOKEN_KEYWORD_ELSE";
		case TOKEN_KEYWORD_WHILE: return "TOKEN_KEYWORD_WHILE";
		default: return "Undefinded";
	}
}

token_stream token_stream_init(void) {
	token_stream ts;
	ts.tokens = (token*) malloc(sizeof(token) * INIT_STREAM_CAPACITY);
	ts.length = 0;
	ts.cursor = 0;
	ts.capacity = INIT_STREAM_CAPACITY;
	return ts;
}

void token_stream_close(token_stream *ts) {
	for (size_t i = 0; i < ts->length; i++) {
		free(ts->tokens[i].value);
	}
	free(ts->tokens);
}

void token_stream_resize(token_stream *ts, size_t size) {
	token *tokens_new;
	tokens_new = realloc(ts->tokens, size);
	if (tokens_new != NULL) {
		ts->capacity = size;
	}
}

void token_stream_push(token_stream *ts, token *t) {
	if (ts->length + 1 > ts->capacity) {
		token_stream_resize(ts, ts->capacity * 2);
	}
	ts->tokens[++ts->cursor] = *t;
	ts->length++;
}

token *token_stream_pop(token_stream *ts) {
	token *t = &ts->tokens[ts->cursor--];
	ts->length--;
	return t;
}
