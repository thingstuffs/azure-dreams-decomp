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

extern void func_800CEFB8();

s32 func_800CEF54(void *arg0, s32 arg1, void *arg2) {
    register u8 *state ASM_REG("$16") = arg0;
    s32 one = 1;

    ASM_CLOBBER_A0();
    for (;;) {
        func_800CEFB8(state, arg1, arg2, *(s16 *)((u8 *)arg2 + 6), one);
        arg2 = *(Node **)(state - 8);
        if (arg2 == 0) {
            break;
        }
        state = (u8 *)arg2 + 32;
        arg1 = ((Node *)arg2)->value1;
        arg2 = ((Node *)arg2)->value2;
    }
    return 0;
}
