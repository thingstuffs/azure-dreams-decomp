#include "common.h"

/* Unaligned 4-byte copy → lwl/lwr + swl/swr */
typedef struct {
    u32 v;
} __attribute__((packed)) UA32;

extern UA32 D_80028064;

s32 func_80025E54(void *arg0, s32 arg1, s32 arg2, void *arg3);
s32 func_80025ECC(void);
void func_80025F0C(void *arg0, s32 arg1);
void func_80025FFC(void *arg0, s32 arg1);

/*
 * Retail materializes &D_80028064 as lui $v0,0x8003 / addiu $a3,$v0,-32668
 * (two-reg la), keeps that pointer in $a3 for the unaligned copy and as the
 * 4th arg to func_80025E54, and leaves a0/a1 live so the call is effectively
 * func_80025E54(arg0, arg1, (arg2==2), &D_80028064). Page base 0x80010000
 * is held in $s0 (lui only). The $a2 pin + ASM_KEEP after the copy stops
 * the (arg2==2) xori/sltiu from floating above the unaligned block.
 */
void func_80026128(UA32 *arg0, s32 arg1, s32 arg2) {
    register u32 hi ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    UA32 *src;
    s32 a2r;
    u8 *p;
    s16 temp;

    /* &D_80028064 == 0x80030000 - 32668 */
    hi = 0x80030000;
    ASM_KEEP(hi);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    src = (UA32 *)(hi - 32668);
    ASM_KEEP(src);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    *arg0 = *src;

    a2r = arg2;
    ASM_KEEP(a2r);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    p = (u8 *)0x80010000;
    temp = (a2r == 2);
    *(s16 *)(p + 0x208) = temp;
    *(s16 *)(p + 0x20A) = temp;
    *(s32 *)(p + 0x224) = *(s32 *)(p + 0x2D5C);
    *(s32 *)(p + 0x230) = func_80025E54(arg0, arg1, temp, src);
    *(s32 *)(p + 0x228) = func_80025ECC();
    func_80025F0C(arg0, arg1);
    func_80025FFC(arg0, arg1);
}
