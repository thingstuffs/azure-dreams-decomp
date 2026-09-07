#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80034EB4_0 {
    s8 unk_00;
    s8 unk_01;
    u8 pad_02[0x32];
    s32 unk_34;
} S_80034EB4_0;   /* arg0 in func_80034EB4 */


void func_80034EB4(S_80034EB4_0 *arg0) {
    arg0->unk_00 = 0;
    arg0->unk_01 = 0;
    arg0->unk_34 = 0;
}
