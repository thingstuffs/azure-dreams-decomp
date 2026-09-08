#include "common.h"
#include "records/Rec_func_800B15B8_arg0.h"





typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004E99C();


typedef struct S_800B15B8_1 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x24];
    s32 * unk_38;
    u8 pad_3C[0x10];
    s32 * unk_4C;
    u8 pad_50[0x10];
    s32 * unk_60;
} S_800B15B8_1;   /* var_s0 in func_800B15B8 */

void func_800B15B8(Rec_func_800B15B8_arg0 *arg0) {
    register void *var_s0 ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 var_s1;

    var_s1 = 0;
    var_s0 = arg0->unk_CC;
    do {
        *((S_800B15B8_1 *)var_s0)->unk_10 = 0;
        var_s1 += 1;
        func_8004E99C(*((S_800B15B8_1 *)var_s0)->unk_38);
        *((S_800B15B8_1 *)var_s0)->unk_38 = 0;
        func_8004E99C(*((S_800B15B8_1 *)var_s0)->unk_4C);
        *((S_800B15B8_1 *)var_s0)->unk_4C = 0;
        func_8004E99C(*((S_800B15B8_1 *)var_s0)->unk_60);
        *((S_800B15B8_1 *)var_s0)->unk_60 = 0;
        var_s0 += 4;
    } while (var_s1 < 5);
}
