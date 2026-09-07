#include "common.h"
#include "m2c_compat.h"

s32 func_80096788();                                /* extern */
M2C_UNK func_800967E0();                 /* extern */
extern s32 D_800FE5D4;

typedef struct S_80096810_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80096810_0;   /* arg0 in func_80096810 */

void func_80096810(S_80096810_0 *arg0) {
    s32 temp_a1;

    if (D_800FE5D4 < 0) {
        temp_a1 = (func_80096788() << 0x10) - 1;
        if (temp_a1 >= arg0->unk_08) {
            func_800967E0(arg0, temp_a1);
        }
    }
}
