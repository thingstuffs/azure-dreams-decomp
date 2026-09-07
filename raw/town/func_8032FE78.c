#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern u8 *D_80016000;

void func_8001A678(s32 unused, u32 arg1, u32 arg2)
{
    u8 *root = D_80016000;
    void *entry_ptr;
    void *position;
    u32 index;
    s32 value1;
    s32 value2;

    entry_ptr = FIELD(root, void *, 0x30);
    index = FIELD(root, u32, 8);
    do {
        index <<= 5;
    } while (0);
    do {
        entry_ptr = FIELD(entry_ptr, void *, 0);
    } while (0);
    index += (u32)entry_ptr;
    position = FIELD(root, void *, 0x1C);
    do {
        arg1 <<= 6;
    } while (0);
    value1 = FIELD((void *)index, s16, 0xC);
    value1 += 0x20;
    arg1 += value1;
    FIELD(position, s32, 4) = arg1;
    root = FIELD(root, void *, 0x1C);
    do {
        arg2 <<= 6;
    } while (0);
    value2 = FIELD((void *)index, s16, 0xE);
    value2 += 0x20;
    arg2 += value2;
    FIELD(root, s32, 8) = arg2;
}
