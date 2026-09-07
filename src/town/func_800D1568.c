#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
extern s8 D_80082688;
extern M2C_UNK D_800CE780;
extern M2C_UNK D_800D72D4;

typedef struct S_800CECC8_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
} S_800CECC8_0;   /* arg0 in func_800CECC8 */

typedef struct S_800CECC8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800CECC8_1;   /* arg1 in func_800CECC8 */

void func_800CECC8(S_800CECC8_0 *arg0, S_800CECC8_1 *arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D72D4);
    D_80082688 = 0;
    arg0->unk_54 = &D_800CE780;
    arg1->unk_14 = 0xFFF60000;
}
