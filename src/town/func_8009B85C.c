#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_8009803C;
extern M2C_UNK D_800D01A0;

typedef struct S_80098FBC_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80098FBC_0;   /* arg0 in func_80098FBC */

void func_80098FBC(S_80098FBC_0 *arg0, M2C_UNK arg1) {
    func_80094984(&D_800D01A0, arg0);
    D_80082668 = 0;
    arg0->unk_04 = &D_8009803C;
    arg0->unk_0A = 0x15;
    func_80099754(arg1);
}
