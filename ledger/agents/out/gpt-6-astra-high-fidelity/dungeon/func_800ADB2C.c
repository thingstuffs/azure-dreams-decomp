#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B328C_0_pre {
    u16 unk_00;
} S_800B328C_0_pre;   /* the 0x2 bytes before arg0 in func_800B328C, addressed as arg0[-1] */

typedef struct S_800B328C_0 {
    void * unk_00;
    s32 unk_04;
    u8 pad_08[0x84];
    s16 unk_8C;
    u16 unk_8E;
} S_800B328C_0;   /* arg0 in func_800B328C */

typedef struct S_800B328C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B328C_1;   /* temp_a1 in func_800B328C */

typedef struct S_800B328C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B328C_2;   /* arg1 in func_800B328C */

typedef struct S_800B328C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B328C_3;   /* temp_a0 in func_800B328C */

typedef struct S_800B328C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B328C_4;   /* ((S_800B328C_0 *)arg0)->unk_00 in func_800B328C */


s32 func_8003DE58();     /* extern */
M2C_UNK func_800B8EA8(); /* extern */
extern M2C_UNK D_800814A0;

void func_800B328C(void *arg0, void *arg1) {
    u16 sp28[3];
    u16 sp30[3];
    s16 temp_a1_2;
    s16 temp_a2;
    s32 temp_a3;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    void *temp_a0;
    void *temp_a1;

    temp_a1 = ((S_800B328C_4 *)(((S_800B328C_0 *)arg0)->unk_00))->unk_0C;
    if (func_8003DE58(((S_800B328C_1 *)temp_a1)->unk_08, temp_a1, sp28, 0) != 0) {
        temp_a0 = ((S_800B328C_4 *)(((S_800B328C_0 *)arg0)->unk_00))->unk_08;
        if (((S_800B328C_0 *)arg0)->unk_8C != 0) {
            temp_a1_2 = (s16) ((S_800B328C_2 *)arg1)->unk_02;
            temp_a2 = (s16) ((S_800B328C_2 *)arg1)->unk_06;
            temp_a3 = ((S_800B328C_2 *)arg1)->unk_0A << 0x10;
            temp_v0 = ((S_800B328C_3 *)temp_a0)->unk_02 + sp28[0];
            ((S_800B328C_2 *)arg1)->unk_02 = temp_v0;
            sp30[0] = temp_v0;
            temp_v0_2 = ((S_800B328C_3 *)temp_a0)->unk_06 + sp28[1];
            ((S_800B328C_2 *)arg1)->unk_06 = temp_v0_2;
            sp30[1] = temp_v0_2;
            temp_v0_3 = ((S_800B328C_3 *)temp_a0)->unk_0A + sp28[2];
            ((S_800B328C_2 *)arg1)->unk_0A = temp_v0_3;
            sp30[2] = temp_v0_3;
            func_800B8EA8(((S_800B328C_0 *)arg0)->unk_00, temp_a1_2, temp_a2, temp_a3 >> 0x10, sp30, ((S_800B328C_0 *)arg0)->unk_04, 2, 0x800, 1);
        } else {
            ((S_800B328C_2 *)arg1)->unk_02 = (u16) (((S_800B328C_3 *)temp_a0)->unk_02 + sp28[0]);
            ((S_800B328C_2 *)arg1)->unk_06 = (u16) (((S_800B328C_3 *)temp_a0)->unk_06 + sp28[1]);
            ((S_800B328C_2 *)arg1)->unk_0A = (u16) (((S_800B328C_3 *)temp_a0)->unk_0A + sp28[2]);
            ((S_800B328C_0 *)arg0)->unk_8C = 1;
        }
    } else if (((S_800B328C_0 *)arg0)->unk_8C != 0) {
        goto mark;
    }
    if (temp_v0_4 = ((S_800B328C_0 *)arg0)->unk_8E - 1, ((S_800B328C_0 *)arg0)->unk_8E = temp_v0_4, ((s16) temp_v0_4 < 0)) {
mark:
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_800B328C_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
/* MECHANISM: Sibling u16[3] objects at sp+0x28/sp+0x30 produce the 0x48 frame and s1/s0 hold set.
   Early signed call-argument reads fix scheduling; the restored flag store fixes the two-word CFG cascade.
   A signed halfword decrement test and direct D_800814A0 RMW close the exact tail. */
