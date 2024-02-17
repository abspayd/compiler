#include <stdio.h>

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("compiler <file.cmm>\n");
	}

	FILE *fp = fopen(argv[1], "r");

	fclose(fp);

	return 0;
}
