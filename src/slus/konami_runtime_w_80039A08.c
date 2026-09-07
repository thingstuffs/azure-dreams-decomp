#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039A08_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_80039A08_0;   /* arg0 in func_80039A08 */


s32 func_80039884();                          /* extern */
M2C_UNK func_80053DA8();                     /* extern */
s32 func_80053EF0();                         /* extern */
extern M2C_UNK func_800389B4;

void func_80039A08(S_80039A08_0 *arg0) {
    s32 temp_s0;

    temp_s0 = func_80053EF0(4);
    if (func_80039884(arg0) != 0) {
        if (temp_s0 != 0) {
            arg0->unk_10 = NULL;
            arg0->unk_1C = (s32) (arg0->unk_1C - 1);
        }
    } else {
        if (temp_s0 == 0x100) {
            arg0->unk_10 = &func_800389B4;
            return;
        }
        func_80053DA8(0xB4);
    }
}
