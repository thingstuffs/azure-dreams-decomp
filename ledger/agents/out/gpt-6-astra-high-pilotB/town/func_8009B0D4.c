#include "common.h"

extern s8 D_80082668[9];
extern s32 D_80097D2C[3];

/* Initializes object fields from source data and clears the shared flag. */
void func_80098834(void *object, void *source) {
    u16 object_field_10;
    u16 source_field_06;

    *(s32 *)((s8 *)object + 0) = (s32)&D_80097D2C[0];
    *(u16 *)((s8 *)object + 0x30) = *(u16 *)((s8 *)source + 2);
    object_field_10 = *(u16 *)((s8 *)object + 0x10);
    source_field_06 = *(u16 *)((s8 *)source + 6);
    *(u16 *)((s8 *)object + 0x0e) = object_field_10;
    *(u16 *)((s8 *)object + 0x32) = source_field_06;
    D_80082668[0] = 0;
}
