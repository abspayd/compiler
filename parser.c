#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "parser.h"

void parser(token_stream *ts) {
	token *t = token_stream_next(ts);
	while (t->type != TOKEN_END) {
		t = token_stream_next(ts);
	}
	printf("End of token stream.\n");
}
