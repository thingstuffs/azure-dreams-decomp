#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002017C_0_pre {
    u16 unk_00;
} S_8002017C_0_pre;   /* the 0x2 bytes before arg0 in func_8002017C, addressed as arg0[-1] */

typedef struct S_8002017C_0 {
    union { s16 s; volatile u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    void * unk_04;
    s32 unk_08;
    u8 pad_0C[0xA];
    u16 unk_16;
} S_8002017C_0;   /* arg0 in func_8002017C */

typedef struct S_8002017C_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8002017C_1;   /* sub in func_8002017C */


extern s32 D_800814A0;

/* Advance a delayed fade after the linked object signals, then flag completion. */
void func_8002017C(void *effect) {
    s16 state;
    s32 fade_rgb;
    u16 delay;
    void *linked_object;
    u16 state_snapshot;
    s16 next_state;
    u16 flags;

    linked_object = ((S_8002017C_0 *)effect)->unk_04;
    state = ((S_8002017C_0 *)effect)->unk_00.s;
    state_snapshot = ((S_8002017C_0 *)effect)->unk_00.u;
    switch (state) {
    case 0:
        delay = ((S_8002017C_0 *)effect)->unk_02 - 1;
        ((S_8002017C_0 *)effect)->unk_02 = delay;
        if ((delay << 0x10) <= 0) {
            flags = ((S_8002017C_0 *)effect)->unk_16;
            next_state = ((S_8002017C_0 *)effect)->unk_00.s;
            flags &= 0xFFFD;
            next_state = (s16) (next_state + 1);
            ((S_8002017C_0 *)effect)->unk_16 = flags;
            ((S_8002017C_0 *)effect)->unk_00.s = next_state;
            return;
        }
        return;
    case 1:
        if (((S_8002017C_1 *)linked_object)->unk_2A & 1) {
            do {
                ((S_8002017C_0 *)effect)->unk_00.s = (s16) (state_snapshot + 1);
            } while (0);
            return;
        }
        break;
    case 2:
        fade_rgb = ((S_8002017C_0 *)effect)->unk_08 + 0xFFF7F7F8;
        ((S_8002017C_0 *)effect)->unk_08 = fade_rgb;
        if (fade_rgb <= 0x80808) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_8002017C_0_pre *)effect)[-1].unk_00 | 0x8000);
            D_800814A0 |= 0x8000;
        }
        break;
    }
}
