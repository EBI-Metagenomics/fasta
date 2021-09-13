#ifndef FASTA_AUX_H
#define FASTA_AUX_H

#include "fasta/target.h"

struct fasta_aux
{
    char *begin;
    char *pos;
    char *end;
    char id[FASTA_ID_MAX];
};

#endif
