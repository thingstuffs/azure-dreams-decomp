#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B173C_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0xB8];
    s32 unk_CC;
} S_800B173C_0;   /* arg0 in func_800B173C */

typedef struct S_800B173C_1 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800B173C_1;   /* *var_v0 in func_800B173C */

void func_800B173C(S_800B173C_0 *arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_v0;
    void **var_v0;

    temp_v0 = arg0->unk_10;
    if (temp_v0 != arg1) {
        temp_a0 = arg0->unk_CC;
        if (temp_v0 >= arg1) {
            var_v0 = temp_a0 + 0x74;
        } else {
            var_v0 = temp_a0 + 0x78;
        }
        *((S_800B173C_1 *)(*var_v0))->unk_04 = 0xE0E0E0;
    }
}
