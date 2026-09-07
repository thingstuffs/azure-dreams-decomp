#include "common.h"
#include "m2c_compat.h"

typedef struct S_80095388_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80095388_0;   /* arg0 in func_80095388 */

void func_80095388(S_80095388_0 *arg0) {
    arg0->unk_14 = (s32) (arg0->unk_14 + 0x20000);
}
