#include "common.h"

typedef struct Func800C138CData {
    u8 pad0[8];
    void *arg1;
    void *arg2;
} Func800C138CData;

extern void func_800C6B40(void *arg0, void *arg1, void *arg2, s32 arg3);

/* Process each linked state with func_800C6B40 in mode zero. */
s32 func_800C6AEC(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        func_800C6B40(state, context, data, 0);
        next_node = *((void **)state - 2);
        if (next_node == 0) {
            return 0;
        }
        state = (u8 *)next_node + 0x20;
        context = ((Func800C138CData *)next_node)->arg1;
        data = ((Func800C138CData *)next_node)->arg2;
    }
}
