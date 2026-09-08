#include "common.h"

extern void func_80177874(void);
extern void func_801778A0(void);
extern void func_80177A9C(s32 *arg0, u16 arg1);

/* Apply option flags to a command word and dispatch its update. */
void func_80041044(s32 *command, s32 flags)
{
    register s32 command_word ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 bit_mask ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    if (flags & 1) {
        bit_mask = 0xF7FF0000;
        __asm__ volatile("" : "=r"(bit_mask) : "0"(bit_mask));
        command_word = *command;
        bit_mask |= 0xFFFF;
        __asm__ volatile(
            ".set\tnoreorder\n"
            "\t.set\tnomacro\n"
            "\tj func_80177874\n"
            "\tand $2,$2,$3\n"
            "\t.set\tmacro\n"
            "\t.set\treorder"
            :
            : "r"(command_word), "r"(bit_mask));
    }

    *command |= 0x08000000;
    __asm__ volatile("" ::: "memory");

    if (flags & 2) {
        bit_mask = 0x02000000;
        command_word = *command;
        __asm__ volatile(
            ".set\tnoreorder\n"
            "\t.set\tnomacro\n"
            "\tj func_801778A0\n"
            "\tor $2,$2,$3\n"
            "\t.set\tmacro\n"
            "\t.set\treorder"
            :
            : "r"(command_word), "r"(bit_mask));
    }

    *command &= 0xFDFFFFFF;
    func_80177A9C(command, *(u16 *)command);
}
