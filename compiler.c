#include <stdio.h>
#include "lexer.h"
#include "parser.h"

void printTokenStream(token_stream *ts) {
	for (int i = 0; i < ts->length; i++) {
		token t = ts->tokens[i];
		if (t.value != 0) {
			printf("%d: %s (%s)\n", t.line, tokenName(&t), t.value);
		} else {
			printf("%d: %s\n", t.line, tokenName(&t));
		}
	}
}

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("compiler <file.pb>\n");
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	token_stream ts = lexer(fp);

	printTokenStream(&ts);

	parser(&ts);

	token_stream_close(&ts);

	fclose(fp);

	return 0;
}
