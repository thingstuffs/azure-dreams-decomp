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

void func_8003BD34(void) {
    volatile CopyBlock *dst = D_8006ADBC;
    volatile CopyBlock *src = D_8006ADEC;
    volatile CopyBlock *end = src + 3;

    do {
        u32 word0 = src->word0;
        u32 word1 = src->word1;
        u32 word2 = src->word2;
        u32 word3 = src->word3;

        dst->word0 = word0;
        dst->word1 = word1;
        dst->word2 = word2;
        dst->word3 = word3;
        src++;
        dst++;
    } while (src != end);
}
