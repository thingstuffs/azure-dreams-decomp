#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80053DA8();                     /* extern */
M2C_UNK func_80094984();  /* extern */
extern M2C_UNK D_80091AF0;
extern M2C_UNK D_800D00E8;

typedef struct S_800940D0_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_800940D0_0;   /* arg0 in func_800940D0 */

void func_800940D0(S_800940D0_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80053DA8(0x510);
    func_80094984(&D_800D00E8, arg0, arg2);
    arg0->unk_00 = &D_80091AF0;
    arg0->unk_0A = 0xC;
}
