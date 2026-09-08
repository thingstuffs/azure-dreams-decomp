#include "common.h"

extern u8 D_800D162C[];

/* Store the table index and its two byte values in the object. */
void func_800B2394(void *object, s32 index) {
    u8 *table;
    u8 *entry;

    table = D_800D162C;
    *(s32 *)((s8 *) object + 0xC) = index;
    entry = table + index * 2;
    *(s32 *)((s8 *) object + 0x14) = entry[0];
    *(s32 *)((s8 *) object + 0x18) = entry[1];
}
