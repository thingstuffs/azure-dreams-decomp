#include "common.h"

typedef struct {
    /* 0x0 */ s8 unk0;
    /* 0x1 */ s8 pad1;
    /* 0x2 */ s8 unk2;
    /* 0x3 */ s8 pad2[9];
} S_8004A10C; /* size 0xC */

extern s32 func_8004B4DC(S_8004A10C *a0);

/* Returns the first flagged entry's signed byte at offset 2 plus 0x80, or zero for NULL. */
s16 func_8004A10C(S_8004A10C *entries) {
    s32 entry_index;
    s8 entry_value;

    if (entries == 0) {
        return 0;
    }
    entry_index = func_8004B4DC(entries);
    entry_value = ((s8 *)entries)[entry_index * 12 - 10];
    return entry_value + 0x80;
}
