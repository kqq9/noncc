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

	token *t = lexer_token(l);
	while (lexer_token_next(l), t->type != TOKEN_EOF) {
		printf("%s\n", t->word_buffer);
	}

	lexer_destroy(l);
	fclose(f);
}
