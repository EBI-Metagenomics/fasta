#ifndef TOK_H
#define TOK_H

#include "fasta/rc.h"
#include <stdio.h>

struct fasta_tok;

enum tok_id
{
    TOK_NL,
    TOK_ID,
    TOK_WORD,
    TOK_EOF,
};

void tok_init(struct fasta_tok *tok, char *error);
enum fasta_rc tok_next(struct fasta_tok *tok, FILE *restrict fd);

#endif
