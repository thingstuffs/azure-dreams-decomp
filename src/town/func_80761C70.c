#include "common.h"

extern u8 D_80017A20[9];
extern u8 D_80017B5C[9];
extern u8 D_80018CC0[9];
extern u8 D_80018D9F[9];
extern u8 D_80018E42[9];

extern void *func_80016F14(void *, void *, void *, s32);
extern s32 func_80016EB8(void *, void *, s32);
extern void func_800164F8(void) __attribute__((noreturn));
extern void func_8001779C(u16);
extern s32 func_8001781C(s16);
extern s32 func_80017948(s32);

void *func_80761C70(void *arg0, s32 arg1, s32 arg2)
{
    void *result;

    result = func_80016F14(D_80017A20, D_80017B5C, arg0, arg2);
    if (func_80016EB8(D_80017A20, arg0, arg2) != 0) {
        if (func_8001781C(0x9E9) != 0) {
            result = D_80018D9F;
            ASM_TAILSLOT_PIN(result);   /* MATCH pin: retail delay-slot contents depend on it */
            func_800164F8();
        } else {
            ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
            result = D_80018CC0;
            ASM_TAILSLOT_PIN(result);   /* MATCH pin: retail delay-slot contents depend on it */
            func_800164F8();
        }
    } else {
        func_8001779C(0x9E9);
        if (func_80017948(7) != 0) {
            result = D_80018E42;
        }
    }
    return result;
}
