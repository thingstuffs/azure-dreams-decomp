#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800CD70C;
extern M2C_UNK D_800D72AC;

typedef struct S_800CDDFC_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u8 pad_6E[0x16];
    s16 unk_84;
} S_800CDDFC_0;   /* arg0 in func_800CDDFC */

void func_800CDDFC(S_800CDDFC_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D72AC);
    arg0->unk_50 = &D_800CD70C;
    arg0->unk_84 = 0x50;
    arg0->unk_6C = 0xD2;
}
