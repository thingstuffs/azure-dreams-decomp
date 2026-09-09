#include "common.h"
#include "m2c_compat.h"

typedef struct S_800178B4_3 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    M2C_UNK * unk_08;
} S_800178B4_3;   /* (temp_a0_3 + arg0->unk_10) in func_800178B4 */


s32 func_800169EC();                                /* extern */
M2C_UNK func_80017808();                      /* extern */
M2C_UNK func_80019814();                 /* extern */
M2C_UNK func_8001A418();                         /* extern */
s32 func_8001A510();                         /* extern */
extern M2C_UNK D_80016A3C;
extern M2C_UNK D_80017B40;
extern M2C_UNK D_8001B718;
extern M2C_UNK D_8001B81C;

typedef struct S_800178B4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
} S_800178B4_0;   /* arg0 in func_800178B4 */

typedef struct S_800178B4_1 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800178B4_1;   /* temp_v1 in func_800178B4 */

typedef struct S_800178B4_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
} S_800178B4_2;   /* temp_a0_2 in func_800178B4 */

s32 func_800178B4(S_800178B4_0 *arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_a0_3;
    S_800178B4_2 *temp_a0_2;

    if ((func_8001A510(0x479) == 0) && (func_800169EC() != 0)) {
        func_8001A418(0x479);
        temp_a0 = arg1 * 0x10;
        {
            M2C_UNK *temp_v0;
            s32 temp_v1;

            temp_v1 = temp_a0 + arg0->unk_10;
            temp_v0 = &D_80016A3C;
            ((S_800178B4_1 *)temp_v1)->unk_04 = temp_v0;
        }
        temp_a0_2 = temp_a0 + arg0->unk_10;
        temp_a0_2->unk_08 = &D_8001B718;
        func_80017808(temp_a0_2);
        return 0;
    }
    if (func_8001A510(0x479) != 0) {
        temp_a0_3 = arg1 * 0x10;
        ((S_800178B4_3 *)((temp_a0_3 + arg0->unk_10)))->unk_04 = &D_80017B40;
        ((S_800178B4_3 *)((temp_a0_3 + arg0->unk_10)))->unk_08 = &D_8001B81C;
    }
    func_8001A418(arg0->unk_18);
    return func_80019814(arg0, arg1);
}

/* MECHANISM: Holding arg0/arg1 in s0/s1 and delaying the second scaled index restores the 32-byte frame.
   The true-space s32 function uses return 0 for the in-row epilogue edge, removing the phantom call.
   At 2.7.2-cdk-G0, an arm-local v1 pin destructively forms temp_a0 + base; post-store ASM_KEEP
   preserves the exact lui/lw/addiu schedule and the ordered addu v1,a0,v1. */
