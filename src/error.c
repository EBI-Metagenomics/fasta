#include "error.h"
#include "fasta/error.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define PARSE_ERROR "Parse error: "
#define RUNTIME_ERROR "Runtime error: "
#define LINE ": line"

static int copy_fmt(int dst_size, char *dst, char const *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(dst, (size_t)dst_size, fmt, ap);
    va_end(ap);
    assert(n >= 0);
    return n;
}

static int copy_ap(int dst_size, char *dst, char const *fmt, va_list ap)
{
    int n = vsnprintf(dst, (size_t)dst_size, fmt, ap);
    assert(n >= 0);
    return n;
}

#define unused(x) ((void)(x))

enum fasta_rc error_io(char *dst, int errnum)
{
    int rc = strerror_r(errnum, dst, FASTA_ERROR_SIZE);
    assert(!rc);
    unused(rc);
    return FASTA_IOERROR;
}

enum fasta_rc error_runtime(char *dst, char const *fmt, ...)
{
    int n = copy_fmt(FASTA_ERROR_SIZE, dst, RUNTIME_ERROR);
    va_list ap;
    va_start(ap, fmt);
    copy_ap(FASTA_ERROR_SIZE - n, dst + n, fmt, ap);
    va_end(ap);
    return FASTA_RUNTIMEERROR;
}

enum fasta_rc error_parse(char *dst, unsigned line, char const *fmt, ...)
{
    int n = copy_fmt(FASTA_ERROR_SIZE, dst, PARSE_ERROR);
    va_list ap;
    va_start(ap, fmt);
    n += copy_ap(FASTA_ERROR_SIZE - n, dst + n, fmt, ap);
    va_end(ap);
    copy_fmt(FASTA_ERROR_SIZE - n, dst + n, "%s %d", LINE, line);
    return FASTA_PARSEERROR;
}
