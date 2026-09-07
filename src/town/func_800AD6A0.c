#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800AAC64;

typedef struct S_800AAE00_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_800AAE00_0;   /* arg1 in func_800AAE00 */

typedef struct S_800AAE00_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_800AAE00_1;   /* arg0 in func_800AAE00 */

void func_800AAE00(S_800AAE00_1 *arg0, S_800AAE00_0 *arg1) {
    arg1->unk_15 = 1;
    arg0->unk_50 = &D_800AAC64;
    arg0->unk_6C = 0x15;
}
