#include "common.h"
#include "m2c_compat.h"

s32 func_80025080();                             /* extern */
s32 func_80026DE0();                    /* extern */
M2C_UNK func_8004B1A4();                         /* extern */

typedef struct S_80027328_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80027328_0;   /* arg0 in func_80027328 */

void *func_80027328(S_80027328_0 *arg0, M2C_UNK arg1) {
    func_8004B1A4(arg0->unk_08);
    arg0->unk_04 = func_80025080(arg0->unk_00);
    arg0->unk_08 = func_80026DE0(arg0->unk_00, arg1);
    return arg0;
}
