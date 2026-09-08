#include "common.h"
#include "m2c_compat.h"

/* extern */
M2C_UNK func_80093D48();      /* extern */

typedef struct S_80090F84_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80090F84_0;   /* arg2 in func_80090F84 */


M2C_UNK func_80090A74(s32 *, M2C_UNK, S_80090F84_0 *);
void func_80090F84(s32 *arg0, M2C_UNK arg1, S_80090F84_0 *arg2) {
    s32 temp_s0;

    temp_s0 = *arg0;
    func_80090A74(arg0, arg1, arg2);
    if ((temp_s0 == *arg0) && (arg2->unk_14 & 0x6000)) {
        func_80093D48(arg0, arg1, arg2);
    }
}
