#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009456C_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8009456C_0;   /* temp_a0 + temp_v0 in func_8009456C */

typedef struct S_8009456C_1 {
    u8 pad_00[0x45];
    s8 unk_45;
} S_8009456C_1;   /* ((S_8009456C_0 *)(temp_a0 + temp_v0))->unk_AC in func_8009456C */




extern s32 D_800E3D7C;


void func_8009456C(s32 arg0, s8 arg1) {
    s32 temp_a0;
    s32 temp_v0;

    temp_v0 = D_800E3D7C;
    temp_a0 = (s32) (arg0 << 0x10) >> 0xE;
    ((S_8009456C_1 *)(((S_8009456C_0 *)(temp_a0 + temp_v0))->unk_AC))->unk_45 = arg1;
}
