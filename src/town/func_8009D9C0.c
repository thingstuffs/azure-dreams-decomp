#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009B120_0 {
    u8 unk_00;
    u8 unk_01;
} S_8009B120_0;   /* arg0 in func_8009B120 */

s32 func_8009B120(S_8009B120_0 *arg0) {
    s32 var_a1;

    var_a1 = 0;
    if (arg0->unk_01 == 0xD) {
        var_a1 = arg0->unk_00 == 4;
    }
    return var_a1;
}
