#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C97F4;
extern M2C_UNK D_800D64C8;

typedef struct S_800C9C0C_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_800C9C0C_0;   /* arg0 in func_800C9C0C */

void func_800C9C0C(S_800C9C0C_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D64C8);
    arg0->unk_50 = &D_800C97F4;
    arg0->unk_6C = 0x15;
}
