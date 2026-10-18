#include "common.h"

struct S_800BBDEC_4;
struct S_800BBDEC_1;
struct S_800BBDEC_3;
extern void draw_shaded_vertical_quad(struct S_800BBDEC_4 *object, struct S_800BBDEC_1 *position, struct S_800BBDEC_3 *appearance, s32 unused_draw_value);

/* Process each linked state using the signed halfword at data offset 6. */
s32 draw_shaded_quad_chain(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        draw_shaded_vertical_quad(state, context, data, *(s16 *)((s8 *)data + 6));
        next_node = *(void **)((s8 *)state - 8);
        if (next_node == 0) {
            return 0;
        }
        state = (void *)((s8 *)next_node + 32);
        context = (void *)((s32 *)next_node)[2];
        data = (void *)((s32 *)next_node)[3];
    }
}
