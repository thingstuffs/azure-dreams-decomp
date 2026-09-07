#include "common.h"

extern s32 func_80019370();
extern void func_80019D44();
extern s32 func_80019DFC();
extern s32 D_8001BB4C[];
extern s32 D_8001C354;
extern s32 D_8001FAE8[];

s32 func_800171F4(s32 arg0, s32 arg1, s32 arg2) {
    s32 saved_arg0 = arg0;
    s32 saved_arg2;
    s32 *base;
    s32 result;

    saved_arg2 = arg2;
    base = D_8001BB4C;
    result = func_80019DFC(base, &D_8001C354, saved_arg0, saved_arg2);
    if (saved_arg2 == 7) {
        if (func_80019370() != 0) {
            return result;
        }
        return (s32)D_8001FAE8;
    }
    func_80019D44(base, saved_arg0, saved_arg2);
    return result;
}

/* MECHANISM: Ordinary locals let the four cross-call values allocate naturally as
   s3=arg0, s0=arg2, s2=the held global base, and s1=the first call's result.
   Removing all inherited hard-register pins restores the retail 0x28 frame and
   s3/s0/s2 save-and-copy order; the body CFG then matches without barriers. */
