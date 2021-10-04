#include "fasta/fasta.h"
#include "hope/hope.h"

void test_read_empty(void);
void test_read_mix(void);
void test_read_example(void);
void test_read_damaged1(void);
void test_read_damaged2(void);
void test_read_damaged3(void);

int main(void)
{
    test_read_empty();
    test_read_mix();
    test_read_example();
    test_read_damaged1();
    test_read_damaged2();
    test_read_damaged3();
    return hope_status();
}

void test_read_empty(void)
{
    FILE *fd = fopen(ASSETS "/empty.fa", "r");
    NOTNULL(fd);

    struct fasta fa;
    fasta_init(&fa, fd, FASTA_READ);

    unsigned i = 0;
    enum fasta_rc rc = FASTA_SUCCESS;
    while (!(rc = fasta_read(&fa)))
    {
        i++;
    }
    EQ(i, 0);
    EQ(rc, FASTA_ENDFILE);

    fclose(fd);
}

static char *mix_id[] = {"LCBO", "MCHU", "gi|5524211|gb|AAD44166.1|",
                         "gi|5524211|gb|AAD44166.1|"};

static char *mix_desc[] = {
    "- Prolactin precursor - Bovine",
    "- Calmodulin - Human, rabbit, bovine, rat, and chicken",
    "cytochrome b [Elephas maximus maximus]",
    "cytochrome b [Elephas maximus maximus]"};

static char *mix_seq[] = {
    "MDSKGSSQKGSRLLLLLVVSNLLLCQGVVSTPVCPNGPGNCQVSLRDLFDRAVMVSHYI"
    "HDLSSEMFNEFDKRYAQGKGFITMALNSCHTSSLPTPEDKEQAQQTHHEVLMSLILGLL"
    "RSWNDPLYHLVTEVRGMKGAPDAILSRAIEIEEENKRLLEGMEMIFGQVIPGAKETEPY"
    "PVWSGLPSLQTKDEDARYSAFYNLLHCLRRDSSKIDTYLKLLNCRIIYNNNC",
    "MADQLTEEQIAEFKEAFSLFDKDGDGTITTKELGTVMRSLGQNPTEAELQDMINEVDAD"
    "GNGTIDFPEFLTMMARKMKDTDSEEEIREAFRVFDKDGNGYISAAELRHVMTNLGEKLT"
    "DEEVDEMIREADIDGDGQVNYEEFVQMMTAK*",
    "LCLYTHIGRNIYYGSYLYSETWNTGIMLLLITMATAFMGYVLPWGQMSFWGATVITNLFSAIPYIGTNLV"
    "EWIWGGFSVDKATLNRFFAFHFILPFTMVALAGVHLTFLHETGSNNPLGLTSDSDKIPFHPYYTIKDFLG"
    "LLILILLLLLLALLSPDMLGDPDNHMPADPLNTPLHIKPEWYFLFAYAILRSVPNKLGGVLALFLSIVIL"
    "GLMPFLHTSKHRSMMLRPLSQALFWTLTMDLLTLTWIGSQPVEYPYTIIGQMASILYFSIILAFLPIAGX"
    "IENY",
    "LCLYTHIGRNIYYGSYLYSETWNTGIMLLLITMATAFMGYVLPWGQMSFWGATVITNLFSAIPYIGT"};

void test_read_mix(void)
{
    FILE *fd = fopen(ASSETS "/mix.fa", "r");
    NOTNULL(fd);

    struct fasta fa;
    fasta_init(&fa, fd, FASTA_READ);

    unsigned i = 0;
    enum fasta_rc rc = FASTA_SUCCESS;
    while (!(rc = fasta_read(&fa)))
    {
        EQ(fa.target.id, mix_id[i]);
        EQ(fa.target.desc, mix_desc[i]);
        EQ(fa.target.seq, mix_seq[i]);
        i++;
    }
    EQ(i, 4);
    EQ(rc, FASTA_ENDFILE);

    fclose(fd);
}

void test_read_example(void)
{
    FILE *fd = fopen(ASSETS "/example.faa", "r");
    NOTNULL(fd);

    struct fasta fa;
    fasta_init(&fa, fd, FASTA_READ);

    unsigned i = 0;
    enum fasta_rc rc = FASTA_SUCCESS;
    while (!(rc = fasta_read(&fa)))
    {
        EQ(fa.target.id, "Homoserine_dh-consensus");
        EQ(fa.target.desc, "");
        EQ(fa.target.seq, "CCTATCATTCTTTCGACGT");
        i++;
    }
    EQ(i, 1);
    EQ(rc, FASTA_ENDFILE);

    fclose(fd);
}

void test_read_damaged1(void)
{
    FILE *fd = fopen(ASSETS "/damaged1.fa", "r");
    NOTNULL(fd);

    struct fasta fa;
    fasta_init(&fa, fd, FASTA_READ);

    unsigned i = 0;
    enum fasta_rc rc = FASTA_SUCCESS;
    while (!(rc = fasta_read(&fa)))
    {
        i++;
    }
    EQ(i, 0);
    EQ(rc, FASTA_PARSEERROR);
    EQ(fa.error, "Parse error: unexpected token: line 1");
    fasta_clearerr(&fa);
    EQ(fa.error, "");

    fclose(fd);
}

void test_read_damaged2(void)
{
    FILE *fd = fopen(ASSETS "/damaged2.fa", "r");
    NOTNULL(fd);

    struct fasta fa;
    fasta_init(&fa, fd, FASTA_READ);

    unsigned i = 0;
    enum fasta_rc rc = FASTA_SUCCESS;
    while (!(rc = fasta_read(&fa)))
    {
        i++;
    }
    EQ(i, 0);
    EQ(rc, FASTA_PARSEERROR);
    EQ(fa.error, "Parse error: unexpected id: line 2");
    fasta_clearerr(&fa);
    EQ(fa.error, "");

    fclose(fd);
}

void test_read_damaged3(void)
{
    FILE *fd = fopen(ASSETS "/damaged3.fa", "r");
    NOTNULL(fd);

    struct fasta fa;
    fasta_init(&fa, fd, FASTA_READ);

    unsigned i = 0;
    enum fasta_rc rc = FASTA_SUCCESS;
    while (!(rc = fasta_read(&fa)))
    {
        i++;
    }
    EQ(i, 0);
    EQ(rc, FASTA_PARSEERROR);
    EQ(fa.error, "Parse error: unexpected token: line 4");
    fasta_clearerr(&fa);
    EQ(fa.error, "");

    fclose(fd);
}
