#include "common.h"
#include "m2c_compat.h"

s32 func_8002190C();                                /* extern */

typedef struct S_80027A68_0 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80027A68_0;   /* arg0 in func_80027A68 */

void func_80027A68(S_80027A68_0 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_14 = arg1;
    arg0->unk_00 = arg2;
    arg0->unk_0C = func_8002190C();
}
