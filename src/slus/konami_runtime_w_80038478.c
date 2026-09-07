#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038478_0 {
    u8 pad_00[0x84];
    s8 unk_84;
} S_80038478_0;   /* arg0 in func_80038478 */


M2C_UNK func_800384A8();                            /* extern */

void func_80038478(S_80038478_0 *arg0) {
    if (arg0->unk_84 != 0) {
        func_800384A8();
    }
}
