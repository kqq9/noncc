#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

struct lexer_
{
	FILE *src;
	token *t;
};

lexer *lexer_create(FILE *f)
{
	lexer *l = malloc(sizeof(lexer));
	l->src = f;
	l->t = malloc(sizeof(token));
	return l;
}

void lexer_destroy(lexer *l)
{
	free(l->t);
	free(l);
}

token *lexer_token(lexer *l)
{
	return l->t;
}

void lexer_next_token(lexer *l)
{
	if (l->t->type == TOKEN_WORD) {
		free(l->t->word_buffer);
	}
	int buffer = fgetc(l->src);
	while (buffer != EOF && isspace(buffer)) {
		buffer = fgetc(l->src);
	}
	if (feof(l->src)) {
		l->t->type = TOKEN_EOF;
		return;
	}
	int len = 0, cap = 8;
	l->t->type = TOKEN_WORD;
	l->t->word_buffer = malloc(8);
	while (buffer != EOF && !isspace(buffer)) {
		len += 1;
		if (len + 1 > cap) {
			l->t->word_buffer = realloc(l->t->word_buffer, cap *= 2);
		}
		l->t->word_buffer[len - 1] = buffer;
		buffer = fgetc(l->src);
	}
	l->t->word_buffer[len] = 0;
}

int lexer_eof(lexer *l)
{
	return feof(l->src);
}
