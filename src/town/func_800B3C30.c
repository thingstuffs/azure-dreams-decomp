#include "common.h"

extern s32 D_800B0824[];

/* Initialize the record values, active flag, and handler table. */
void func_800B1390(void *record_data, s32 value_20, s32 value_08, s32 value_0c, s32 value_10,
                   s32 value_14, s32 value_24, s32 value_18) {
    *(s32 *)((s8 *)record_data + 4) = 1;
    *(s32 *)((s8 *)record_data + 8) = value_08;
    *(s32 *)((s8 *)record_data + 0xC) = value_0c;
    *(s32 *)((s8 *)record_data + 0x20) = value_20;
    *(s32 **)((s8 *)record_data - 0x10) = D_800B0824;
    *(s32 *)((s8 *)record_data + 0x10) = value_10;
    *(s32 *)((s8 *)record_data + 0x14) = value_14;
    *(s32 *)((s8 *)record_data + 0x24) = value_24;
    *(s32 *)((s8 *)record_data + 0x18) = value_18;
}
