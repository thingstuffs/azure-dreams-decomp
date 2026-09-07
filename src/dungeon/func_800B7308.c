#include "common.h"

typedef struct S_8003E2D8 {
    u8 pad_000[0x1DC];
    u8 *table;
    u8 pad_1E0[0x10];
    s16 shift;
} S_8003E2D8;

extern S_8003E2D8 D_80083160;

s16 func_800BCA68(s32 arg0, s32 arg1) {
    S_8003E2D8 *base = &D_80083160;
    u32 index;
    u8 *entry;

    index = (((u32) (arg1 & 0xFFFF) >> 6) << base->shift) & 0xFFFF;
    index += (u32) (arg0 & 0xFFFF) >> 6;
    entry = (u8 *) ((u32) (index * 6) + (u32) base->table);
    if (*(u16 *) entry != 0) {
        return (s16) (0 - *(u16 *) (entry + 2));
    }
    return 0x400;
}
