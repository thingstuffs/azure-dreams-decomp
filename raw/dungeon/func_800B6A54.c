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
        register void *pa0 ASM_REG("$4");
        register s32 pa1 ASM_REG("$5");
        register s32 pa2 ASM_REG("$6");
        register s32 v0 ASM_REG("$2");
        register s32 v1 ASM_REG("$3");

        pa0 = sp10;
        pa1 = 0x270;
        ASM_KEEP(pa1);
        v0 = *(u16 *)((unsigned char *)arg0 + 2);
        v1 = *(u16 *)((unsigned char *)arg0 + 0xC);
        ASM_KEEP_MEM(v1);
        pa2 = 0x100;
        ASM_KEEP(pa2);
        v0 = (v0 - v1) & 0x1F;
        *(u16 *)((unsigned char *)arg0 + 2) = (u16)v0;
        v0 = pa1;
        ASM_KEEP(v0);
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
