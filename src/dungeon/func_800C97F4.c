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

/* Process each linked state with func_800CEFB8 in mode one. */
s32 func_800CEF54(void *initial_state, s32 value, void *data) {
    u8 *state = initial_state;
    s32 mode = 1;

    for (;;) {
        func_800CEFB8(state, value, data, *(s16 *)((u8 *)data + 6), mode);
        data = *(Node **)(state - 8);
        if (data == 0) {
            break;
        }
        state = (u8 *)data + 32;
        value = ((Node *)data)->value1;
        data = ((Node *)data)->value2;
    }
    return 0;
}
