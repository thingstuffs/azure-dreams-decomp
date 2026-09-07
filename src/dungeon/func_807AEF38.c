#include "common.h"
#include "m2c_compat.h"

extern s8 D_80082EA4;
extern void *D_800E3D7C;

typedef struct S_800F6738_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x44];
    s32 unk_5C;
} S_800F6738_0;   /* var_v1 in func_800F6738 */

void func_800F6738(void) {
    void *temp_a0;
    S_800F6738_0 *var_v1;

    var_v1 = D_800E3D7C;
    temp_a0 = var_v1;
    do {
        if (var_v1->unk_13 == 0x32) {
            var_v1->unk_14 = (s32) (var_v1->unk_14 | 0x800000);
        }
        var_v1 = var_v1->unk_5C + 0x20;
    } while (var_v1 != temp_a0);
    D_80082EA4 = 0x1F;
}
