#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_800AADB0;

typedef struct S_800AAE30_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800AAE30_0;   /* arg2 in func_800AAE30 */

typedef struct S_800AAE30_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x1E];
    s16 unk_72;
} S_800AAE30_1;   /* arg0 in func_800AAE30 */

void func_800AAE30(S_800AAE30_1 *arg0, void *arg1, S_800AAE30_0 *arg2) {
    arg2->unk_0C = (s32) (func_80064584(arg0->unk_72) << 8);
    arg2->unk_10 = (s32) ((0 - func_800644B8(arg0->unk_72)) << 8);
    arg2->unk_14 = 0;
    arg0->unk_50 = &D_800AADB0;
}
