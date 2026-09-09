#include "common.h"

extern void func_800BBDEC(void *arg0, void *arg1, void *arg2, s16 arg3);

/* Process each linked state using the signed halfword at data offset 6. */
s32 func_800BC054(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        func_800BBDEC(state, context, data, *(s16 *)((s8 *)data + 6));
        next_node = *(void **)((s8 *)state - 8);
        if (next_node == 0) {
            return 0;
        }
        state = (void *)((s8 *)next_node + 32);
        context = (void *)((s32 *)next_node)[2];
        data = (void *)((s32 *)next_node)[3];
    }
}
