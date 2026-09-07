#include "common.h"
#include "m2c_compat.h"

extern s32 D_800E3D7C;

typedef struct S_800C82B8_0 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_800C82B8_0;   /* var_v1 in func_800C82B8 */

typedef struct S_800C82B8_1 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_800C82B8_1;   /* arg0 in func_800C82B8 */

s32 func_800C82B8(void *arg0) {
    s32 var_a1;
    s32 var_a2;
    void *var_v1;

    var_a2 = 0;
    if (arg0 == D_800E3D7C) {
        var_a1 = 1;
        var_v1 = arg0 + 4;
        do {
            if ((((S_800C82B8_0 *)var_v1)->unk_AC != 0) && (((S_800C82B8_1 *)arg0)->unk_54 & 8)) {
                var_a2 += 1;
            }
            var_a1 -= 1;
            var_v1 -= 4;
        } while (var_a1 >= 0);
    }
    return var_a2;
}
