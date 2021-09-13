#ifndef FASTA_FASTA_H
#define FASTA_FASTA_H

#include "fasta/aux.h"
#include "fasta/error.h"
#include "fasta/export.h"
#include "fasta/rc.h"
#include "fasta/target.h"
#include "fasta/tok.h"
#include <stdio.h>

enum fasta_mode
{
    FASTA_READ,
    FASTA_WRITE,
};

struct fasta
{
    FILE *restrict fd;
    enum fasta_mode mode;
    struct fasta_target target;
    struct __fasta_target buffer;
    unsigned state;
    struct fasta_tok tok;
    struct fasta_aux aux;
    char error[FASTA_ERROR_SIZE];
};

FASTA_API void fasta_init(struct fasta *fa, FILE *restrict fd,
                          enum fasta_mode mode);

FASTA_API enum fasta_rc fasta_read(struct fasta *fa);

FASTA_API void fasta_clearerr(struct fasta *fa);

FASTA_API void fasta_write(struct fasta *fa, struct fasta_target tgt,
                           unsigned ncols);

#endif
