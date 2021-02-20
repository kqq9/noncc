#include <stdio.h>
#include <ctype.h>
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
	int buffer = fgetc(l->src);
	while (buffer != EOF && isspace(buffer)) {
		buffer = fgetc(l->src);
	}
	if (feof(l->src)) {
		return (token) { .type = TOKEN_EOF };
	}
	int len = 0, cap = 8;
	token word = { .type = TOKEN_WORD, .word_buffer = malloc(8) };
	while (buffer != EOF && !isspace(buffer)) {
		len += 1;
		if (len + 1 > cap) {
			word.word_buffer = realloc(word.word_buffer, cap *= 2);
		}
		word.word_buffer[len - 1] = buffer;
		buffer = fgetc(l->src);
	}
	word.word_buffer[len] = 0;
	return word;
}

int lexer_eof(lexer *l)
{
	return feof(l->src);
}
