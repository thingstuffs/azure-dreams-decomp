#include "common.h"
#include "m2c_compat.h"

typedef struct S_80018198_0 {
    u8 pad_00[0x38];
    s32 unk_38;
} S_80018198_0;   /* D_80016000 in func_80018198 */


M2C_UNK func_80018824();                /* extern */
extern S_80018198_0 *D_80016000;

void func_80018198(void) {
    s32 temp_s0;

    temp_s0 = D_80016000->unk_38;
    func_80018824(temp_s0 + 0x3640, 0xC0);
    func_80018824(temp_s0 + 0x3700, 0x10);
}
