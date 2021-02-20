#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

struct lexer_;
typedef struct lexer_ lexer;

typedef struct {
	enum {
		TOKEN_WORD,
		TOKEN_EOF
	} type;
	union {
		struct {
			char *word_buffer;
		};
	};
} token;

lexer *lexer_create(FILE *);
void lexer_destroy(lexer *);

token lexer_next_token(lexer *);
int lexer_eof(lexer *);

#endif
