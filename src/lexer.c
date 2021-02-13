#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

struct lexer_
{
	FILE *src;
};

lexer *lexer_create(FILE *f)
{
	lexer *l = malloc(sizeof(lexer));
	l->src = f;
	return l;
}

void lexer_destroy(lexer *l)
{
	free(l);
}

token lexer_next_token(lexer *l)
{
	char buffer;
	fread(&buffer, 1, 1, l->src);
	while (!feof(l->src) && (
	       buffer == ' ' ||
	       buffer == '\t' ||
	       buffer == '\n' ||
	       buffer == '\r') ) {
		fread(&buffer, 1, 1, l->src);
	}
	if (feof(l->src)) {
		return (token) { .type = TOKEN_EOF };
	}
	int len = 0;
	while (!feof(l->src) && !(
	       buffer == ' ' ||
	       buffer == '\t' ||
	       buffer == '\n' ||
	       buffer == '\r') ) {
		len += 1;
		fread(&buffer, 1, 1, l->src);
	}
	return (token) { .type = TOKEN_WORD, .word_length = len };
}

int lexer_eof(lexer *l)
{
	return feof(l->src);
}
