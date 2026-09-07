#include "common.h"

extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_800960E4(void);
extern s32 D_8008ACDC;

#ifndef NON_MATCHING
register u8 *dispatch_result ASM_REG("$2");
#define KEEP_DISPATCH() \
    ASM_KEEP(dispatch_result)
#endif

void func_80096088(void *arg0in, void *arg1in) {
#ifndef NON_MATCHING
    register void *arg0 ASM_REG("$17");
    register void *arg1 ASM_REG("$16");
#else
    void *arg0;
    void *arg1;
#endif
    arg0 = arg0in;
    arg1 = arg1in;

#ifndef NON_MATCHING
    {
        register s32 cond1 ASM_REG("$2");
        cond1 = func_80042900(arg1, 10) << 16;
        if (cond1 != 0) {
            dispatch_result = (u8 *)0x80090000;
            KEEP_DISPATCH();
            dispatch_result += 0x6384;
            func_800960E4();
            return;
        }
    }
    dispatch_result = (u8 *)0x80090000;
    KEEP_DISPATCH();

    {
        register s32 cond2 ASM_REG("$2");
        cond2 = *(s32 *)((u8 *)arg1 + 0x1C);
        cond2 &= 0x100000;
        if (cond2 != 0) {
            dispatch_result = (u8 *)0x80090000;
            KEEP_DISPATCH();
            dispatch_result -= 5432;
            func_800960E4();
            return;
        }
    }
    dispatch_result = (u8 *)0x80090000;
    KEEP_DISPATCH();

    {
        register u8 *result ASM_REG("$2");
        result = (u8 *)&D_8008ACDC;
        *(void **)((u8 *)arg0 + 0x8C) = result;
    }
#else
    if ((func_80042900(arg1, 10) << 16) != 0) {
        func_800960E4();
        return;
    }
    if ((*(s32 *)((u8 *)arg1 + 0x1C) & 0x100000) != 0) {
        func_800960E4();
        return;
    }
    *(void **)((u8 *)arg0 + 0x8C) = &D_8008ACDC;
#endif
}
