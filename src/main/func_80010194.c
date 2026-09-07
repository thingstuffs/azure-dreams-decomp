#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E994();                         /* extern */

typedef struct S_80023194_0 {
    u8 pad_00[0x8CC];
    s32 * unk_8CC;
} S_80023194_0;   /* var_s0 in func_80023194 */

void func_80023194(void *arg0) {
    s32 *temp_v0;
    s32 var_s1;
    void *var_s0;

    var_s1 = 0;
    var_s0 = arg0;
    do {
        temp_v0 = ((S_80023194_0 *)var_s0)->unk_8CC;
        var_s0 += 4;
        var_s1 += 1;
        func_8004E994(*temp_v0);
    } while (var_s1 < 5);
}
