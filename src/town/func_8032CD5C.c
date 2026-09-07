#include "common.h"

typedef struct {
    s32 words[4];
} PackedWord;

extern PackedWord D_80016024;
extern s32 func_8001ADE0(s32);
extern s32 func_8001B0E8(s32, s32);
extern void func_8001B168(s32, s32, s32);

s32 func_8001755C(void)
{
    PackedWord values;
    s32 index;

    values = D_80016024;
    index = func_8001B0E8(0xD6E, 2);
    if (func_8001ADE0(0xDB0) == 0) {
        index++;
        if (index == 4) {
            index = 0;
        }
        func_8001B168(0xD6E, index, 2);
    }
    return values.words[index];
}

/* MECHANISM: A four-word sibling frame object forces the retail 0x28 frame and
   copy into stack slots 0x10..0x1c with the retail aggregate-copy ordering.
   One live index occupies s0 and wraps only on the failed 0xDB0 test. */
