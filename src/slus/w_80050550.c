#include "common.h"

typedef struct S_80050550_A {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3[9];
    /* 0x0C */ s16 unkC;
} S_80050550_A;

typedef struct S_80050550_B {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ s16 unk2;
} S_80050550_B;

typedef struct S_80050550_Outer {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ S_80050550_A *fieldA;
    /* 0x08 */ S_80050550_B *fieldB;
} S_80050550_Outer;

/* Computes lighting/palette-ratio values: scales a1 by fixed constants (80/128/1024),
 * divides each by a2, and writes the results into two output structs via pointers
 * held at offset 4 and offset 8 of the input struct. */
void func_80050550(S_80050550_Outer *a0, s32 a1, s32 a2) {
    register s32 v0 ASM_REG("v0") = (a1 * 80) / a2;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 a3 = (-(a1 * 128)) / a2;
    s32 a1v = (a1 * 1024) / a2;

    register S_80050550_A *p ASM_REG("v1");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */

    v0 = v0 + 0x30;
    p = a0->fieldA;
    p->unk2 = (u8)v0;
    p->unk1 = (u8)v0;
    p->unk0 = (u8)v0;

    v0 = 0x180;
    p = a0->fieldA;
    v0 = v0 - a3;
    p->unkC = v0;

    v0 = 0x400;
    v0 = v0 - a1v;
    a0->fieldB->unk2 = v0;
}
