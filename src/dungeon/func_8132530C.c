#include "common.h"

extern void func_800A4ACC(s32);
extern s32 func_800AB1C0(void);
extern s32 func_800AD9B4(s32, s32);
extern s32 D_8016B778;

void func_8016CB0C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 held_arg2 ASM_REG("$18") = arg2;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    if (func_800AB1C0() != 0) {
        ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_800A4ACC(arg3);
        if ((func_800AD9B4(held_arg2, arg3) << 16) > 0) {
            *(s32 **)((u8 *)arg0 + 0x8c) = &D_8016B778;
            *(s32 *)((u8 *)arg0 + 0x90) = 0;
        }
    }
}
