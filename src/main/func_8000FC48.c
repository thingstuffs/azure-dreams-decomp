#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022BE8();                      /* extern */
extern u8 D_800280B4[];
__asm__(".set D_800280B4, 0x800280B4");

typedef struct S_80022C48_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x8];
    s32 unk_20;
} S_80022C48_0;   /* arg0 in func_80022C48 */

void func_80022C48(S_80022C48_0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0->unk_14 = arg1;
    arg0->unk_20 = arg4;
    arg0->unk_08 = arg2;
    arg0->unk_0C = arg3;
    func_80022BE8((arg2 * 0x18) + &D_800280B4[0]);
}
