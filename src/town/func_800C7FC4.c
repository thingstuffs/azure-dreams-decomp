#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
extern s8 D_80082710;
extern M2C_UNK D_800C5620;
extern M2C_UNK D_800D5360;

typedef struct S_800C5724_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x14];
    s16 unk_6C;
} S_800C5724_0;   /* arg0 in func_800C5724 */

void func_800C5724(S_800C5724_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D5360);
    D_80082710 = 0;
    arg0->unk_54 = &D_800C5620;
    arg0->unk_6C = 0x15;
}
