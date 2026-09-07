#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D0170;

typedef struct S_80098C40_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80098C40_0;   /* arg0 in func_80098C40 */

void func_80098C40(S_80098C40_0 *arg0, M2C_UNK arg1) {
    func_80094984(&D_800D0170, arg0);
    arg0->unk_04 = &D_80098078;
    arg0->unk_0A = 0x10;
    func_80099754(arg1);
}
