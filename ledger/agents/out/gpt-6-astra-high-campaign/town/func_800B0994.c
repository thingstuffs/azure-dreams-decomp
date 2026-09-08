#include "common.h"

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Words;

extern s32 D_80082A38[];

/* Copy a global state word and a 17-word block into the record. */
void func_800AE0F4(s32 *record) {
    Words *src;
    register Words *dst ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (word_0 copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    Words *end;

    {
        s32 *base;

        dst = (Words *)(record + 0xD);
        base = D_80082A38;
        src = (Words *)(base + 0x32);
        record[0xC] = base[0x20];
        end = (Words *)(base + 0x42);
    }
    do {
        s32 word_0;
        s32 word_1;
        s32 word_2;
        s32 word_3;

        word_0 = src->a;
        word_1 = src->b;
        word_2 = src->c;
        word_3 = src->d;
        dst->a = word_0;
        dst->b = word_1;
        dst->c = word_2;
        dst->d = word_3;
        ASM_KEEP(src);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        src++;
        dst++;
    } while (src != end);
    dst->a = src->a;
}
