#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800213C4();                         /* extern */
M2C_UNK func_800214A4();                            /* extern */
M2C_UNK _card_wait();                     /* extern */
extern s32 D_800287CC;

/* Waits for both card channels and requests information for the selected channel. */
void func_80020984(void) {
    func_800214A4();
    _card_wait(0);
    _card_wait(1);
    func_800213C4(D_800287CC);
}
