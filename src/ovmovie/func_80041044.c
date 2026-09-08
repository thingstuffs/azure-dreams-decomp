#include "common.h"

extern void func_80177874(void);
extern void func_801778A0(void);
extern void func_80177A9C(s32 *arg0, u16 arg1);

void func_80041044(s32 *arg0, s32 arg1)
{
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 mask ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    if (arg1 & 1) {
        mask = 0xF7FF0000;
        __asm__ volatile("" : "=r"(mask) : "0"(mask));
        value = *arg0;
        mask |= 0xFFFF;
        __asm__ volatile(
            ".set\tnoreorder\n"
            "\t.set\tnomacro\n"
            "\tj func_80177874\n"
            "\tand $2,$2,$3\n"
            "\t.set\tmacro\n"
            "\t.set\treorder"
            :
            : "r"(value), "r"(mask));
    }

    *arg0 |= 0x08000000;
    __asm__ volatile("" ::: "memory");

    if (arg1 & 2) {
        mask = 0x02000000;
        value = *arg0;
        __asm__ volatile(
            ".set\tnoreorder\n"
            "\t.set\tnomacro\n"
            "\tj func_801778A0\n"
            "\tor $2,$2,$3\n"
            "\t.set\tmacro\n"
            "\t.set\treorder"
            :
            : "r"(value), "r"(mask));
    }

    *arg0 &= 0xFDFFFFFF;
    func_80177A9C(arg0, *(u16 *)arg0);
}
