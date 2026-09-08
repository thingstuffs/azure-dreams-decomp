#include "common.h"

#include "common.h"

/* Initialize four polygon edges for rasterization and return the aligned minimum y. */
s32 func_80046C20(s16 *vertices, s32 *edges, u16 *edge_count) {
    s16 *vertex_base; /* t4 */
    register s32 min_y ASM_REG("$11"); /* t3 */
    register s32 edge_index ASM_REG("$9");      /* t1 */
    s32 grid_mask;  /* t5 */
    register s32 *edge_state ASM_REG("$8");    /* t0 */
    register s16 *vertex ASM_REG("$10"); /* t2 */
    register s32 top_vertex ASM_REG("$3");     /* v1 */
    register s32 bottom_vertex ASM_REG("$4");     /* a0 */
    s32 top_y;     /* a3 */
    register s32 edge_value ASM_REG("$2");    /* v0 */
    s32 *edge_x;
    s32 height;
    s32 signed_dx;

    vertex_base = vertices;
    __asm__ __volatile__("" :: "r"(vertex_base));
    min_y = 0x7FFF;
    edge_index = 0;
    grid_mask = -0x40;
    edge_x = edges;
    edge_state = (s32 *)((char *)edges + 0x1C);
    vertex = vertex_base;

    do {
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

            top_vertex = (top_vertex << 3) + (s32)vertex_base;
            *edge_x = ((s16 *)top_vertex)[0];
            edge_value = *(u16 *)(top_vertex + 2) & grid_mask;
            top_y = (edge_value << 16) >> 16;
            edge_state[-1] = top_y;
            if (top_y < min_y) {
                min_y = top_y;
            }

            bottom_vertex = (bottom_vertex << 3) + (s32)vertex_base;
            height = ((s16 *)bottom_vertex)[1] - top_y;
            edge_state[-4] = height;
            __asm__ __volatile__("" ::: "memory");
            edge_value = height;
            __asm__ __volatile__("" :: "r"(edge_value));
            edge_value <<= 7;
            edge_state[-3] = height;
            edge_state[-6] = edge_value;

            /* reuse edge_value ($v0) for dx so lh lands in v0 like retail */
            edge_value = ((s16 *)bottom_vertex)[0];
            edge_value = edge_value - *edge_x;
            edge_state[-2] = edge_value;
            signed_dx = *(volatile s32 *)&edge_state[-2];
            if (edge_value < 0) {
                edge_value = -edge_value;
            }
            edge_state[1] = edge_value;
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
    } while (edge_index < 4);

    return min_y & -0x40;
}
