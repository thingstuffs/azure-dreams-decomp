#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80094C1C();                            /* extern */
extern M2C_UNK D_80092320;
extern M2C_UNK D_800D0108;

typedef struct S_800943B8_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_800943B8_0;   /* arg0 in func_800943B8 */

void func_800943B8(S_800943B8_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80094C1C();
    func_80094984(&D_800D0108, arg0, arg2);
    arg0->unk_00 = &D_80092320;
    arg0->unk_0A = 6;
}
