#include "common.h"

extern u8 D_800A79F0[12];

/* Initialize object data and mode, and set the primitive color to neutral gray. */
void func_800A79C8(void *object, void *unused, void *primitive) {
    *(void **)((s8 *)object + 0x50) = D_800A79F0;
    *(s16 *)((s8 *)object + 0x6C) = 0x16;
    *(u8 *)((s8 *)primitive + 0x0E) = 0x80;
    *(u8 *)((s8 *)primitive + 0x0D) = 0x80;
    *(u8 *)((s8 *)primitive + 0x0C) = 0x80;
}
