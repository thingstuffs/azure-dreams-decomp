#include "modules/dungeon_resource06_slot0.h"

s32 func_8017489C(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        dungeonProjectAndQueueTexturedQuad(state, context, data,(s16)(0));
        next_node = *((void **)state - 2);
        if (next_node == 0) {
            return 0;
        }
        state = (u8 *)next_node + 0x20;
        context = ((R06_8017489C_Func800C138CData *)next_node)->context;
        data = ((R06_8017489C_Func800C138CData *)next_node)->data;
    }
}
