#include "common.h"

typedef struct Func800C138CData {
    u8 pad0[8];
    void *context;
    void *data;
} Func800C138CData;

extern void draw_sprite_parts_as_quad_grid(s32 context, void *position, void *sprite, s16 depth_bias);

/* Process each linked state with draw_sprite_parts_as_quad_grid in mode zero. */
s32 process_linked_states_mode_zero(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        draw_sprite_parts_as_quad_grid(state, context, data, 0);
        next_node = *((void **)state - 2);
        if (next_node == 0) {
            return 0;
        }
        state = (u8 *)next_node + 0x20;
        context = ((Func800C138CData *)next_node)->context;
        data = ((Func800C138CData *)next_node)->data;
    }
}
