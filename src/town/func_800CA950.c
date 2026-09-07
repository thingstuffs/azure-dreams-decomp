#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
extern s8 D_80082680;
extern M2C_UNK D_800C7EF0;
extern M2C_UNK D_800D5FA0;

typedef struct S_800C80B0_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x1A];
    s16 unk_72;
} S_800C80B0_0;   /* arg0 in func_800C80B0 */

void func_800C80B0(S_800C80B0_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D5FA0);
    D_80082680 = 0;
    arg0->unk_54 = &D_800C7EF0;
    arg0->unk_72 = 0;
}
