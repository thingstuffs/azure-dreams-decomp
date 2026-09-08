#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern void func_8001ACE8(s32 arg0);
extern void func_800184A0(void) __attribute__((noreturn));
extern void func_800184A4(void) __attribute__((noreturn));
extern void *func_80019DFC(void *arg0, void *arg1, s32 arg2, s32 arg3);

extern u8 D_8001BE24[];
extern u8 D_8001C354[];
extern u8 D_8001DCD4[];
extern u8 D_8001E16A[];
extern u8 D_8001E42A[];

void *func_80018420(s32 arg0, s32 arg1, s32 arg2) {
    void *result;

    if (arg2 == 0x1E) {
        if (func_8001ADE0(0x145E) != 0) {
            if (func_8001ADE0(0x145F) != 0) {
                result = D_8001E42A;
                ASM_TAILSLOT_PIN(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                func_800184A0();
            } else {
                result = D_8001E16A;
                ASM_TAILSLOT_PIN(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                func_800184A0();
            }
        }

        result = D_8001DCD4;
        func_8001ACE8(0x145E);
        {
            register void *tail_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

            tail_result = result;
            ASM_TAILSLOT_PIN(tail_result);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            func_800184A4();
        }
    }

    result = func_80019DFC(D_8001BE24, D_8001C354, arg0, arg2);
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    return result;
}
