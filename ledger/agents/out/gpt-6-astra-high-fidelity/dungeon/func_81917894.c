#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80024E80_arg1.h"

M2C_UNK func_80024E80();              /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern s32 D_800814A0;


typedef struct S_80025094_0_pre {
    u16 unk_00;
} S_80025094_0_pre;   /* the 0x2 bytes before arg0 in func_80025094, addressed as arg0[-1] */

typedef struct S_80025094_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    s16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
} S_80025094_0;   /* arg0 in func_80025094 */

typedef struct S_80025094_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80025094_1;   /* temp_v1 in func_80025094 */



void func_80025094(void *arg0, void *arg1, void *arg2) {
    s32 temp_v0_2;
    s16 temp_v1_2;
    u8 temp_v0;
    void *temp_v1;

    temp_v1 = ((S_80025094_0 *)arg0)->unk_00;
    ((S_80025094_1 *)temp_v1)->unk_14 = (u16) (((S_80025094_1 *)temp_v1)->unk_14 + 1);
    func_800478B8(arg2);
    ((S_80025094_0 *)arg0)->unk_06.u = (u16) (((S_80025094_0 *)arg0)->unk_06.u + 1);
    ((Rec_D_80082E80 *)arg2)->unk_1A.as_u16 = (u16) (((Rec_D_80082E80 *)arg2)->unk_1A.as_u16 + 0x200);
    temp_v1_2 = ((S_80025094_0 *)arg0)->unk_04.s;

    if (temp_v1_2 == 1) {
        goto state_1;
    }
    if (temp_v1_2 < 2) {
        if (temp_v1_2 == 0) {
            goto state_0;
        }
        goto common;
    }
    if (temp_v1_2 == 2) {
        goto state_2;
    }
    goto common;

state_0:
    {
        u16 tail_value;

        if (((S_80025094_0 *)arg0)->unk_06.u & 1) {
            tail_value = ((S_80025094_0 *)arg0)->unk_0A + 2;
        } else {
            tail_value = ((S_80025094_0 *)arg0)->unk_0A + 1;
        }
        ((S_80025094_0 *)arg0)->unk_0A = tail_value;
    }
    temp_v0 = ((Rec_D_80082E80 *)arg2)->unk_0C.at02_u8.v + 3;
    ((Rec_D_80082E80 *)arg2)->unk_0C.at02_u8.v = temp_v0;
    ((Rec_D_80082E80 *)arg2)->unk_0C.at01_u8.v = temp_v0;
    ((Rec_D_80082E80 *)arg2)->unk_0C.at00_u8.v = temp_v0;
    temp_v0_2 = ((S_80025094_0 *)arg0)->unk_06.s << 5;
    ((Rec_D_80082E80 *)arg2)->unk_1C.at02_s16.v = temp_v0_2;
    ((Rec_D_80082E80 *)arg2)->unk_1C.at00_s16.v = temp_v0_2;
    ((Rec_func_80024E80_arg1 *)arg1)->unk_08.at02_u16.v =
        (u16) (((Rec_func_80024E80_arg1 *)arg1)->unk_08.at02_u16.v - 2);

state_1:
    if ((s16) ((S_80025094_0 *)arg0)->unk_06.u >= 0x20) {
        ((S_80025094_0 *)arg0)->unk_06.u = 0U;
        ((S_80025094_0 *)arg0)->unk_04.u =
            (u16) (((S_80025094_0 *)arg0)->unk_04.u + 1);
        goto common;
    }
    goto common;

state_2:
    if ((s16) ((S_80025094_0 *)arg0)->unk_06.u >=
            ((S_80025094_0 *)arg0)->unk_08) {
        func_80024E80(arg0, arg1);
        (*(u16 *)((u8 *)arg0 + (-2))) =
            (u16) (((S_80025094_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
        return;
    }

common:
    ((Rec_func_80024E80_arg1 *)arg1)->unk_00.at02_s16.v = (s16) (((Rec_func_80024E80_arg1 *)arg1)->unk_0E + ((s32) ((func_80064584(((S_80025094_0 *)arg0)->unk_0C) >> 4) * (s16) ((S_80025094_0 *)arg0)->unk_0A) >> 8));
    ((Rec_func_80024E80_arg1 *)arg1)->unk_04.at02_s16.v = (s16) (((Rec_func_80024E80_arg1 *)arg1)->unk_12 + ((s32) ((func_800644B8(((S_80025094_0 *)arg0)->unk_0C) >> 4) * (s16) ((S_80025094_0 *)arg0)->unk_0A) >> 8));
}

/* MECHANISM: Explicit invalid-state predecessors plus a one-sided scheduling barrier
   prevent GCC from merging retail's two dispatcher tails. A guarded $v0 tail-slot pin
   preserves the hidden +2 continuation value; an s32 scale temp forces the signed lh. */
