#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800214A4();                            /* extern */
s32 _card_info();                             /* extern */
extern s32 D_800287C8[];
extern s32 D_800287E0[];

s32 func_800213C4(s32 arg0) {
    func_800214A4();
    do {

    } while (_card_info(arg0) == 0);
    D_800287E0[0] = 0;
    D_800287C8[0] = 1;
    return 1;
}
