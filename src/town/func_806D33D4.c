#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

typedef struct S_80016BD4_2 {
    u8 pad_00[0x4];
    M2C_UNK (*unk_04)(void *, u8, s32);
} S_80016BD4_2;   /* ((temp_a1 * 0x10) + temp_a0->unk_10) in func_80016BD4 */



typedef struct S_80016BD4_1 {
    u8 unk_00;
    u8 pad_01[0xF];
    s32 unk_10;
} S_80016BD4_1;   /* temp_a0 in func_80016BD4 */


extern Rec_D_80016000 *D_80016000;
extern s32 D_80016E40;

void func_80016BD4(void) {
    u8 temp_a1;
    S_80016BD4_1 *temp_a0;

    temp_a0 = (D_80016000->unk_14 * 0x1C) + D_80016E40;
    temp_a1 = temp_a0->unk_00;
    ((S_80016BD4_2 *)(((temp_a1 * 0x10) + temp_a0->unk_10)))->unk_04(temp_a0, temp_a1, D_80016000->unk_00.at00_s32.v);
}
