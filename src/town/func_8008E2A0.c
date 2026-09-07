#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008BA00_0 {
    u8 pad_00[0x64];
    u16 unk_64;
    u8 pad_66[0x2];
    M2C_UNK (*unk_68)();
    M2C_UNK (*unk_6C)();
} S_8008BA00_0;   /* arg0 in func_8008BA00 */


void func_8008BA00(S_8008BA00_0 *arg0) {
    M2C_UNK (*temp_v0_2)();
    u16 temp_v0;

    temp_v0 = arg0->unk_64 - 1;
    arg0->unk_64 = temp_v0;
    if ((s16) temp_v0 < 0) {
        temp_v0_2 = arg0->unk_6C;
        arg0->unk_68 = temp_v0_2;
        temp_v0_2();
    }
}
