#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AD914_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800AD914_0;   /* arg0 in func_800AD914 */

typedef struct S_800AD914_1 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800AD914_1;   /* var_a0 in func_800AD914 */

s32 func_800AD914(void *arg0) {
    s32 var_a1;
    u8 *var_a0;
    u8 var_v1;

    var_v1 = ((S_800AD914_0 *)arg0)->unk_01;
    var_a1 = 0;
    if (var_v1 != 0) {
        var_a0 = arg0 + 1;
        do {
            if ((((S_800AD914_1 *)var_a0)->unk_02 & 0x20) && ((u32) (var_v1 - 0x17) >= 2U)) {
                var_a1 += 1;
            }
            var_a0 += 4;
            var_v1 = *var_a0;
        } while (var_v1 != 0);
    }
    return var_a1;
}
