#include "fasta/fasta.h"
#include "error.h"
#include "fsm.h"
#include "tok.h"
#include <errno.h>
#include <string.h>

static void buffer_init(struct fasta *fa)
{
    fa->buffer.id[0] = '\0';
    fa->buffer.desc[0] = '\0';
    fa->buffer.seq[0] = '\0';
}

void fasta_init(struct fasta *fa, FILE *restrict fd, enum fasta_mode mode)
{
    fa->fd = fd;
    fa->mode = mode;
    fa->target.id = fa->buffer.id;
    fa->target.desc = fa->buffer.desc;
    fa->target.seq = fa->buffer.seq;
    buffer_init(fa);
    fsm_init(&fa->state);
    fa->error[0] = '\0';
    tok_init(&fa->tok, fa->error);
}

enum fasta_rc fasta_read(struct fasta *fa)
{
    if (fa->state == STATE_END) return FASTA_ENDFILE;

    if (fa->state != STATE_BEGIN && fa->state != STATE_PAUSE)
        return error_runtime(fa->error, "unexpected %s call", __func__);

    buffer_init(fa);
    if (fa->state == STATE_PAUSE) strcpy(fa->buffer.id, fa->aux.id);

    enum state initial_state = fa->state;
    do
    {
        enum fasta_rc rc = FASTA_SUCCESS;
        if ((rc = tok_next(&fa->tok, fa->fd))) return rc;

        if ((fa->state = fsm_next(fa->state, &fa->tok, &fa->aux,
                                  &fa->buffer)) == STATE_ERROR)
            return FASTA_PARSEERROR;

    } while (fa->state != STATE_PAUSE && fa->state != STATE_END);

    if (fa->state == STATE_END && initial_state == STATE_BEGIN)
        return FASTA_ENDFILE;

    return FASTA_SUCCESS;
}

void fasta_clearerr(struct fasta *fa) { fa->error[0] = '\0'; }

enum fasta_rc fasta_write(struct fasta *fa, struct fasta_target tgt,
                          unsigned ncols)
{
    if (fprintf(fa->fd, ">%s", tgt.id) < 0) return error_io(fa->error, errno);

    if (tgt.desc[0] && fprintf(fa->fd, " %s", tgt.desc) < 0)
        return error_io(fa->error, errno);

    for (char const *c = tgt.seq; *c; ++c)
    {
        if (((c - tgt.seq) % ncols) == 0)
        {
            if (fputc('\n', fa->fd) == EOF) return error_io(fa->error, errno);
        }
        if (fputc(*c, fa->fd) == EOF) return error_io(fa->error, errno);
    }
    if (fputc('\n', fa->fd) == EOF) return error_io(fa->error, errno);
    return FASTA_SUCCESS;
}
