#include "common.h"

s32 func_8009368C(void *arg0) {
    u8 *ptr = *(u8 **)((u8 *)arg0 + 0x2C);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    if (ptr != 0) {
        s32 type = 4;

        if ((ptr[0x14] == type) || (ptr[0x4D] == 0xD)) {
            return (s32)(ptr + 0x4C);
        }
    }
    return 0;
}
