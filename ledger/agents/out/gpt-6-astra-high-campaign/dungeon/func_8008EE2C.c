#include "common.h"

extern void *D_800E3D7C[];

/* Set the indexed object value and its mirrored table entry. */
void func_8009458C(s16 object_index, s8 value) {
    u8 *table_address;
    s32 object_offset = object_index * 4;
    void *object = *(void **)(object_offset + 0xAC + (u8 *)D_800E3D7C[0]);
    *(s8 *)((u8 *)object + 0x12) = value;

    table_address = (u8 *)0x80010000 + (object_index * 2);
    *(s16 *)(table_address + 0x2098) = value & 0xFF;
}
