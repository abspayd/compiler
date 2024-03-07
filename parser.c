#include <stdio.h>
#include "token.h"
#include "parser.h"



void parser(token_stream *token_stream) {
	token *t = token_stream_next(token_stream);
	while (t->type != TOKEN_END) {
		t = token_stream_next(token_stream);
	}
	printf("End of token stream.\n");
}
