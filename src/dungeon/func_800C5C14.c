#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8();                      /* extern */
typedef struct { s32 v; s32 pad[2]; } S_800814A0;
extern S_800814A0 D_800814A0;


typedef struct S_800CB374_0_pre {
    u16 unk_00;
} S_800CB374_0_pre;   /* the 0x2 bytes before arg0 in func_800CB374, addressed as arg0[-1] */

typedef struct S_800CB374_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
    u8 pad_AC[0x8];
    s16 unk_B4;
} S_800CB374_0;   /* arg0 in func_800CB374 */

typedef struct S_800CB374_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xC];
    u16 unk_1C;
    u16 unk_1E;
} S_800CB374_1;   /* arg2 in func_800CB374 */

typedef struct S_800CB374_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800CB374_2;   /* temp_v1 in func_800CB374 */

typedef struct S_800CB374_3 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
    u8 pad_20[0xAC];
    s32 unk_CC;
} S_800CB374_3;   /* ((S_800CB374_0 *)arg0)->unk_A8 in func_800CB374 */

void func_800CB374(void *arg0, void *arg1, S_800CB374_1 *arg2) {
    s16 temp_v0;
    u8 temp_a0;
    S_800CB374_2 *temp_v1;

    func_800478B8(arg2);
    if (((S_800CB374_0 *)arg0)->unk_B4 != 0) {
        arg2->unk_0C.at00.v = (u8) (arg2->unk_0C.at00.v - ((s32) arg2->unk_0C.at00.v / (s16) ((S_800CB374_0 *)arg0)->unk_96));
        arg2->unk_0C.at01.v = (u8) (arg2->unk_0C.at01.v - ((s32) arg2->unk_0C.at01.v / (s16) ((S_800CB374_0 *)arg0)->unk_96));
        temp_a0 = arg2->unk_0C.at02.v - ((s32) arg2->unk_0C.at02.v / (s16) ((S_800CB374_0 *)arg0)->unk_96);
        arg2->unk_0C.at02.v = temp_a0;
        arg2->unk_06 = (u16) (arg2->unk_06 - 1);
        temp_v0 = (u16) ((S_800CB374_0 *)arg0)->unk_96 - 1;
        ((S_800CB374_0 *)arg0)->unk_96 = temp_v0;
        if ((temp_v0 << 0x10) > 0) {
            return;
        }
        goto block_5;
    }
    arg2->unk_0C.at00u.v = ((S_800CB374_3 *)(((S_800CB374_0 *)arg0)->unk_A8))->unk_CC;
    temp_v1 = ((S_800CB374_3 *)(((S_800CB374_0 *)arg0)->unk_A8))->unk_0C;
    arg2->unk_1C = (u16) temp_v1->unk_1C;
    arg2->unk_1E = (u16) temp_v1->unk_1E;
    if (((S_800CB374_3 *)(((S_800CB374_0 *)arg0)->unk_A8))->unk_1E & 0x8000) {
block_5:
        ((S_800CB374_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800CB374_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0.v |= 0x8000;
    }
}

/* MECHANISM: The 0x20 frame naturally holds arg0 in s1 and arg2 in s0 across the call.
   A zero-argument tail call and 32-bit fallback copy restore the retail ABI and widths.
   Ordering the +6 halfword decrement after all byte reductions closes the one-word cascade. */
