#ifndef FASTA_TARGET_H
#define FASTA_TARGET_H

#include "fasta/export.h"
#include "fasta/rc.h"
#include <stdio.h>

#define FASTA_ID_MAX 64
#define FASTA_DESC_MAX 128
#define FASTA_SEQ_MAX (1024 * 1024)

struct fasta;

struct fasta_target
{
    char const *id;
    char const *desc;
    char const *seq;
};

static inline struct fasta_target fasta_target(char const *id, char const *desc,
                                               char const *seq)
{
    return (struct fasta_target){id, desc, seq};
}

struct __fasta_target
{
    char id[FASTA_ID_MAX];
    char desc[FASTA_DESC_MAX];
    char seq[FASTA_SEQ_MAX];
};

#endif
