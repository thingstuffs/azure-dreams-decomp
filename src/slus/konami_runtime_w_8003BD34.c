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
    CopyBlock *destination = D_8006ADBC;
    CopyBlock *source = D_8006ADEC;
    CopyBlock *source_end = source + 3;

    do {
        *destination = *source;
        source++;
        destination++;
    } while (source != source_end);
}
