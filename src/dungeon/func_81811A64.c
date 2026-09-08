#include "common.h"

extern void *func_8003FC64();
extern s32 func_800269E8();
extern s32 func_800267B0();
extern void func_800269A0();
extern void func_8004491C();
extern void *func_80026B20() __attribute__((noreturn));
extern void func_8004B1A4();
extern u8 D_8004CAA0[];
extern s32 D_800814A0;

void *func_80026A64(s32 arg0, s32 arg1, s32 arg2) {
    u8 *obj;
    u8 *sub;

    obj = func_8003FC64(0);
    sub = obj + 0x20;
    if (obj != 0) {
        if (func_800269E8(sub) != 0) {
            register void *tail_obj ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */

            *(void **)(obj + 0xC) = obj + 0x80;
            *(s32 *)(sub + 0x6C) = func_800267B0(*(s32 *)(sub + 0x70));
            func_800269A0(sub, arg0, arg1, arg2);
            func_8004491C(obj, D_8004CAA0);
            tail_obj = obj;
            ASM_TAILSLOT_PIN(tail_obj);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            return func_80026B20();
        }
        func_8004B1A4(*(s32 *)(sub + 0x74));
        *(u16 *)(obj + 0x1E) |= 0x8000;
        obj = 0;
        D_800814A0 |= 0x8000;
    }
    return obj;
}

/* MECHANISM: The unchanged seed preserves retail's 0x28 frame and s2/s3/s4/s1/s0 save order.
   A short-lived $v0 tail carrier holds obj only after the last call; LEAD 28b sinks move v0,s0
   into the converted noreturn j delay slot, closing the sole delay-slot substitution. */
