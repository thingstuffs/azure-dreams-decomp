#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80051FBC();                         /* extern */

typedef struct S_8001C3EC_0 {
    u8 pad_00[0x68C];
    s32 * unk_68C;
} S_8001C3EC_0;   /* var_s0 in func_8001C3EC */

void func_8001C3EC(void *arg0) {
    s32 *temp_v0;
    s32 var_s1;
    void *var_s0;

    var_s1 = 0;
    var_s0 = arg0;
    do {
        temp_v0 = ((S_8001C3EC_0 *)var_s0)->unk_68C;
        var_s0 += 4;
        var_s1 += 1;
        func_80051FBC(*temp_v0);
    } while (var_s1 < 4);
}
