#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800176B8();             /* extern */
M2C_UNK func_80018594();                         /* extern */
s32 func_8001868C();                         /* extern */
M2C_UNK func_800188E8();   /* extern */

typedef struct S_806D43CC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_806D43CC_0;   /* arg0 in func_806D43CC */

/* Performs conditional object setup before forwarding to func_800176B8. */
void func_806D43CC(S_806D43CC_0 *object, M2C_UNK forwardedValue) {
    if (func_8001868C(0x145C) != 0) {
        func_800188E8(0x990, 2, 2);
        func_80018594(object->unk_18);
    }
    func_800176B8(object, forwardedValue);
}
