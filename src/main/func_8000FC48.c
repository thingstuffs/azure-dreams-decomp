#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8002290C_arg0.h"

M2C_UNK func_80022BE8();                      /* extern */
extern u8 D_800280B4[];
__asm__(".set D_800280B4, 0x800280B4");


void func_80022C48(Rec_func_8002290C_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0->unk_14 = arg1;
    arg0->unk_20 = arg4;
    arg0->unk_08 = arg2;
    arg0->unk_0C = arg3;
    func_80022BE8((arg2 * 0x18) + &D_800280B4[0]);
}
