#include "common.h"
#include "m2c_compat.h"

typedef s8 M2C_UNK8;

extern M2C_UNK func_80094A60();

typedef struct S_80094984_0 {
    u8 pad_00[0x16];
    s16 unk_16;
} S_80094984_0;   /* arg1 in func_80094984 */

void func_80094984(s32 *arg0, S_80094984_0 *arg1) {
    if (arg0[arg1->unk_16] != 0) {
        func_80094A60();
    }
}
