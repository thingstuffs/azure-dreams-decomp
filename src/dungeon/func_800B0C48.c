#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B63A8_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B63A8_0;   /* arg1 in func_800B63A8 */

typedef struct S_800B63A8_1_pre {
    u16 unk_00;
} S_800B63A8_1_pre;   /* the 0x2 bytes before arg0 in func_800B63A8, addressed as arg0[-1] */

typedef struct S_800B63A8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x2];
    u16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    u8 unk_14;
    u8 pad_15[0x1];
    u8 unk_16;
    u8 pad_17[0x1];
    u8 unk_18;
} S_800B63A8_1;   /* arg0 in func_800B63A8 */

typedef struct S_800B63A8_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800B63A8_2;   /* arg2 in func_800B63A8 */


M2C_UNK func_800478B8();            /* extern */
extern M2C_UNK D_800814A0;

void func_800B63A8(void *arg0, void *arg1, void *arg2) {
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_lo;
    u16 temp_v0_4;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;

    ((S_800B63A8_0 *)arg1)->unk_0C = (s32) (((S_800B63A8_0 *)arg1)->unk_0C + ((S_800B63A8_1 *)arg0)->unk_00);
    ((S_800B63A8_0 *)arg1)->unk_10 = (s32) (((S_800B63A8_0 *)arg1)->unk_10 + ((S_800B63A8_1 *)arg0)->unk_04);
    temp_lo = ((S_800B63A8_1 *)arg0)->unk_08 * ((S_800B63A8_1 *)arg0)->unk_10;
    ((S_800B63A8_0 *)arg1)->unk_14 = (s32) (((S_800B63A8_0 *)arg1)->unk_14 + temp_lo);
    ((S_800B63A8_1 *)arg0)->unk_10 = (s16) ((u16) ((S_800B63A8_1 *)arg0)->unk_10 + 1);
    temp_a0 = ((S_800B63A8_0 *)arg1)->unk_10;
    temp_a2 = ((S_800B63A8_0 *)arg1)->unk_14;
    ((S_800B63A8_0 *)arg1)->unk_00 = (s32) (((S_800B63A8_0 *)arg1)->unk_00 + ((S_800B63A8_0 *)arg1)->unk_0C);
    ((S_800B63A8_0 *)arg1)->unk_04 = (s32) (((S_800B63A8_0 *)arg1)->unk_04 + temp_a0);
    ((S_800B63A8_0 *)arg1)->unk_08 = (s32) (((S_800B63A8_0 *)arg1)->unk_08 + temp_a2);
    func_800478B8(arg2, arg1, temp_a2);
    temp_v1 = ((S_800B63A8_2 *)arg2)->unk_0C;
    if (temp_v1 != 0) {
        temp_v0 = temp_v1 - ((S_800B63A8_1 *)arg0)->unk_14;
        ((S_800B63A8_2 *)arg2)->unk_0C = temp_v0;
        if ((u32) (temp_v0 & 0xFF) >= 0x81U) {
            ((S_800B63A8_2 *)arg2)->unk_0C = 0x80U;
        }
    }
    temp_v1_2 = ((S_800B63A8_2 *)arg2)->unk_0D;
    if (temp_v1_2 != 0) {
        temp_v0_2 = temp_v1_2 - ((S_800B63A8_1 *)arg0)->unk_16;
        ((S_800B63A8_2 *)arg2)->unk_0D = temp_v0_2;
        if ((u32) (temp_v0_2 & 0xFF) >= 0x81U) {
            ((S_800B63A8_2 *)arg2)->unk_0D = 0x80U;
        }
    }
    temp_v1_3 = ((S_800B63A8_2 *)arg2)->unk_0E;
    if (temp_v1_3 != 0) {
        temp_v0_3 = temp_v1_3 - ((S_800B63A8_1 *)arg0)->unk_18;
        ((S_800B63A8_2 *)arg2)->unk_0E = temp_v0_3;
        if ((u32) (temp_v0_3 & 0xFF) >= 0x81U) {
            ((S_800B63A8_2 *)arg2)->unk_0E = 0x80U;
        }
    }
    temp_v0_4 = ((S_800B63A8_1 *)arg0)->unk_0E - 1;
    ((S_800B63A8_1 *)arg0)->unk_0E = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_800B63A8_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 = (s32) (D_800814A0 | 0x8000);
    }
}

/* MECHANISM: The three-argument callee contract keeps arg1 in a1 and the updated +0x14 value in a2,
   removing the seed's extra call-argument move while preserving the s0/s1 32-byte frame.
   Separate +0x10/+0x14 locals order the two hoisted loads; 2.8.1-G0 holds D_800814A0's page in v1. */
