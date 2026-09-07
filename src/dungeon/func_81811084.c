#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025D9C();       /* extern */
M2C_UNK func_80025E3C();                 /* extern */
M2C_UNK func_80025FFC();                            /* extern */

typedef struct S_80026084_0 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_80026084_0;   /* arg0 in func_80026084 */

void func_80026084(void *arg0) {
    func_80025FFC();
    func_80025D9C(arg0, arg0 + 0x44, arg0 + 0x1C, arg0 + 0x2C);
    func_80025E3C(arg0, ((S_80026084_0 *)arg0)->unk_54);
}
