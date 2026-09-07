#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001EEAC_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_8001EEAC_0;   /* arg0 in func_8001EEAC; pointer addresses record offset 0x10 */


extern M2C_UNK D_80405DE0;

void func_8001EEAC(void *arg0) {
    s32 temp_v0;

    temp_v0 = ((S_8001EEAC_0 *)((u8 *)arg0 - 0x10))->unk_4C - 1;
    ((S_8001EEAC_0 *)((u8 *)arg0 - 0x10))->unk_4C = temp_v0;
    if (temp_v0 < 0) {
        ((S_8001EEAC_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_80405DE0;
    }
}
