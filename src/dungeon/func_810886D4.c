#include "common.h"

extern void func_80175F08() __attribute__((noreturn));

s32 func_810886D4(u8 *arg0, u32 *arg1) {
    if (arg0[0xAE] == 0) {
        register s32 callarg ASM_REG("$4") = 0xBFFF0000;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        register s32 result ASM_REG("$2") = 0;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        ASM_TAILSLOT_PIN_TIED(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80175F08(callarg);
    }
    arg0[0xAE] = 0;
    arg1[5] &= 0xBFFFFFFF;
    return 1;
}
