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
        register void *pa0 ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        s32 pa1;
        s32 pa2;
        register s32 v0 ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s32 v1;

        pa0 = sp10;
        pa1 = 0x270;
           /* MATCH pin: retail schedule: same instructions, different order without it */
        v0 = *(u16 *)((unsigned char *)arg0 + 2);
        v1 = *(u16 *)((unsigned char *)arg0 + 0xC);
           /* MATCH pin: retail schedule: same instructions, different order without it */
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
