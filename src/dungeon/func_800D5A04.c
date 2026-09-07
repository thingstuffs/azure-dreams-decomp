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

void func_800DB164(void *arg0, void *arg1, void *arg2) {
    s16 temp_v1;
    s32 temp_a0;
    s32 temp_v0;

    temp_v1 = ((S_800DB164_0 *)arg0)->unk_4C.s;
    temp_a0 = ((S_800DB164_0 *)arg0)->unk_48 - 1;
    ((S_800DB164_0 *)arg0)->unk_48 = temp_a0;
    if (temp_v1 == 1) {
        goto case_1;
    }
    if (temp_v1 >= 2) {
        goto check_2;
    }
    if (temp_v1 == 0) {
        goto case_0;
    }
    goto block_16;

check_2:
    if (temp_v1 == 2) {
        goto case_2;
    }
    goto block_16;

case_0:
    ((Rec_D_80082E80 *)arg2)->unk_1C.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_1C.at00_u16.v - ((rand(temp_a0) & 0xFF) + 0x300));
    ((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v + ((rand() & 0xFF) + 0x200));
    if ((s16) ((S_800DB164_0 *)arg0)->unk_48 > 0) {
        goto block_16;
    }
    temp_v0 = ((S_800DB164_0 *)arg0)->unk_4C.u + 1;
    goto store_increment;

case_1:
    ((Rec_D_80082E80 *)arg2)->unk_0C.at00_s32.v = (s32) (((Rec_D_80082E80 *)arg2)->unk_0C.at00_s32.v + 0xFFF3F3F4);
    ((S_800DB164_2 *)arg1)->unk_14 = (s32) (((S_800DB164_2 *)arg1)->unk_14 - ((rand(temp_a0) & 0xFF) << 0xA));
    if (((S_800DB164_2 *)arg1)->unk_08.at02.v < ((S_800DB164_0 *)arg0)->unk_10) {
        temp_v1 = 4;
        ((S_800DB164_0 *)arg0)->unk_48 = temp_v1;
        temp_v0 = ((S_800DB164_0 *)arg0)->unk_4C.u + 1;
        goto store_increment;
    }

    goto block_16;

store_increment:
    ((S_800DB164_0 *)arg0)->unk_4C.u = temp_v0;
    goto block_16;

case_2:
    if ((temp_a0 << 0x10) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_800DB164_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }

block_16:
    if (((S_800DB164_0 *)arg0)->unk_4C.s != 0) {
        ((S_800DB164_2 *)arg1)->unk_08.at00.v = (s32) (((S_800DB164_2 *)arg1)->unk_08.at00.v + ((S_800DB164_2 *)arg1)->unk_14);
        func_800478B8(arg2);
    }
}

/* MECHANISM: The true-space function uses three held argument bases and local CFG joins at
   800DB268/800DB298; restoring the shared increment/store join made the 94-word shape exact.
   Reusing the selector local for constant 4 colored it v1 and preserved the increment in v0. */
