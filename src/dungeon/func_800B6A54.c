#include "common.h"

#ifdef NON_MATCHING
#define ASM_KEEP_MEM(var) ((void)0)
#else
#define ASM_KEEP_MEM(var) __asm__ __volatile__("" : "+r"(var) :: "memory")
#endif

extern void func_800673A0();

void func_800BC1B4(void *arg0) {
    s16 sp10[4];

    {
        register void *pa0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        s32 pa1;
        s32 pa2;
        register s32 v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        s32 v1;

        pa0 = sp10;
        pa1 = 0x270;
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        v0 = *(u16 *)((unsigned char *)arg0 + 2);
        v1 = *(u16 *)((unsigned char *)arg0 + 0xC);
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        pa2 = 0x100;
        v0 = (v0 - v1) & 0x1F;
        *(u16 *)((unsigned char *)arg0 + 2) = (u16)v0;
        v0 = pa1;
        sp10[0] = v0;
        v1 = *(u16 *)((unsigned char *)arg0 + 2);
        v0 = 0x10;
        sp10[2] = v0;
        v0 = 0x20;
        sp10[3] = v0;
        v1 = v1 + 0x140;
        sp10[1] = v1;
        func_800673A0(pa0, pa1, pa2, arg0);
    }
    func_800673A0(sp10, 0x270, 0x120);
}
