#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026C00();         /* extern */
M2C_UNK func_80026D78();                       /* extern */

typedef struct S_80026E90_0 {
    s32 unk_00;
} S_80026E90_0;   /* arg0 in func_80026E90 */

void func_80026E90(s8 *arg0, s32 arg1) {
    ((S_80026E90_0 *)arg0)->unk_00 = arg1;
    func_80026C00(arg0 + 0x50, arg0 + 0x28, arg0 + 0x38);
    func_80026D78(arg0);
}
