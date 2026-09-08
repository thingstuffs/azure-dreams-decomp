#include "common.h"

extern s8 D_80082668[9];
extern s32 D_80097D2C[3];

/* Initialize the record from source fields, preserve its current value, and clear the global flag. */
void func_80098834(void *record, void *source) {
    u16 saved_value;
    u16 source_value;

    *(s32 *)((s8 *)record + 0) = (s32)&D_80097D2C[0];
    *(u16 *)((s8 *)record + 0x30) = *(u16 *)((s8 *)source + 2);
    saved_value = *(u16 *)((s8 *)record + 0x10);
    source_value = *(u16 *)((s8 *)source + 6);
    *(u16 *)((s8 *)record + 0x0e) = saved_value;
    *(u16 *)((s8 *)record + 0x32) = source_value;
    D_80082668[0] = 0;
}
