#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017D9C();             /* extern */
M2C_UNK func_80018854();                         /* extern */
M2C_UNK func_800188CC();                     /* extern */

typedef struct S_800164E8_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800164E8_0;   /* arg0 in func_800164E8 */

void func_800164E8(S_800164E8_0 *arg0, M2C_UNK arg1) {
    func_80018854(arg0->unk_18);
    func_800188CC(0x50C);
    func_80017D9C(arg0, arg1);
}
