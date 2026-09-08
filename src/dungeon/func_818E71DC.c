#include "common.h"
#include "records/Rec_func_800249DC_arg0.h"


extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];


typedef struct S_800249DC_0_pre {
    u16 unk_00;
} S_800249DC_0_pre;   /* the 0x2 bytes before arg0 in func_800249DC, addressed as arg0[-1] */


typedef struct S_800249DC_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800249DC_1;   /* temp_ptr in func_800249DC */

typedef struct S_800249DC_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800249DC_2;   /* arg1 in func_800249DC */

typedef struct S_800249DC_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x6];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    u16 unk_14;
} S_800249DC_3;   /* arg2 in func_800249DC */

/* Advance the target, ease the position toward it, and update visual brightness and flags. */
void func_800249DC(void *motion, S_800249DC_2 *position, S_800249DC_3 *visual) {
    s32 current_x;
    s32 current_y;
    s32 current_z;
    s32 delta;
    u16 ticks_left;
    S_800249DC_1 *owner;

    owner = ((Rec_func_800249DC_arg0 *)motion)->unk_00.at00_pv.v;
    owner->unk_10 =
        (s32)(owner->unk_10 | 0x8000);

    ticks_left = ((Rec_func_800249DC_arg0 *)motion)->unk_48 - 1;
    ((Rec_func_800249DC_arg0 *)motion)->unk_48 = ticks_left;
    if ((ticks_left << 16) > 0) {
        ((Rec_func_800249DC_arg0 *)motion)->unk_1C =
            (s32)(((Rec_func_800249DC_arg0 *)motion)->unk_1C + ((Rec_func_800249DC_arg0 *)motion)->unk_34);
        ((Rec_func_800249DC_arg0 *)motion)->unk_20 =
            (s32)(((Rec_func_800249DC_arg0 *)motion)->unk_20 + ((Rec_func_800249DC_arg0 *)motion)->unk_38);
        ((Rec_func_800249DC_arg0 *)motion)->unk_24 =
            (s32)(((Rec_func_800249DC_arg0 *)motion)->unk_24 + ((Rec_func_800249DC_arg0 *)motion)->unk_3C);
    }

    delta = ((Rec_func_800249DC_arg0 *)motion)->unk_1C;
    current_x = position->unk_00;
    delta -= current_x;
    position->unk_00 =
        (s32)(current_x + (delta / 5));
    delta = ((Rec_func_800249DC_arg0 *)motion)->unk_20;
    current_y = position->unk_04;
    delta -= current_y;
    position->unk_04 =
        (s32)(current_y + (delta / 5));
    delta = ((Rec_func_800249DC_arg0 *)motion)->unk_24;
    current_z = position->unk_08;
    delta -= current_z;
    position->unk_08 =
        (s32)(current_z + (delta / 5));

    func_800478B8(visual);
    if (visual->unk_14 & 0x6000) {
        visual->unk_04 = 0;
        visual->unk_05 = 0;
    }

    if ((u8)visual->unk_0C.u8 >= 0x60U) {
        ((S_800249DC_0_pre *)motion)[-1].unk_00 =
            (u16)(((S_800249DC_0_pre *)motion)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
        return;
    }

    visual->unk_0C.s32 += 0xC0C0C;
}
