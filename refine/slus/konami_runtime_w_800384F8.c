#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80038538();                         /* extern */
s32 func_80053EF0();                         /* extern */

/* Advance the object's callback once the channel 4 blocking status clears. */
void func_800384F8(s32 object) {
    if (func_80053EF0(4) != 0x100) {
        func_80038538(object);
    }
}
