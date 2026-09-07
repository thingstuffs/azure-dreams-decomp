#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 func_80065F90();             /* extern */
M2C_UNK func_80095168();                         /* extern */
M2C_UNK func_8009519C();                         /* extern */
extern M2C_UNK D_80000001;

typedef struct S_80095094_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095094_0;   /* arg0 in func_80095094 */

void func_80095094(S_80095094_0 *arg0) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 temp_v0;
    register s32 temp_v0_2 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 temp_v0_3 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0_2;
    s32 var_s0;

    temp_v1 = arg0->unk_0C;
    if ((temp_v1 != 0) || (arg0->unk_10 != 0)) {
        var_a2 = 0x80000001;
        ASM_KEEP(var_a2);   /* MATCH pin: retail immediate-load split depends on it */
        var_a0 = 0x80000001;
        if (var_a2 < temp_v1) {
            var_a0 = temp_v1;
        }
        temp_v1_2 = arg0->unk_10;
        var_a1 = 0x80000001;
        if (var_a2 < temp_v1_2) {
            var_a1 = temp_v1_2;
        }
        var_s0 = func_80065F90(var_a0, var_a1, var_a2);
        temp_v0_2 = func_800644B8(var_s0);
        var_a0_2 = var_s0;
        temp_v0_2 = temp_v0_2 << 5;
        var_s0 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_s0 = 0 - var_s0;
        }
        temp_v0_3 = func_80064584(var_a0_2);
        temp_v1_3 = arg0->unk_0C;
        temp_v0_3 = temp_v0_3 << 5;
        var_a0_2 = temp_v0_3;
        if (temp_v0_3 < 0) {
            var_a0_2 = 0 - var_a0_2;
        }
        temp_v0_4 = temp_v1_3 - var_s0;
        if (temp_v1_3 < 0) {
            temp_v0_5 = temp_v1_3 + var_s0;
            arg0->unk_0C = temp_v0_5;
            if (temp_v0_5 > 0) {
                arg0->unk_0C = 0;
                func_80095168(var_a0_2);
                return;
            }
            goto block_16;
        }
        arg0->unk_0C = temp_v0_4;
        if (temp_v0_4 < 0) {
            arg0->unk_0C = 0;
        }
block_16:
        temp_v0_6 = arg0->unk_10;
        if (temp_v0_6 < 0) {
            temp_v0_7 = temp_v0_6 + var_a0_2;
            arg0->unk_10 = temp_v0_7;
            if (temp_v0_7 > 0) {
                arg0->unk_10 = 0;
                func_8009519C(var_a0_2);
            }
        } else {
            temp_v0_8 = temp_v0_6 - var_a0_2;
            arg0->unk_10 = temp_v0_8;
            if (temp_v0_8 < 0) {
                arg0->unk_10 = 0;
            }
        }
    }
}

/* MECHANISM: Signed shifted-result lifetimes give the 0x20 frame with s1=arg0 and s0=the held delta.
   Guarded v0 result holds and an a2 sentinel hold reproduce both absolute-value and constant-split slots.
   Explicit field clears before the two sibcalls supply retail's store-filled tail-jump delay slots. */
