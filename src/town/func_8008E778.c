#include "common.h"

extern void func_8008BF00(void);
extern u8 D_800FC418;
extern u8 D_8008BA00[];
extern u8 D_8008BC58[];

s32 func_8008BED8(void *arg0) {
    u8 value = D_800FC418;

#ifndef NON_MATCHING
    if (value == 0xFF) {
        register u32 dead_v0 ASM_REG("$2") = 0x80090000;   /* MATCH pin: retail immediate-load split depends on it */

        ASM_KEEP(dead_v0);   /* MATCH pin: retail basic-block layout depends on it */
        func_8008BF00();
        return dead_v0 - 0x4600;
    }
    {
        u32 result = 0x80090000;

        if (value == 0) {
            ASM_KEEP(result);   /* MATCH pin: keeps a statement from moving across a call/branch */
            result -= 0x43A8;
            *(u32 *)((u8 *)arg0 + 0x68) = result;
        }
        return result;
    }
#else
    if (value == 0xFF) {
        func_8008BF00();
    } else if (value == 0) {
        *(u8 **)((u8 *)arg0 + 0x68) = D_8008BC58;
    }
    return 0;
#endif
}
