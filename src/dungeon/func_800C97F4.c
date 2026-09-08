#include "common.h"

typedef struct Node {
    s32 pad[2];
    s32 value1;
    struct Node *value2;
} Node;

#ifdef NON_MATCHING
#define ASM_CLOBBER_A0() ((void)0)
#else
#define ASM_CLOBBER_A0() ASM_CLOBBER("$4")
#endif

extern void func_800CEF6C(void) __attribute__((noreturn));
extern void func_800CEFB8();

s32 func_800CEF54(void *arg0, s32 arg1, void *arg2) {
    register u8 *state ASM_REG("$16") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 one = 1;

    ASM_CLOBBER_A0();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_800CEFB8(state, arg1, arg2, *(s16 *)((u8 *)arg2 + 6), one);
    arg2 = *(Node **)(state - 8);
    if (arg2 != 0) {
        register s32 value1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        state = (u8 *)arg2 + 32;
        value1 = ((Node *)arg2)->value1;
        arg2 = ((Node *)arg2)->value2;
        ASM_USE(state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        ASM_USE(one);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE(value1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_USE(arg2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_800CEF6C();
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return 0;
}
