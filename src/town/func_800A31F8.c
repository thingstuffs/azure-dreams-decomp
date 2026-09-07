#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800A07E8;

typedef struct S_800A0958_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x1A];
    u16 unk_6E;
} S_800A0958_0;   /* arg0 in func_800A0958 */

void func_800A0958(S_800A0958_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6E - 0x40;
    arg0->unk_6E = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg0->unk_6E = 0U;
        arg0->unk_50 = &D_800A07E8;
    }
}
