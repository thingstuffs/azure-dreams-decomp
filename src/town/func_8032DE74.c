#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern u8 D_8001ED0E[];

#ifndef NON_MATCHING
register u8 *dispatch_result ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
#endif

void *func_80018674(void) {
    if (func_8001ADE0(0xD81) == 0) {
#ifndef NON_MATCHING
        dispatch_result = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
        dispatch_result -= 0x13CB;
#endif
        return;
    }
    return D_8001ED0E;
}
