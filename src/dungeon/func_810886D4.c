#include "common.h"


/* Requires and clears the object flag at 0xAE, then clears record bit 30. */
s32 func_810886D4(u8 *object, u32 *flag_record) {
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    if (object[0xAE] == 0) {
        result = 0;
    } else {
        object[0xAE] = 0;
        flag_record[5] &= 0xBFFFFFFF;
        result = 1;
    }
    return result;
}
