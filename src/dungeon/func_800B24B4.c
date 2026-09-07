#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B7C14_0 {
    s32 unk_00;
    u8 pad_04[0x8];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
} S_800B7C14_0;   /* arg2 in func_800B7C14 */

typedef struct S_800B7C14_1_pre {
    u16 unk_00;
} S_800B7C14_1_pre;   /* the 0x2 bytes before arg0 in func_800B7C14, addressed as arg0[-1] */

typedef struct S_800B7C14_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u16 unk_16;
} S_800B7C14_1;   /* arg0 in func_800B7C14 */

typedef struct S_800B7C14_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B7C14_2;   /* arg1 in func_800B7C14 */


M2C_UNK func_8003DB94();        /* extern */
M2C_UNK func_800478B8();                      /* extern */
extern M2C_UNK D_800814A0;

void func_800B7C14(void *arg0, void *arg1, void *arg2) {
    s32 temp_v1;
    u16 temp_v0_3;
    u8 temp_v0;

    if (((S_800B7C14_0 *)arg2)->unk_00 != 0) {
        func_800478B8(arg2);
        if (((S_800B7C14_0 *)arg2)->unk_14 & 0x4000) {
            func_8003DB94(arg2, ((S_800B7C14_1 *)arg0)->unk_08, 0);
        }
    }
    ((S_800B7C14_2 *)arg1)->unk_00 = (s32) (((S_800B7C14_2 *)arg1)->unk_00 + ((S_800B7C14_2 *)arg1)->unk_0C);
    ((S_800B7C14_2 *)arg1)->unk_04 = (s32) (((S_800B7C14_2 *)arg1)->unk_04 + ((S_800B7C14_2 *)arg1)->unk_10);
    temp_v1 = ((S_800B7C14_2 *)arg1)->unk_0C;
    ((S_800B7C14_2 *)arg1)->unk_08 = (s32) (((S_800B7C14_2 *)arg1)->unk_08 + ((S_800B7C14_2 *)arg1)->unk_14);
    ((S_800B7C14_2 *)arg1)->unk_0C = (s32) (temp_v1 - (temp_v1 >> 4));
    ((S_800B7C14_2 *)arg1)->unk_10 = (s32) (((S_800B7C14_2 *)arg1)->unk_10 - (((S_800B7C14_2 *)arg1)->unk_10 >> 4));
    ((S_800B7C14_2 *)arg1)->unk_14 = (s32) (((S_800B7C14_2 *)arg1)->unk_14 + 0x40000);
    if (((S_800B7C14_1 *)arg0)->unk_12 != 0) {
        temp_v0 = ((S_800B7C14_0 *)arg2)->unk_0C;
        if (temp_v0 != 0) {
            temp_v0 -= 8;
            ((S_800B7C14_0 *)arg2)->unk_0C = temp_v0;
            ((S_800B7C14_0 *)arg2)->unk_0E = temp_v0;
            ((S_800B7C14_0 *)arg2)->unk_0D = temp_v0;
        }
    }
    ((S_800B7C14_0 *)arg2)->unk_16 = (u16) (((S_800B7C14_0 *)arg2)->unk_16 + ((S_800B7C14_1 *)arg0)->unk_14);
    ((S_800B7C14_0 *)arg2)->unk_18 = (u16) (((S_800B7C14_0 *)arg2)->unk_18 + ((S_800B7C14_1 *)arg0)->unk_16);
    temp_v0_3 = ((S_800B7C14_1 *)arg0)->unk_10 - 1;
    ((S_800B7C14_1 *)arg0)->unk_10 = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_800B7C14_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
}

/* MECHANISM: Natural argument lifetimes produce the 0x20 frame and s2/s1/s0 held pointers.
   Direct +0x10 field reuse preserves retail's load order and later $a1 damping lifetime.
   One in-place u8 temp gives the branch-delay subtract and three stores the same $v0.
   Direct scalar D_800814A0 RMW removes the extra address-add/displacement cascade. */
