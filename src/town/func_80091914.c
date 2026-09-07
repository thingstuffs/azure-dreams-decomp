#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008F01C();                            /* extern */

typedef struct S_8008F074_0 {
    u8 pad_00[0x14];
    s8 unk_14;
} S_8008F074_0;   /* arg0 in func_8008F074 */

void func_8008F074(S_8008F074_0 *arg0) {
    func_8008F01C();
    arg0->unk_14 = 1;
}
