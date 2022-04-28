#ifndef FASTA_TOK_H
#define FASTA_TOK_H

#include <stdbool.h>

#define FASTA_TOK_LINE_MAX 256

struct fasta_tok
{
    unsigned id;
    char const *value;
    struct
    {
        char data[FASTA_TOK_LINE_MAX];
        unsigned number;
        bool consumed;
        char *ctx;
    } line;
    char *error;
};

#endif
