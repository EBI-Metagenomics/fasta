#ifndef AUX_H
#define AUX_H

#include "fasta/aux.h"

static inline void aux_init(struct fasta_aux *aux)
{
    aux->begin = NULL;
    aux->pos = NULL;
    aux->end = NULL;
    aux->id[0] = '\0';
}

#endif
