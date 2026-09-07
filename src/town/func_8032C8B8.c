#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern void func_8001ACE8(s32 arg0);
extern void func_8001AD60(s32 arg0);
extern u8 D_8001E259[];
extern u8 D_8001E405[];

#ifndef NON_MATCHING
register u8 *dispatch_result ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
#endif

void *func_800170B8(void) {
    if (func_8001ADE0(0xD53) == 0) {
        func_8001ACE8(0xD53);
#ifndef NON_MATCHING
        dispatch_result = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
        dispatch_result -= 0x1BFB;
#else
        (void)D_8001E405;
#endif
        return;
    }
    func_8001AD60(0xD53);
    return D_8001E259;
}
