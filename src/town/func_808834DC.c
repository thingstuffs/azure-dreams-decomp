#include "common.h"

typedef struct CopyBlock {
    s32 words[4];
} CopyBlock;

extern u8 D_80700000[];

/* Copy 52 bytes from the source to the global buffer at offset 0xE34. */
void func_808834DC(CopyBlock *source) {
    CopyBlock *dst = (CopyBlock *)(D_80700000 + 0xE34);
    CopyBlock *src = source;
    CopyBlock *end = src + 3;

    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    dst->words[0] = src->words[0];
}
