#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017480();     /* extern */
s32 func_80017BEC();                             /* extern */
M2C_UNK func_8001D4AC();                 /* extern */
M2C_UNK func_8001D5D8();                 /* extern */

typedef struct S_8001CE44_0 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
} S_8001CE44_0;   /* arg0 in func_8001CE44 */

void func_8001CE44(S_8001CE44_0 *arg0, s16 arg1) {
    do {
        func_8001D5D8(arg0, arg1);
        func_8001D4AC(arg0, arg1);
    } while ((func_80017BEC(arg1) << 0x10) == 0);
    func_80017480(arg0->unk_00, arg0->unk_02, arg0->unk_04, arg0->unk_06, 0xF);
}
