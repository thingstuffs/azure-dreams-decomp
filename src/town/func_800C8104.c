#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C56A8;
extern M2C_UNK D_800D5388;

typedef struct S_800C5864_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x14];
    s16 unk_6C;
} S_800C5864_0;   /* arg0 in func_800C5864 */

void func_800C5864(S_800C5864_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D5388);
    arg0->unk_6C = 0x28;
    arg0->unk_54 = &D_800C56A8;
}
