#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80049D80(s16 *);                       /* extern */

s32 func_80023BE4(s32 arg0, s16 arg1, s16 arg2) {
    s16 sp10;
    s16 sp12;
    s16 sp14;
    s16 sp16;

    sp10 = (s16) ((s16) -arg1 / 2);
    sp14 = arg1;
    sp12 = (s16) ((s16) -arg2 / 2);
    sp16 = arg2;
    func_80049D80(&sp10);
    return arg0;
}
