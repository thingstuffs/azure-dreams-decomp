#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001703C_0 {
    s32 unk_00;
} S_8001703C_0;   /* &D_80083CE8 in func_8001703C */

typedef struct S_8001703C_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x2];
    s32 unk_18;
    s16 unk_1C;
} S_8001703C_1;   /* temp_v0 in func_8001703C */

void func_8001703C(void) {
    u8 *temp_v0;

    ((S_8001703C_0 *)(&D_80083CE8))->unk_00 = 0;
    temp_v0 = (u8 *)&D_80083CE8;
    ((S_8001703C_1 *)temp_v0)->unk_04 = 0;
    ((S_8001703C_1 *)temp_v0)->unk_08 = 0;
    ((S_8001703C_1 *)temp_v0)->unk_0C = 0;
    ((S_8001703C_1 *)temp_v0)->unk_10 = 0;
    ((S_8001703C_1 *)temp_v0)->unk_14 = 0;
    ((S_8001703C_1 *)temp_v0)->unk_18 = 0;
    ((S_8001703C_1 *)temp_v0)->unk_1C = 0;
}
