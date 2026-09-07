#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800213C4();                         /* extern */
M2C_UNK func_800214A4();                            /* extern */
M2C_UNK _card_wait();                     /* extern */
extern s32 D_800287CC[];

void func_800209C4(void) {
    s32 temp_a0;
    func_800214A4();
    _card_wait(0);
    _card_wait(1);
    temp_a0 = 0x10 - D_800287CC[0];
    D_800287CC[0] = temp_a0;
    func_800213C4(temp_a0);
}
