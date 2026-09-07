#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800177CC();             /* extern */
M2C_UNK func_80018594();                         /* extern */
M2C_UNK func_8001860C();                     /* extern */
s32 func_800187B8();                         /* extern */
s32 func_80018800();                         /* extern */

typedef struct S_806D435C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_806D435C_0;   /* arg0 in func_806D435C */

void func_806D435C(S_806D435C_0 *arg0, M2C_UNK arg1) {
    func_8001860C(0x98F);
    if ((func_800187B8(5) != 0) || (func_80018800(5) != 0)) {
        func_80018594(arg0->unk_18);
    }
    func_800177CC(arg0, arg1);
}
