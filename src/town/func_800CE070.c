#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800D68E8;

typedef struct S_800CB7D0_0 {
    u8 pad_00[0x7C];
    s32 * unk_7C;
} S_800CB7D0_0;   /* arg0 in func_800CB7D0 */

s32 func_800CB7D0(S_800CB7D0_0 *arg0) {
    return *arg0->unk_7C == (s32) &D_800D68E8;
}
