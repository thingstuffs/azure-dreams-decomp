#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800B62A4_0 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_800B62A4_0;   /* var_s2 in func_800B62A4 */



M2C_UNK bzero();            /* extern */
M2C_UNK func_800B58B8();             /* extern */
M2C_UNK func_800B6094();            /* extern */
M2C_UNK func_800B61C0();            /* extern */

void func_800B62A4(void *arg0, s32 arg1) {
    void *sp10[3];
    s32 var_s0;
    register s32 var_s1 ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    s32 var_s3;
    s32 var_v0;
    void *temp_a0;
    s32 *temp_v0;
    void *var_a1;
    void *var_s2;

    var_s1 = 0;
    var_s0 = var_s1;
    var_s3 = 8;
    var_s2 = arg0;
    do {
        if (((S_800B62A4_0 *)var_s2)->unk_08 != 0) {
            func_800B6094(arg0 + var_s3, arg1, var_s1);
            var_s1 += 1;
        }
        var_s3 += 3;
        var_s0 += 1;
        var_s2 += 3;
    } while (var_s0 < 3);
    bzero(sp10, 0xC);
    func_800B58B8(sp10, arg0);
    var_s0 = 0;
    var_v0 = var_s1 < 3;
    var_s3 = var_s1;
    if (var_v0 != 0) {
        var_s2 = sp10;
        do {
            temp_a0 = *(void **)var_s2;
            if (temp_a0 != NULL) {
                func_800B61C0(temp_a0, arg1, var_s1);
                var_s1 += 1;
            }
            var_s0 += 1;
            var_s2 = (void *)((s8 *)var_s2 + 4);
        } while ((var_s0 + var_s3) < 3);
        var_v0 = var_s1 < 3;
    }
    var_s0 = var_s1;
    if ((var_v0 != 0) && (((Rec_D_800E3D7C *)arg0)->unk_48.at01_u8.v != 0)) {
        func_800B61C0(arg0 + 0x48, arg1, var_s1);
        var_s1 += 1;
        ASM_KEEP(var_s1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        var_s0 = var_s1;
    }
    if (var_s0 < 3) {
        var_a1 = (var_s0 * 4) + arg1;
        do {
            temp_v0 = (*(s32 * volatile *)((u8 *)var_a1 + 0x38));
            var_s0 += 1;
            *temp_v0 = 0;
            ASM_KEEP(temp_v0);   /* MATCH pin: keeps a statement from moving across a call/branch */
            var_a1 += 4;
        } while (var_s0 < 3);
    }
}
/* MECHANISM: A 3-pointer stack array forces the retail 0x40 frame; unified loop-role
   live ranges plus guarded $s1/$s3/$s2 pins reproduce the hold set.
   cdk-G0's zero-equivalence copy and a volatile $v0 tail load with post-store keep fence
   place $s0++ in the load delay and preserve the retail loop schedule. */
