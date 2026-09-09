#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern u8 D_8001ED0E[];

register u8 *dispatch_result ASM_REG("$2");

void *func_80018674(void) {
    if (func_8001ADE0(0xD81) == 0) {
        dispatch_result = (u8 *)0x80020000;
        ASM_KEEP(dispatch_result);
        dispatch_result -= 0x13CB;
        goto merge;
    }
    ASM_SCHED_BARRIER();
    dispatch_result = D_8001ED0E;
merge:
    return (void *)dispatch_result;
}
