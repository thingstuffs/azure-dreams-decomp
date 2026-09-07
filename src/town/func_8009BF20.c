#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D01E0;

typedef struct S_80099680_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
} S_80099680_0;   /* arg0 in func_80099680 */

void func_80099680(S_80099680_0 *arg0, M2C_UNK arg1) {
    func_80094984(&D_800D01E0, arg0);
    D_80082668 = 0;
    arg0->unk_04 = &D_80098078;
    arg0->unk_10 = 0;
    arg0->unk_0A = 4;
    func_80099754(arg1);
}
