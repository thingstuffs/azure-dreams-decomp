#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033CD8();                   /* extern */
extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800A7774[3];

typedef struct S_800A77D0_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x3C];
    u16 unk_90;
} S_800A77D0_0;   /* arg0 in func_800A77D0 */

void func_800A77D0(S_800A77D0_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_90 - 1;
    arg0->unk_90 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_80033CD8(arg0, &D_80045340[0]);
        arg0->unk_90 = 0xAU;
        arg0->unk_50 = &D_800A7774[0];
    }
}
