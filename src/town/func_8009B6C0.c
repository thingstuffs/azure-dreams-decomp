#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();           /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D00A0;

typedef struct S_80098E20_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80098E20_0;   /* arg0 in func_80098E20 */

void func_80098E20(S_80098E20_0 *arg0) {
    func_80094984(&D_800D00A0, arg0);
    D_80082668 = 0;
    arg0->unk_04 = &D_80098078;
    arg0->unk_0A = 8;
}
