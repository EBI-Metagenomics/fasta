#ifndef ERROR_H
#define ERROR_H

#include "fasta/rc.h"

enum fasta_rc error_io(char *dst, int errnum);
enum fasta_rc error_runtime(char *dst, char const *fmt, ...);
enum fasta_rc error_parse(char *dst, unsigned line, char const *fmt, ...);

#endif
