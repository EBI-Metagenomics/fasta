#include "fasta/fasta.h"
#include "hope.h"

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

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

int main(void)
{
    FILE *fd = fopen(TMPDIR "/mix.fa", "w");
    NOTNULL(fd);

    struct fasta fa;
    fasta_init(&fa, fd, FASTA_WRITE);

    for (unsigned i = 0; i < ARRAY_SIZE(mix_id); ++i)
    {
        fasta_write(&fa, fasta_target(mix_id[i], mix_desc[i], mix_seq[i]), 60);
    }

    fclose(fd);

    FILE *actual = fopen(TMPDIR "/mix.fa", "r");
    FILE *desired = fopen(ASSETS "/desired_mix.fa", "r");
    NOTNULL(actual);
    NOTNULL(desired);
    EQ(actual, desired);
    fclose(desired);
    fclose(actual);

    return hope_status();
}
