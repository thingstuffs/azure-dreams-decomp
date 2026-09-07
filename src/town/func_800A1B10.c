#include "common.h"

extern void func_8009F2A0(void *arg0);
extern void *D_800CFCC4[];

s32 func_8009F270(void) {
    register u8 *ptr ASM_REG("$4") = (u8 *)D_800CFCC4[0];   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    if (ptr != 0) {
        s32 type = 4;

        if (ptr[0x14] == type) {
            func_8009F2A0(ptr);
            return (s32)(ptr + 0x4C);
        }
        return 0;
    }
    return 0;
}
