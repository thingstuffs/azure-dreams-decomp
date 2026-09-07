#include "common.h"
#include "m2c_compat.h"

s32 func_80026E30();                             /* extern */
s32 func_80027008();               /* extern */
M2C_UNK func_8004B1A4();                         /* extern */

typedef struct S_80027384_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80027384_0;   /* arg0 in func_80027384 */

void *func_80027384(S_80027384_0 *arg0, M2C_UNK arg1) {
    s32 temp_v0;

    func_8004B1A4(arg0->unk_08);
    temp_v0 = func_80026E30(arg0->unk_00);
    arg0->unk_04 = temp_v0;
    arg0->unk_08 = func_80027008(arg0->unk_00, arg1, temp_v0);
    return arg0;
}
