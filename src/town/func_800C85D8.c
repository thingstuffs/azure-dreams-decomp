#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C4174();                            /* extern */
extern M2C_UNK D_800D55A0;
extern M2C_UNK D_800D55A8;
extern M2C_UNK D_800D55D0;
extern M2C_UNK D_800D55D4;

typedef struct S_800C5D38_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800C5D38_0;   /* arg2 in func_800C5D38 */

typedef struct S_800C5D38_1 {
    u8 pad_00[0x58];
    M2C_UNK * unk_58;
    M2C_UNK * unk_5C;
    u8 pad_60[0x1C];
    M2C_UNK * unk_7C;
    M2C_UNK * unk_80;
} S_800C5D38_1;   /* arg0 in func_800C5D38 */

void func_800C5D38(S_800C5D38_1 *arg0, M2C_UNK arg1, S_800C5D38_0 *arg2) {
    if (arg2->unk_14 & 0x6000) {
        arg0->unk_58 = &D_800D55D0;
        arg0->unk_5C = &D_800D55D4;
        arg0->unk_7C = &D_800D55A0;
        arg0->unk_80 = &D_800D55A8;
        func_800C4174();
    }
}
