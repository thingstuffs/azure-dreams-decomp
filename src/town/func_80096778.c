#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80094C1C();                            /* extern */
M2C_UNK func_80094C74();                     /* extern */
extern M2C_UNK D_80091260;
extern M2C_UNK D_800D0090;

typedef struct S_80093ED8_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x3A];
    s16 unk_3E;
} S_80093ED8_0;   /* arg0 in func_80093ED8 */

void func_80093ED8(S_80093ED8_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    arg0->unk_3E = 6;
    func_80094C1C();
    func_80094C74(arg1);
    func_80094984(&D_800D0090, arg0, arg2);
    arg0->unk_00 = &D_80091260;
}
