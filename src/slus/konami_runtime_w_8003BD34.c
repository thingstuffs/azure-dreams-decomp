#include "common.h"

#include "common.h"

typedef struct {
    u32 word0;
    u32 word1;
    u32 word2;
    u32 word3;
} CopyBlock;

extern CopyBlock D_8006ADBC[3];
extern CopyBlock D_8006ADEC[3];

/* Copy three blocks from D_8006ADEC to D_8006ADBC. */
void func_8003BD34(void) {
    volatile CopyBlock *destination = D_8006ADBC;
    volatile CopyBlock *source = D_8006ADEC;
    volatile CopyBlock *source_end = source + 3;

    do {
        u32 word0 = source->word0;
        u32 word1 = source->word1;
        u32 word2 = source->word2;
        u32 word3 = source->word3;

        destination->word0 = word0;
        destination->word1 = word1;
        destination->word2 = word2;
        destination->word3 = word3;
        source++;
        destination++;
    } while (source != source_end);
}
