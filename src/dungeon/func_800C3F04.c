#include "common.h"

extern void func_800C96E8();
extern void func_800C967C(void) __attribute__((noreturn));

s32 func_800C9664(void *arg0, void *arg1) {
    register u8 *base ASM_REG("$16") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *scratch ASM_REG("$17") = (u8 *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register u8 *next ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 offset;

    ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    offset = (s32)((u32)*(u16 *)base << 16) >> 17;
    *(u16 *)(scratch + 0xB8) = *(u16 *)((u8 *)arg1 + 2) - offset;
    *(u16 *)(scratch + 0xBA) = *(u16 *)((u8 *)arg1 + 6);
    *(s32 *)(scratch + 0xC0) = *(s16 *)((u8 *)arg1 + 10);
    func_800C96E8(base, scratch);
    next = *(u8 **)(base - 8);
    if (next != 0) {
        base = next + 0x20;
        next = *(u8 **)(next + 8);
        ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(next);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_800C967C();
    }
    ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return 0;
}
