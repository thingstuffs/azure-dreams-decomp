#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800231E4();                     /* extern */

typedef struct S_800226A8_0 {
    u8 pad_00[0x20];
    s32 * unk_20;
} S_800226A8_0;   /* arg0 in func_800226A8 */

void func_800226A8(S_800226A8_0 *arg0) {
    if (*arg0->unk_20 == 0) {
        func_800231E4(0);
    }
}
