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

/* Apply a randomized effect to eligible targets within two tiles of the center. */
void func_8185C860(s16 center_x, s16 center_y, M2C_UNK source, s32 power) {
    M2C_UNK effect_code;
    s16 base_value;
    s32 effect_value;
    s32 distance_x;
    s32 distance_y;
    u8 *target;
    S_8185C860_1 *position;

    target = *D_800E3D7C;
    base_value = (s16)(((u32)(power & 0xFF) >> 2) + 0x10);
    do {
        if ((func_800A2CB8(source, target) << 0x10) != 0) {
            position = ((S_8185C860_0 *)((u8 *)target - 0x14))->unk_00;
            distance_x = position->unk_24 - center_x;
            if (distance_x < 0) {
                distance_x = 0 - distance_x;
            }
            if (distance_x < 3) {
                distance_y = position->unk_25 - center_y;
                if (distance_y < 0) {
                    distance_y = 0 - distance_y;
                }
                if (distance_y < 3) {
                    if ((func_800A41F0(target) << 0x10) != 0) {
                        effect_value = base_value + (func_800A6D30() & 3);
                        effect_code = 0x20;
                        if (D_800E3D68 == 0xFF) {
                            effect_code = 0xFF;
                        }
                        func_800C87C4(target, effect_code, effect_value);
                    }
                }
            }
        }
        target = ((S_8185C860_0 *)((u8 *)target - 0x14))->unk_70 + 0x20;
    } while (target != *D_800E3D7C);
}

