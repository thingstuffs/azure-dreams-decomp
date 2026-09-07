#include "common.h"

typedef struct S_8017573C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    s16 unk_04;
} S_8017573C_0;   /* arg0 in func_8017573C */

typedef struct S_8017573C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8017573C_1;   /* arg2 in func_8017573C */



extern void func_80047784(void *, u8, s32);
extern void func_800478B8(void *);
extern s16 D_80083228;
extern u8 D_80176460[8];

/* Updates object direction and grows it to full scale after an eight-tick delay. */
void func_8017573C(S_8017573C_0 *animation, s32 unused, S_8017573C_1 *object) {
    s32 direction_index;
    s16 phase;
    u16 phase_u;
    u16 scale;

    animation->unk_02.s = animation->unk_02.s + 1;
    func_800478B8(object);
    if (object->unk_14 & 0x6000) {
        direction_index = D_80083228;
        direction_index += animation->unk_04;
        direction_index += 0x100;
        direction_index >>= 9;
        direction_index &= 7;
        func_80047784(object, D_80176460[direction_index], 0);
    }

    phase = animation->unk_00.s;
    phase_u = animation->unk_00.u;
    if (phase == 1) {
        goto grow;
    }
    if (phase >= 2) {
        goto done;
    }
    if (phase != 0) {
        goto done;
    }
    if (animation->unk_02.u < 8) {
        goto done;
    }
    animation->unk_00.u = phase_u + 1;
    goto done;

grow:
    scale = object->unk_1E + 0x100;
    object->unk_1E = scale;
    object->unk_1C = scale;
    if ((u16)scale >= 0x1000U) {
        goto clamp;
    }
    if (object->unk_1E < 0x1000U) {
        goto done;
    }

clamp:
    object->unk_1E = 0x1000;
    object->unk_1C = 0x1000;
    animation->unk_00.u = animation->unk_00.u + 1;

done:
    return;
}
