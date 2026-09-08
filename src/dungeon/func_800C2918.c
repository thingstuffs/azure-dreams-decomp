#include "common.h"

extern s32 D_800E3D7C[4];

typedef struct S_800C8078_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x3C];
    s32 unk_54;
} S_800C8078_0;   /* arg0 in func_800C8078 */

typedef struct S_800C8078_1 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800C8078_1;   /* var_v1 in func_800C8078 */

typedef struct S_800C8078_2 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_800C8078_2;   /* temp_v0 in func_800C8078 */

s32 func_800C8078(S_800C8078_0 *arg0) {
    s32 var_a0;
    S_800C8078_2 *temp_v0;
    void *var_v1;

    if (arg0->unk_14 & 0x4000) {
        var_a0 = 1;
        var_v1 = (void *)(D_800E3D7C[0] + 4);
        do {
            temp_v0 = ((S_800C8078_1 *)var_v1)->unk_AC;
            if ((temp_v0 != 0) && ((temp_v0->unk_54 & 0x4000) != 0)) {
                return 1;
            }
            var_a0 -= 1;
            var_v1 -= 4;
        } while (var_a0 >= 0);
        goto zero;
    }
    if ((arg0->unk_54 & 0x4000) != 0) {
        return 1;
    }
zero:
    return 0;
}
