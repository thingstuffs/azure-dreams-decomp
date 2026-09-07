#include "common.h"
#include "m2c_compat.h"

typedef struct S_800945C4_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800945C4_0;   /* temp_a0 + temp_v0 in func_800945C4 */

typedef struct S_800945C4_1 {
    u8 pad_00[0x46];
    s16 unk_46;
} S_800945C4_1;   /* ((S_800945C4_0 *)(temp_a0 + temp_v0))->unk_AC in func_800945C4 */




extern s32 D_800E3D7C;


void func_800945C4(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_v0;

    temp_v0 = D_800E3D7C;
    temp_a0 = (s32) (arg0 << 0x10) >> 0xE;
    ((S_800945C4_1 *)(((S_800945C4_0 *)(temp_a0 + temp_v0))->unk_AC))->unk_46 = (s16) (arg1 | 0x8000);
}
