#include "common.h"

typedef struct S_800A3918_0 {
    u16 unk_00;
    s16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { u16 s; s16 u; } unk_08;   /* accessed as both */
    u8 pad_0A[0x2];
    s16 unk_0C;
    u8 pad_0E[0x4];
    u16 unk_12;
    union { s16 s; u16 u; } unk_14;   /* accessed as both */
    s16 unk_16;
} S_800A3918_0;   /* arg0 in func_800A3918 */

typedef struct S_800A3918_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_800A3918_1;   /* D_8008274C in func_800A3918 */

typedef struct S_800A3918_2 {
    u8 pad_00[0xD8A];
    union { s16 s; u16 u; } unk_D8A;   /* accessed as both */
} S_800A3918_2;   /* base in func_800A3918 */



extern void *D_8008274C;
extern s32 D_800C5100;

/* Advances the animation phase and frame index, applying the state-one offset transition. */
void func_800A3918(S_800A3918_0 *anim, s32 unused) {
    s16 state;
    s32 phase;
    register u8 *global_base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 offset;
    u16 offset_bits;

    state = anim->unk_02;
    if (state == 0) {
        goto state_zero;
    }
    global_base = (u8 *)0x80100000;
    if (state == 1) {
        goto state_one;
    }
    goto finish;

state_zero:
    if (anim->unk_0C == 0) {
        phase = (s16)(anim->unk_08.s + 0x1BC0);
        anim->unk_06 += 2;
        phase %= 0x1C00;
    } else {
        phase = (s16)(anim->unk_08.s + 0x1B71);
        anim->unk_06 += 1;
        phase %= 0x1C00;
    }
    anim->unk_08.u = phase;
    do {
        anim->unk_00++;
    } while (0);
    if (((S_800A3918_1 *)D_8008274C)->unk_74 == &D_800C5100) {
        anim->unk_02 = 1;
    }
    goto finish;

state_one:
    ASM_KEEP_NV(global_base);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    offset = ((S_800A3918_2 *)global_base)->unk_D8A.s;
    offset_bits = ((S_800A3918_2 *)global_base)->unk_D8A.u;
    if (offset < -0x1FFF) {
        ((S_800A3918_2 *)global_base)->unk_D8A.s = -0x2000;
    } else {
        anim->unk_12 -= 0x20;
        offset = offset_bits + anim->unk_12;
        ((S_800A3918_2 *)global_base)->unk_D8A.s = offset;
        if (offset < -0x1FFF) {
            ((S_800A3918_2 *)global_base)->unk_D8A.s = -0x2000;
        }
    }
    if (anim->unk_14.s < 0x200) {
        anim->unk_14.s = anim->unk_14.u + 0x20;
    }
    if (anim->unk_0C == 0) {
        phase = (s16)(anim->unk_08.s + 0x1C00 - anim->unk_14.u);
        anim->unk_06 += 2;
        phase %= 0x1C00;
    } else {
        phase = (s16)(anim->unk_08.s + 0x1C00 - anim->unk_14.s * 2);
        anim->unk_06 += 1;
        phase %= 0x1C00;
    }
    anim->unk_08.u = phase;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    anim->unk_00++;

finish:
    anim->unk_16 = anim->unk_08.u / 0x200 + 0x10;
}
