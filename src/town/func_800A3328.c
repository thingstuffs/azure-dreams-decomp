#include "common.h"
#include "m2c_compat.h"

s32 func_800A0988();                       /* extern */
extern M2C_UNK D_800A0CF8;
extern M2C_UNK D_800D4404;

typedef struct S_800A0A88_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800A0A88_0;   /* temp_v1 in func_800A0A88 */

void func_800A0A88(void) {
    s32 temp_v0;
    S_800A0A88_0 *temp_v1;

    temp_v0 = func_800A0988(&D_800D4404);
    temp_v1 = temp_v0 + 0x20;
    if (temp_v0 != 0) {
        temp_v1->unk_90 = 6;
        temp_v1->unk_50 = &D_800A0CF8;
    }
}
