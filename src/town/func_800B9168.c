#include "common.h"
#include "m2c_compat.h"

s32 func_800B68AC();                             /* extern */
M2C_UNK func_800B6E3C();                      /* extern */
extern M2C_UNK D_800B66E8;

typedef struct S_800B68C8_0 {
    M2C_UNK * unk_00;
    s32 unk_04;
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
    s16 unk_0E;
    u8 pad_10[0x4];
    s32 unk_14;
} S_800B68C8_0;   /* arg0 in func_800B68C8 */

void func_800B68C8(S_800B68C8_0 *arg0, s32 arg1, s16 arg2) {
    arg0->unk_08 = arg2;
    arg0->unk_04 = arg1;
    arg0->unk_0C = 0;
    arg0->unk_0E = 0;
    arg0->unk_00 = &D_800B66E8;
    arg0->unk_14 = func_800B68AC(arg0->unk_08);
    func_800B6E3C(arg0);
}
