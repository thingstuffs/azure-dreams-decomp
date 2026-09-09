#include "common.h"

typedef struct Node {
    s32 pad[2];
    s32 value1;
    struct Node *value2;
} Node;

extern void func_800CEFB8();

s32 func_800CEEFC(void *arg0, s32 arg1, void *arg2) {
    u8 *state = arg0;

    for (;;) {
        func_800CEFB8(state, arg1, arg2, *(s16 *)((u8 *)arg2 + 6), 0);
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
