#include "common.h"
#include "m2c_compat.h"

typedef struct S_80021EB8_0 {
    u8 pad_00[0x204];
    s32 unk_204;
} S_80021EB8_0;   /* arg0 in func_80021EB8 */

void func_80021EB8(void *arg0) {
    s32 *var_a1;
    s32 temp_v0;
    s32 var_a2;
    s32 var_v1;

    var_a2 = 0;
    var_a1 = arg0 + 0x208;
    var_v1 = 0x177D;
    do {
        temp_v0 = *var_a1;
        var_a1 += 1;
        var_v1 -= 1;
        var_a2 ^= temp_v0;
    } while (var_v1 >= 0);
    ((S_80021EB8_0 *)arg0)->unk_204 = var_a2;
}
