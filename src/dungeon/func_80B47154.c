#include "modules/dungeon_resource12_slot0.h"

s32 func_80174954(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        transform_and_queue_line_packets(state, context, data,(s16)(0));
        next_node = *((void **)state - 2);
        if (next_node == 0) {
            return 0;
        }
        state = (u8 *)next_node + 0x20;
        context = ((R12_80174954_Func800C138CData *)next_node)->context;
        data = ((R12_80174954_Func800C138CData *)next_node)->data;
    }
}
