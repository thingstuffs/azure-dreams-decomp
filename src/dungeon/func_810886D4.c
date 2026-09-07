#include "common.h"

extern void func_80175F08() __attribute__((noreturn));

s32 func_810886D4(u8 *arg0, u32 *arg1) {
    if (arg0[0xAE] == 0) {
        register s32 callarg ASM_REG("$4") = 0xBFFF0000;   /* MATCH pin: retail basic-block layout depends on it */
        register s32 result ASM_REG("$2") = 0;   /* MATCH pin: keeps a statement from moving across a call/branch */

        ASM_TAILSLOT_PIN_TIED(result);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80175F08(callarg);
    }
    arg0[0xAE] = 0;
    arg1[5] &= 0xBFFFFFFF;
    return 1;
}
