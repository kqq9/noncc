#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "None filename. Giving up...\n");
		return 1;
	}
	char *fname = argv[1];

	FILE *f = fopen(fname, "r");
	lexer *l = lexer_create(f);

	token t = lexer_next_token(l);
	while (t.type != TOKEN_EOF) {
		printf("%d\n", t.word_length);
		t = lexer_next_token(l);
	}

	lexer_destroy(l);
	fclose(f);
}
