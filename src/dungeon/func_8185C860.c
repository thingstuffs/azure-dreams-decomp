#include "common.h"
#include "m2c_compat.h"

typedef struct S_8185C860_0 {
    void * unk_00;
    u8 pad_04[0x6C];
    s32 unk_70;
} S_8185C860_0;   /* var_s0 in func_8185C860; pointer addresses record offset 0x14 */

typedef struct S_8185C860_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8185C860_1;   /* temp_v1 in func_8185C860 */

extern u8 *D_800E3D7C[];
s32 func_800A2CB8();
s32 func_800A41F0();
s32 func_800A6D30();
M2C_UNK func_800C87C4();
extern u8 D_800E0003[];
extern u8 D_800E3D68;

void func_8185C860(s16 arg0, s16 arg1, M2C_UNK arg2, s32 arg3) {
    M2C_UNK var_a1;
    s16 var_s1;
    s32 temp_a2;
    s32 var_v0_2;
    s32 var_v0_3;
    u8 *var_s0;
    S_8185C860_1 *temp_v1;

    var_s0 = *D_800E3D7C;
    var_s1 = (s16)(((u32)(arg3 & 0xFF) >> 2) + 0x10);
    do {
        if ((func_800A2CB8(arg2, var_s0) << 0x10) != 0) {
            temp_v1 = ((S_8185C860_0 *)((u8 *)var_s0 - 0x14))->unk_00;
            var_v0_2 = temp_v1->unk_24 - arg0;
            if (var_v0_2 < 0) {
                var_v0_2 = 0 - var_v0_2;
            }
            if (var_v0_2 < 3) {
                var_v0_3 = temp_v1->unk_25 - arg1;
                if (var_v0_3 < 0) {
                    var_v0_3 = 0 - var_v0_3;
                }
                if (var_v0_3 < 3) {
                    if ((func_800A41F0(var_s0) << 0x10) != 0) {
                        temp_a2 = var_s1 + (func_800A6D30() & 3);
                        var_a1 = 0x20;
                        if (D_800E3D68 == 0xFF) {
                            var_a1 = 0xFF;
                        }
                        func_800C87C4(var_s0, var_a1, temp_a2);
                    }
                }
            }
        }
        var_s0 = ((S_8185C860_0 *)((u8 *)var_s0 - 0x14))->unk_70 + 0x20;
    } while (var_s0 != *D_800E3D7C);
}

