#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A2CAC_0 {
    u8 pad_00[0x25];
    u8 unk_25;
} S_800A2CAC_0;   /* arg0 in func_800A2CAC */

s32 func_800A2CAC(S_800A2CAC_0 *arg0) {
    return (u8) arg0->unk_25 < 0x40U;
}
