#include "common.h"
#include "shared/object_flags.h"

typedef struct S_80022514_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x4];
    s32 unk_08;
} S_80022514_0;   /* arg0 in func_80022514 */


/* Advances a timed color fade and sets completion flags at the final threshold. */
void func_80022514(void *effect) {
    s32 phase;
    s32 frames_left;
    u16 phase_value;
    s32 color;

    phase = ((S_80022514_0 *)effect)->unk_00.s;
    phase_value = ((S_80022514_0 *)effect)->unk_00.u;
    frames_left = ((S_80022514_0 *)effect)->unk_02.s - 1;
    ((S_80022514_0 *)effect)->unk_02.s = frames_left;
    switch (phase) {
    case 0:
        ((S_80022514_0 *)effect)->unk_08 += 0x40404;
        if (((S_80022514_0 *)effect)->unk_02.u < 0) {
            ((S_80022514_0 *)effect)->unk_02.s = 0x10E;
            ((S_80022514_0 *)effect)->unk_00.u++;
        }
        break;
    case 1:
        if ((s16)frames_left < 0) {
            ((S_80022514_0 *)effect)->unk_00.u = phase_value + 1;
        }
        break;
    case 2:
        color = ((S_80022514_0 *)effect)->unk_08 + 0xFFF7F7F8;
        ((S_80022514_0 *)effect)->unk_08 = color;
        if (color <= 0x80808) {
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        break;
    }
}
