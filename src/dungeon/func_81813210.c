#include "common.h"

extern u8 D_80027F34[];

/* Initialize the record handler, state, and a range spanning 0x20. */
void func_80028210(void *record, s32 range_start, s32 value) {
    *(s32 *)((u8 *)record + 0x44) = range_start;
    range_start += 0x20;
    *(s32 *)((u8 *)record + 0x04) = 4;
    *(s32 *)((u8 *)record + 0x48) = range_start;
    *(s32 *)((u8 *)record + 0x18) = value;
    *(s32 *)record = 0;
    *(u8 **)((u8 *)record - 0x10) = D_80027F34;
}
