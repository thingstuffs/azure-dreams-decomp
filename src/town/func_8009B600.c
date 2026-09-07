#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80099754();                     /* extern */
extern M2C_UNK D_800981D4;
extern M2C_UNK D_800D0090;

typedef struct S_80098D60_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x8];
    s16 unk_10;
} S_80098D60_0;   /* arg0 in func_80098D60 */

void func_80098D60(S_80098D60_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80099754(arg1);
    func_80094984(&D_800D0090, arg0, arg2);
    arg0->unk_04 = &D_800981D4;
    arg0->unk_10 = 0x800;
}
