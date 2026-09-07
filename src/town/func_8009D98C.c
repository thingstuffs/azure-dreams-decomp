#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8009AF74;

typedef struct S_8009B0EC_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8009B0EC_0;   /* arg0 in func_8009B0EC */

void func_8009B0EC(S_8009B0EC_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg0->unk_0A = 3U;
        arg0->unk_04 = &D_8009AF74;
    }
}
