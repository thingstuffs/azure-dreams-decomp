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

extern void func_800CEF0C(void) __attribute__((noreturn));
extern void func_800CEFB8();

s32 func_800CEEFC(void *arg0, s32 arg1, void *arg2) {
    register u8 *state ASM_REG("$16") = arg0;   /* MATCH pin: retail register colouring depends on it */

    ASM_CLOBBER_A0();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_800CEFB8(state, arg1, arg2, *(s16 *)((u8 *)arg2 + 6), 0);
    arg2 = *(Node **)(state - 8);
    if (arg2 != 0) {
        register s32 value1 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */

        state = (u8 *)arg2 + 32;
        value1 = ((Node *)arg2)->value1;
        arg2 = ((Node *)arg2)->value2;
        ASM_USE(state);   /* MATCH pin: retail delay-slot contents depend on it */
        ASM_USE(value1);   /* MATCH pin: retail basic-block layout depends on it */
        ASM_USE(arg2);   /* MATCH pin: retail basic-block layout depends on it */
        func_800CEF0C();
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    return 0;
}
