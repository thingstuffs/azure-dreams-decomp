#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035820_0 {
    s32 unk_00;
    u8 pad_04[0x4C];
    u16 unk_50;
    u8 pad_52[0x22];
    s32 unk_74;
} S_80035820_0;   /* arg0 in func_80035820 */


M2C_UNK func_80033C84();                         /* extern */
M2C_UNK func_80034EB4();                         /* extern */
M2C_UNK func_80035090();                      /* extern */
M2C_UNK func_8003FFF0();                      /* extern */
M2C_UNK func_80044A50();                      /* extern */

void func_80035820(void *arg0) {
    void *temp_s0;

    if (((S_80035820_0 *)arg0)->unk_50 == 0x101) {
        func_80034EB4(((S_80035820_0 *)arg0)->unk_74);
        func_80033C84(((S_80035820_0 *)arg0)->unk_00);
        func_80035090(arg0 + 0x54);
        temp_s0 = arg0 - 0x20;
        func_80044A50(temp_s0);
        func_8003FFF0(temp_s0);
    }
}
