#include "common.h"

extern void func_800C96E8();
extern void func_800C967C(void) __attribute__((noreturn));

s32 func_800C9664(void *arg0, void *arg1) {
    register u8 *base ASM_REG("$16") = arg0;   /* MATCH pin: retail register colouring depends on it */
    register u8 *scratch ASM_REG("$17") = (u8 *)0x1F800000;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u8 *next ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 offset;

    ASM_CLOBBER("$4");   /* MATCH pin: load-bearing for the whole function shape */
    offset = (s32)((u32)*(u16 *)base << 16) >> 17;
    *(u16 *)(scratch + 0xB8) = *(u16 *)((u8 *)arg1 + 2) - offset;
    *(u16 *)(scratch + 0xBA) = *(u16 *)((u8 *)arg1 + 6);
    *(s32 *)(scratch + 0xC0) = *(s16 *)((u8 *)arg1 + 10);
    func_800C96E8(base, scratch);
    next = *(u8 **)(base - 8);
    if (next != 0) {
        base = next + 0x20;
        next = *(u8 **)(next + 8);
        ASM_KEEP(base);   /* MATCH pin: retail delay-slot contents depend on it */
        ASM_KEEP(next);   /* MATCH pin: retail basic-block layout depends on it */
        func_800C967C();
    }
    ASM_CLOBBER("$5");   /* MATCH pin: retail basic-block layout depends on it */
    return 0;
}
