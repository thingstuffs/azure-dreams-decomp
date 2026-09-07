#include "common.h"

extern s32 func_80049E6C(s32 kind);
extern u8 D_80077E84[];
extern u8 D_80077EF0[];
extern u8 D_80077EFC[];

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void func_800233D0(void *arg0)
{
    u8 *cursor;
    void *base4;
    void *source0;
    void *source1;
    s32 result;
    s32 index;
    s32 offset;

    result = func_80049E6C(3);
    index = 0;
    source0 = D_80077EF0;
    source1 = D_80077EFC;
    base4 = (u8 *)arg0 + 4;
    offset = 0x90;
    FIELD(FIELD(arg0, void *, 0x1A0), s32, 0) = result;
    FIELD(FIELD(arg0, void *, 0x1A4), void *, 0) = D_80077E84;
    cursor = arg0;
    do {
        FIELD(FIELD(cursor, void *, 0x1A8), void *, 0) = source0;
        FIELD(FIELD(cursor, void *, 0x1B8), void *, 0) = source1;
        FIELD(FIELD(cursor, void *, 0x1C8), void *, 0) = base4;
        FIELD(FIELD(cursor, void *, 0x1D8), void *, 0) = (u8 *)arg0 + offset;
        offset += 0x48;
        index++;
        cursor += 4;
    } while (index < 3);
}
