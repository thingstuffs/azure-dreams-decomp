#include "common.h"


/* Requires and clears the object flag at 0xAE, then clears record bit 30. */
s32 func_810886D4(u8 *object, u32 *flag_record) {
    if (object[0xAE]) {
        object[0xAE] = 0;
        flag_record[5] &= 0xBFFFFFFF;
        return 1;
    }
    return 0;
}
