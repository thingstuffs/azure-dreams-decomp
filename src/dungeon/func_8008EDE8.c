#include "common.h"
#include "m2c_compat.h"

typedef struct S_80094548_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80094548_0;   /* temp_a0 + temp_v0 in func_80094548 */

typedef struct S_80094548_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80094548_1;   /* ((S_80094548_0 *)(temp_a0 + temp_v0))->unk_AC in func_80094548 */




extern s32 D_800E3D7C;


void func_80094548(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_v0;

    temp_v0 = D_800E3D7C;
    temp_a0 = (s32) (arg0 << 0x10) >> 0xE;
    ((S_80094548_1 *)(((S_80094548_0 *)(temp_a0 + temp_v0))->unk_AC))->unk_2A = (s16) (arg1 << 9);
}
