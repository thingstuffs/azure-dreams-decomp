#include "common.h"
#include "m2c_compat.h"

typedef struct S_8012498C_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
} S_8012498C_0;   /* arg0 in func_8012498C */

void func_8012498C(S_8012498C_0 *arg0) {
    arg0->unk_0A = 1;
    arg0->unk_04 = 0;
    arg0->unk_06 = 0;
}
