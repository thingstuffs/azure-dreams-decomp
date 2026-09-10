#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_80026E3C_0_pre {
    u16 unk_00;
} S_80026E3C_0_pre;   /* the 0x2 bytes before arg0 in func_80026E3C, addressed as arg0[-1] */

typedef struct S_80026E3C_0 {
    u8 pad_00[0x66];
    u16 unk_66;
    u16 unk_68;
    union { u8 u8; u16 u16; } unk_6A;   /* accessed as both */
} S_80026E3C_0;   /* arg0 in func_80026E3C */

typedef struct S_80026E3C_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80026E3C_1;   /* arg2 in func_80026E3C */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_800814A0[3];

/* Alternate the effect shade, decay its intensity, and flag expiration. */
void func_80026E3C(void *effect, M2C_UNK unused, S_80026E3C_1 *color)
{
    register u16 ticks_left ASM_REG("$4");
    u16 frame;
    u16 intensity;
    u32 shade;
    s32 decay;

    frame = ((S_80026E3C_0 *)effect)->unk_68 + 1;
    ((S_80026E3C_0 *)effect)->unk_68 = frame;
    if (frame & 1) {
        shade = ((S_80026E3C_0 *)effect)->unk_6A.u8;
    } else {
        shade = ((S_80026E3C_0 *)effect)->unk_6A.u16 >> 3;
    }
    color->unk_0E = (s8) shade;
    color->unk_0D = (s8) shade;
    color->unk_0C = (s8) shade;
    intensity = ((S_80026E3C_0 *)effect)->unk_6A.u16;
    decay = (s16)intensity >> 4;
    ticks_left = ((S_80026E3C_0 *)effect)->unk_66;
    do {
        intensity -= decay;
    } while (0);
    ticks_left--;
    ((S_80026E3C_0 *)effect)->unk_66 = ticks_left;
    ((S_80026E3C_0 *)effect)->unk_6A.u16 = intensity;
    if ((ticks_left << 0x10) <= 0) {
        ((S_80026E3C_0_pre *)effect)[-1].unk_00 =
            (u16)(((S_80026E3C_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}
