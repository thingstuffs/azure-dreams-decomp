/* first_pass: swept 49 configs, best 2.7.2-cdk '-fno-delayed-branch' 89 words off — do NOT re-sweep by hand */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8004FAA4_0 {
    u8 pad_00[0x8];
    union { s32 s; volatile s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
} S_8004FAA4_0;   /* input in func_8004FAA4 */

typedef struct S_8004FAA4_1 {
    u8 pad_00[0x24];
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    u8 pad_34[0x4];
    s32 unk_38;
} S_8004FAA4_1;   /* arg0 in func_8004FAA4 */

typedef struct S_8004FAA4_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    s32 unk_B0;
} S_8004FAA4_2;   /* D_800814A8[0] in func_8004FAA4 */


M2C_UNK func_8004FA2C();
s32 func_8004FD78();
M2C_UNK func_80053DA8();
extern void *D_800814A8[];
extern M2C_UNK D_80083160[8];

void func_8004FAA4(S_8004FAA4_1 *arg0) {
    M2C_UNK var_a1;
    M2C_UNK *input;
    void *call_arg0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_s0;

    input = D_80083160;
    var_s0 = 0;
    if ((((S_8004FAA4_0 *)input)->unk_08.s != 0) && (arg0->unk_24 >= 2)) {
        if (((S_8004FAA4_0 *)input)->unk_08.s & 0xA000) {
            if (((S_8004FAA4_0 *)input)->unk_10 & 0x2000) {
                var_s0 = 1;
                goto block_7;
            }
            if (((S_8004FAA4_0 *)input)->unk_10 & 0x8000) {
                var_s0 = -1;
block_7:
                arg0->unk_38 = 0;
                arg0->unk_28 = 4;
            } else {
                temp_v1 = arg0->unk_38;
                if (temp_v1 >= 9) {
                    arg0->unk_38 = (s32) (temp_v1 - 2);
                    temp_v1 = ((S_8004FAA4_0 *)input)->unk_08.u;
                    if (temp_v1 & 0x2000) {
                        var_s0 = 1;
                        goto block_13;
                    }
                    if (temp_v1 & 0x8000) {
                        var_s0 = -1;
block_13:
                        arg0->unk_28 = 3;
                    }
                } else {
                    arg0->unk_38 = (s32) (temp_v1 + 1);
                }
            }
        }
        if (var_s0 == 0) {
            if (((S_8004FAA4_0 *)input)->unk_10 & 1) {
                ASM_SCHED_BARRIER();   /* MATCH pin: slus-diff */
                if (((S_8004FAA4_2 *)(D_800814A8[0]))->unk_B0 != 0) {
                    call_arg0 = arg0;
                    var_a1 = 1;
                    goto block_22;
                }
            } else if (((S_8004FAA4_0 *)input)->unk_10 & 2) {
                ASM_SCHED_BARRIER();   /* MATCH pin: slus-diff */
                if (((S_8004FAA4_2 *)(D_800814A8[0]))->unk_AC != 0) {
                    call_arg0 = arg0;
                    var_a1 = 0;
block_22:
                    temp_v0 = func_8004FD78(call_arg0, var_a1);
                    arg0->unk_28 = 4;
                    var_s0 = temp_v0 - arg0->unk_30;
                }
            }
            if (var_s0 != 0) {
                goto block_24;
            }
        } else {
block_24:
            func_80053DA8(0x504);
            func_8004FA2C(arg0, var_s0);
        }
    }
}
