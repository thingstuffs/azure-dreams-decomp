/* Relink of matched dungeon/func_800C138C; every changed retail word is a paired relocation. */
#include "common.h"

typedef struct Func800C138CData {
    u8 pad0[8];
    void *context;
    void *data;
} Func800C138CData;

extern void func_801663AC(void *, void *, void *, s16);

/* Process each linked state with func_801663AC in mode zero. */
s32 func_80166914(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        func_801663AC(state, context, data, 0);
        next_node = *((void **)state - 2);
        if (next_node == 0) {
            return 0;
        }
        state = (u8 *)next_node + 0x20;
        context = ((Func800C138CData *)next_node)->context;
        data = ((Func800C138CData *)next_node)->data;
    }
}
