#include "common.h"

typedef struct CopyBlock {
    s32 words[4];
} CopyBlock;

extern u8 D_80700000[];

void func_808834DC(CopyBlock *arg0) {
    CopyBlock *dst = (CopyBlock *)(D_80700000 + 0xE34);
    CopyBlock *src = arg0;
    CopyBlock *end = src + 3;

    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    dst->words[0] = src->words[0];
}
