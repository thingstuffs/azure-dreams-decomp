/* Relinked copy of town/func_808834DC (func_808834DC.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/scene.h"

typedef struct CopyBlock {
    s32 words[4];
} CopyBlock;

extern u8 D_0000001C[];

/* Copy 52 bytes from the source to the global buffer at offset 0xE34. */
void copy_52_bytes_source_global(CopyBlock *source) {
    CopyBlock *dst = (CopyBlock *)(D_0000001C + 0xE34);
    CopyBlock *src = source;
    CopyBlock *end = src + 3;

    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    dst->words[0] = src->words[0];
}
