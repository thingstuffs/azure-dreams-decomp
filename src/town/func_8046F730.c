#include "common.h"

extern s32 func_8001628C();
extern s32 func_80017E98();
extern s32 func_80019880();
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern s32 func_8001A7F8();
extern s32 D_8001A954;
extern s32 D_8001B1F8;
extern s32 D_8001B63C;
extern s32 D_800211DC;

s32 func_80016730(s32 arg0, s32 arg1, s32 arg2) {
    register void *base ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 result;

    if (func_80017E98() != 0) {
        s32 page;

        page = (s32)0x80020000;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        return page - 0x49C4;
    }
    {
        register s32 page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

        ASM_CLOBBER("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        page = (s32)0x80020000;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        base = (void *)(page - 0x56AC);
    }
    result = func_80019ABC(base, &D_8001B1F8, arg0, arg2);
    if (func_8001A7F8() >= 10) {
        register void *call_base ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        s32 page;

        call_base = base;
        ASM_KEEP(call_base);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80019880(call_base);
        page = (s32)0x80020000;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        result = page + 0x11DC;
    }
    if (func_80019A04(base, arg0, arg2) != 0) {
        result = func_8001628C(arg0, arg1, arg2);
    }
    return result;
}

/* MECHANISM: The 0x28 frame falls out of arg0/arg1/arg2 held in s1/s4/s2, with result in s0.
   Short-lived v0 page carriers plus a pinned s3 base reproduce retail's split lui/addiu forms.
   A block-local a0 call carrier removes the duplicate call-slot move and leaves retail's nop. */
