#include "common.h"
#include "m2c_compat.h"

typedef struct S_800F62BC_0_pre {
    u16 unk_00;
} S_800F62BC_0_pre;   /* the 0x2 bytes before state in func_800F62BC, addressed as state[-1] */

typedef struct S_800F62BC_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    s16 unk_02;
    s16 unk_04;
} S_800F62BC_0;   /* state in func_800F62BC */

typedef struct S_800F62BC_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_800F62BC_1;   /* actor in func_800F62BC */


s32 func_800644B8();                             /* extern */
extern s32 D_800814A0;
extern u8 D_80173AF8;

/* Pulses the actor color, then fades it out and marks completion. */
void func_800F62BC(void *state_data, s32 unused, void *actor_data) {
    s16 fade_ticks;
    s32 pulse;
    s32 pulse_color;
    u8 fade_color;
    void *state = state_data;
    void *actor = actor_data;

    if (((S_800F62BC_0 *)state)->unk_00.s == 0) {
        pulse = func_800644B8(((S_800F62BC_0 *)state)->unk_04 << 7) >> 6;
        pulse_color = pulse + 0x80;
        do {
            pulse = (s32) (pulse << 0x10) >> 0x11;
        } while (0);
        pulse_color += pulse;
        ((S_800F62BC_1 *)actor)->unk_0D = pulse_color;
        ((S_800F62BC_1 *)actor)->unk_0E = pulse_color;
        ((S_800F62BC_1 *)actor)->unk_0C = pulse_color;
        if (D_80173AF8 != 0) {
            ((S_800F62BC_0 *)state)->unk_02 = 0x20;
            ((S_800F62BC_0 *)state)->unk_00.u = (u16) (((S_800F62BC_0 *)state)->unk_00.u + 1);
        }
    } else {
        fade_color = ((S_800F62BC_1 *)actor)->unk_0C;
        fade_color -= (s32) fade_color / ((S_800F62BC_0 *)state)->unk_02;
        ((S_800F62BC_1 *)actor)->unk_0C = fade_color;
        ((S_800F62BC_1 *)actor)->unk_0D = fade_color;
        ((S_800F62BC_1 *)actor)->unk_0E = fade_color;
        fade_ticks = (u16) ((S_800F62BC_0 *)state)->unk_02 - 1;
        ((S_800F62BC_0 *)state)->unk_02 = fade_ticks;
        if ((fade_ticks << 0x10) <= 0) {
            (*(u16 *)((u8 *)state + -2)) = (u16) (((S_800F62BC_0_pre *)state)[-1].unk_00 | 0x8000);
            D_800814A0 |= 0x8000;
        }
    }
    ((S_800F62BC_1 *)actor)->unk_1A = (u16) (((S_800F62BC_1 *)actor)->unk_1A + 0x40);
    ((S_800F62BC_0 *)state)->unk_04 = (s16) ((u16) ((S_800F62BC_0 *)state)->unk_04 + 1);
}
