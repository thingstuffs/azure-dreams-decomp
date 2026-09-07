#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E6F4(); /* extern */
M2C_UNK func_800B3FB8();      /* extern */
M2C_UNK func_800B40E0();                         /* extern */
M2C_UNK func_800B4188();                         /* extern */
M2C_UNK func_800B426C();                         /* extern */
M2C_UNK func_800B4350();                      /* extern */
extern M2C_UNK D_800D1658;
extern M2C_UNK D_800D175C;

typedef struct S_800B43E8_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800B43E8_0;   /* arg0 in func_800B43E8 */

void func_800B43E8(S_800B43E8_0 *arg0) {
    s8 *var_s0;
    s32 var_s1;

    var_s1 = 0;
    func_800B40E0(arg0->unk_20);
    func_800B4188(arg0->unk_20 + 0x48);
    func_800B426C(arg0->unk_20 + 0x90);
    func_8004E6F4(0x10, &D_800D175C, &D_800D175C, &D_800D175C, 0, 0xA);
    var_s0 = &D_800D1658;
    do {
        func_800B3FB8(arg0, var_s0, var_s1);
        var_s1 += 1;
        var_s0 += 0x14;
    } while (var_s1 < 5);
    func_800B4350(arg0);
}
