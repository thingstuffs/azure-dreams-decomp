#include "common.h"

typedef struct S_80022514_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x4];
    s32 unk_08;
} S_80022514_0;   /* arg0 in func_80022514 */



extern s32 D_800814A0;

/* Advances a timed color fade and sets completion flags at the final threshold. */
void func_80022514(void *effect) {
    s16 phase;
    s32 color_step;
    s32 frames_left;
    s32 phase_value;

    phase = ((S_80022514_0 *)effect)->unk_00.s;
    phase_value = ((S_80022514_0 *)effect)->unk_00.u;
    frames_left = ((S_80022514_0 *)effect)->unk_02.s - 1;
    ((S_80022514_0 *)effect)->unk_02.s = frames_left;
    if (phase == 1) {
        goto mode_one;
    }
    if (phase < 2) {
        color_step = 0x40000;
        if (phase == 0) {
            goto mode_zero;
        }
        goto done;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (phase == 2) {
        goto mode_two;
    }
    goto done;

mode_zero:
{
    s32 countdown;
    s32 next_phase;
    s32 color;

    color_step |= 0x404;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    color = ((S_80022514_0 *)effect)->unk_08;
    countdown = ((S_80022514_0 *)effect)->unk_02.u;
    color += color_step;
    ((S_80022514_0 *)effect)->unk_08 = color;
    if (countdown >= 0) {
        goto done;
    }
    next_phase = ((S_80022514_0 *)effect)->unk_00.u;
    ((S_80022514_0 *)effect)->unk_02.s = 0x10E;
    next_phase++;
    ((S_80022514_0 *)effect)->unk_00.u = next_phase;
    goto done;
}

mode_one:
{
    if ((s16)frames_left >= 0) {
        goto done;
    }
    {
        s32 next_phase;

        do {
            next_phase = phase_value + 1;
        } while (0);
        ((S_80022514_0 *)effect)->unk_00.u = next_phase;
    }
    goto done;
}

mode_two:
{
    s32 fade_step;
    s32 color;

    fade_step = 0xFFF7F7F8;
    color = ((S_80022514_0 *)effect)->unk_08 + fade_step;
    ((S_80022514_0 *)effect)->unk_08 = color;
    if (color <= 0x80808) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

done:
    ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    return;
}
