#include "fasta/tok.h"
#include "error.h"
#include "fasta/error.h"
#include "tok.h"
#include <string.h>

#define DELIM " \t\r"

static void add_space_before_newline(char line[FASTA_TOK_LINE_MAX]);
static enum fasta_rc next_line(FILE *restrict fp, char error[FASTA_ERROR_SIZE],
                               char line[FASTA_TOK_LINE_MAX]);

void fasta_tok_init(struct fasta_tok *tok, char *error)
{
    tok->id = TOK_NL;
    tok->value = tok->line.data;
    memset(tok->line.data, '\0', FASTA_TOK_LINE_MAX);
    tok->line.number = 0;
    tok->line.consumed = true;
    tok->line.ctx = NULL;
    tok->error = error;
}

enum fasta_rc fasta_tok_next(struct fasta_tok *tok, FILE *restrict fp)
{
    enum fasta_rc rc = FASTA_SUCCESS;

    if (tok->line.consumed)
    {
        if ((rc = next_line(fp, tok->error, tok->line.data)))
        {
            if (rc == FASTA_ENDFILE)
            {
                tok->value = NULL;
                tok->id = TOK_EOF;
                tok->line.data[0] = '\0';
                return FASTA_SUCCESS;
            }
            return rc;
        }
        tok->value = strtok_r(tok->line.data, DELIM, &tok->line.ctx);
        tok->line.number++;
    }
    else
        tok->value = strtok_r(NULL, DELIM, &tok->line.ctx);

    if (!tok->value) return FASTA_PARSEERROR;

    if (!strcmp(tok->value, "\n"))
        tok->id = TOK_NL;
    else if (*tok->value == '>')
        tok->id = TOK_ID;
    else
        tok->id = TOK_WORD;

    tok->line.consumed = tok->id == TOK_NL;

    return FASTA_SUCCESS;
}

static enum fasta_rc next_line(FILE *restrict fp, char error[FASTA_ERROR_SIZE],
                               char line[FASTA_TOK_LINE_MAX])
{
    if (!fgets(line, FASTA_TOK_LINE_MAX - 2, fp))
    {
        if (feof(fp)) return FASTA_ENDFILE;

        return error_io(error, ferror(fp));
    }

    add_space_before_newline(line);
    return FASTA_SUCCESS;
}

static void add_space_before_newline(char line[FASTA_TOK_LINE_MAX])
{
    unsigned n = (unsigned)strlen(line);
    if (n > 0)
    {
        if (line[n - 1] == '\n')
        {
            line[n - 1] = ' ';
            line[n] = '\n';
            line[n + 1] = '\0';
        }
        else
        {
            line[n] = ' ';
            line[n + 1] = '\n';
            line[n + 2] = '\0';
        }
    }
}
