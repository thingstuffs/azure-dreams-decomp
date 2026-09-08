#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800213C4();                         /* extern */
M2C_UNK func_800214A4();                            /* extern */
M2C_UNK _card_wait();                     /* extern */
extern s32 D_800287CC[];

/* Waits for both card channels and requests information for the alternate channel. */
void func_800209C4(void) {
    s32 card_channel;
    func_800214A4();
    _card_wait(0);
    _card_wait(1);
    card_channel = 0x10 - D_800287CC[0];
    D_800287CC[0] = card_channel;
    func_800213C4(card_channel);
}
