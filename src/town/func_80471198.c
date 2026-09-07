#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"



M2C_UNK func_80018824();                /* extern */
extern Rec_D_80016000 *D_80016000;

void func_80018198(void) {
    s32 temp_s0;

    temp_s0 = D_80016000->unk_38.as_s32;
    func_80018824(temp_s0 + 0x3640, 0xC0);
    func_80018824(temp_s0 + 0x3700, 0x10);
}
