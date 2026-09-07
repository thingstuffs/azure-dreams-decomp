#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4();                         /* extern */
M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80094C1C();                            /* extern */
M2C_UNK func_8009503C();                     /* extern */
extern M2C_UNK D_80091528;
extern M2C_UNK D_800D0098;

typedef struct S_80093F48_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
    u8 pad_0C[0x32];
    s16 unk_3E;
} S_80093F48_0;   /* arg0 in func_80093F48 */

void func_80093F48(S_80093F48_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    arg0->unk_3E = 6;
    func_80094C1C();
    func_8009503C(arg1);
    func_80094984(&D_800D0098, arg0, arg2);
    arg0->unk_00 = &D_80091528;
    arg0->unk_0A = (s16) (func_800374F4(2) + 0xC);
}
