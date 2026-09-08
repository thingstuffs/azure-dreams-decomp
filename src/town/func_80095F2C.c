#include "common.h"

s32 func_8009368C(void *arg0) {
    register u8 *ptr ASM_REG("$4") = *(u8 **)((u8 *)arg0 + 0x2C);   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    if (ptr != 0) {
        s32 type = 4;

        if ((ptr[0x14] == type) || (ptr[0x4D] == 0xD)) {
            return (s32)(ptr + 0x4C);
        }
    }
    return 0;
}
