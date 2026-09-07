#include "common.h"
#include "m2c_compat.h"

s32 func_8002553C();                             /* extern */
M2C_UNK func_8002654C();                         /* extern */

typedef struct S_800255D0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800255D0_0;   /* arg0 in func_800255D0 */

s32 func_800255D0(S_800255D0_0 *arg0) {
    func_8002654C(func_8002553C(arg0->unk_14));
    return 1;
}
