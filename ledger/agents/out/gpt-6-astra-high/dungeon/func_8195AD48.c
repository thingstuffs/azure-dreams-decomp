#include "common.h"

extern void func_80065820(void *, void *);
extern void func_80064BC0(void *, s32 *);

/* Initializes the destination from the source position and signed vector components. */
void func_8195AD48(void *dest, void *source) {
    s32 position[3];

    func_80065820(source, dest);
    position[0] = *(s16 *)((u8 *)source + 0x10);
    position[1] = *(s16 *)((u8 *)source + 0x12);
    position[2] = *(s16 *)((u8 *)source + 0x14);
    func_80064BC0(dest, position);
    *(s32 *)((u8 *)dest + 0x14) = *(s16 *)((u8 *)source + 8);
    *(s32 *)((u8 *)dest + 0x18) = *(s16 *)((u8 *)source + 0xA);
    *(s32 *)((u8 *)dest + 0x1C) = *(s16 *)((u8 *)source + 0xC);
}
