#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80024298();                         /* extern */

typedef struct S_80026270_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80026270_0;   /* var_s0 in func_80026270 */

void func_80026270(void *arg0) {
    s32 temp_a0;
    s32 var_s1;
    void *var_s0;

    var_s1 = 0;
    var_s0 = arg0;
    do {
        temp_a0 = ((S_80026270_0 *)var_s0)->unk_0C;
        var_s0 += 4;
        var_s1 += 1;
        func_80024298(temp_a0);
    } while (var_s1 < 5);
}
