#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();           /* extern */
extern M2C_UNK D_80090C68;
extern M2C_UNK D_800D0078;

typedef struct S_80093D48_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_80093D48_0;   /* arg0 in func_80093D48 */

void func_80093D48(S_80093D48_0 *arg0) {
    func_80094984(&D_800D0078, arg0);
    arg0->unk_00 = &D_80090C68;
    arg0->unk_0A = 0x54;
}
