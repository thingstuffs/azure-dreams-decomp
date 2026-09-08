#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800DB164_0_pre {
    u16 unk_00;
} S_800DB164_0_pre;   /* the 0x2 bytes before arg0 in func_800DB164, addressed as arg0[-1] */

typedef struct S_800DB164_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x36];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_800DB164_0;   /* arg0 in func_800DB164 */


typedef struct S_800DB164_2 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800DB164_2;   /* arg1 in func_800DB164 */


M2C_UNK func_800478B8();                      /* extern */
s32 rand();                             /* extern */
extern s32 D_800814A0;

/* Updates a timed effect's animation and motion, marking it for removal when finished. */
void func_800DB164(void *effect, void *motion, void *visual) {
    s16 phase;
    s32 ticks_left;
    s32 next_phase;

    phase = ((S_800DB164_0 *)effect)->unk_4C.s;
    ticks_left = ((S_800DB164_0 *)effect)->unk_48 - 1;
    ((S_800DB164_0 *)effect)->unk_48 = ticks_left;
    if (phase == 1) {
        goto case_1;
    }
    if (phase >= 2) {
        goto check_2;
    }
    if (phase == 0) {
        goto case_0;
    }
    goto update_motion;

check_2:
    if (phase == 2) {
        goto case_2;
    }
    goto update_motion;

case_0:
    ((Rec_D_80082E80 *)visual)->unk_1C.at00_u16.v = (u16) (((Rec_D_80082E80 *)visual)->unk_1C.at00_u16.v - ((rand(ticks_left) & 0xFF) + 0x300));
    ((Rec_D_80082E80 *)visual)->unk_1C.at02_u16.v = (u16) (((Rec_D_80082E80 *)visual)->unk_1C.at02_u16.v + ((rand() & 0xFF) + 0x200));
    if ((s16) ((S_800DB164_0 *)effect)->unk_48 > 0) {
        goto update_motion;
    }
    next_phase = ((S_800DB164_0 *)effect)->unk_4C.u + 1;
    goto advance_phase;

case_1:
    ((Rec_D_80082E80 *)visual)->unk_0C.at00_s32.v = (s32) (((Rec_D_80082E80 *)visual)->unk_0C.at00_s32.v + 0xFFF3F3F4);
    ((S_800DB164_2 *)motion)->unk_14 = (s32) (((S_800DB164_2 *)motion)->unk_14 - ((rand(ticks_left) & 0xFF) << 0xA));
    if (((S_800DB164_2 *)motion)->unk_08.at02.v < ((S_800DB164_0 *)effect)->unk_10) {
        phase = 4;
        ((S_800DB164_0 *)effect)->unk_48 = phase;
        next_phase = ((S_800DB164_0 *)effect)->unk_4C.u + 1;
        goto advance_phase;
    }

    goto update_motion;

advance_phase:
    ((S_800DB164_0 *)effect)->unk_4C.u = next_phase;
    goto update_motion;

case_2:
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800DB164_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }

update_motion:
    if (((S_800DB164_0 *)effect)->unk_4C.s != 0) {
        ((S_800DB164_2 *)motion)->unk_08.at00.v = (s32) (((S_800DB164_2 *)motion)->unk_08.at00.v + ((S_800DB164_2 *)motion)->unk_14);
        func_800478B8(visual);
    }
}
