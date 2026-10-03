#include "common.h"

#include "common.h"

/* Initialize four polygon edges for rasterization and return the aligned minimum y. */
s32 func_80046C20(s32 bottom_vertex, s32 *edges, u16 *edge_count) {
    s32 min_y;
    s32 edge_index;      /* t1 */
    s32 grid_mask;  /* t5 */
    s32 *edge_state;    /* t0 */
    s16 *vertex; /* t2 */
    s32 top_vertex;
    s16 *vertices = (s16 *)bottom_vertex;
    s32 top_y;     /* a3 */
    s32 edge_value;
    s32 *edge_x;
    s32 edge_scratch;
    s32 signed_dx;

    edge_x = edges;
    min_y = 0x7FFF;
    edge_index = 0;
    grid_mask = -0x40;
    edge_state = (s32 *)((char *)edges + 0x1C);
    vertex = vertices;

loop_0:
    {
        top_vertex = vertex[1];
        top_vertex = top_vertex - vertex[5];

        if (top_vertex == 0) {
            *edge_state = -1;
            *edge_count -= 1;
        } else {
            if (top_vertex < 0) {
                top_vertex = edge_index;
                bottom_vertex = edge_index + 1;
            } else {
                top_vertex = edge_index + 1;
                bottom_vertex = edge_index;
            }

            top_vertex <<= 3;
            top_vertex += (s32)vertices;
            *edge_x = ((s16 *)top_vertex)[0];
            edge_value = *(u16 *)(top_vertex + 2) & grid_mask;
            top_y = (edge_value << 16) >> 16;
            edge_state[-1] = top_y;
            if (top_y < min_y) {
                min_y = top_y;
            }

            bottom_vertex <<= 3;
            bottom_vertex += (s32)vertices;
            edge_scratch = ((s16 *)bottom_vertex)[1];
            edge_scratch -= top_y;
            edge_state[-4] = edge_scratch;
            ASM_MEM_BARRIER();
            edge_value = edge_scratch;
            ASM_USE(edge_value);
            edge_value <<= 7;
            edge_state[-3] = edge_scratch;
            edge_state[-6] = edge_value;

            edge_value = ((s16 *)bottom_vertex)[0];
            edge_scratch = *edge_x;
            edge_value = edge_value - edge_scratch;
            edge_state[-2] = edge_value;
            edge_value = __builtin_abs(edge_value);
            edge_state[1] = edge_value;
            signed_dx = edge_state[-2];
            edge_state[-5] = edge_value << 7;
            if (signed_dx > 0) {
                edge_state[-2] = 0x40;
            } else if (signed_dx < 0) {
                edge_state[-2] = grid_mask;
            }
            *edge_state = 0;
            edge_value = edge_state[1] + 0x20;
            edge_state[1] = edge_value;
            edge_state[2] = edge_value;
        }
        vertex += 4;
        edge_index += 1;
        edge_state = (s32 *)((char *)edge_state + 0x28);
        edge_x = (s32 *)((char *)edge_x + 0x28);
    }
    if (edge_index < 4)
        goto loop_0;

    return min_y & -0x40;
}
