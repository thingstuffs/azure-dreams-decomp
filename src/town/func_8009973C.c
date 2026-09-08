#include "common.h"

/* Push the point to the nearest edge of each containing rectangle and return the hit side flags. */
s32 func_80096E9C(s32 *x, s32 *y) {
    s32 nearest_side[2];
    s32 edge_dist[4];
    register volatile s32 *bounds_page ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register volatile s32 *bounds ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 hit_sides;
    s32 first_min_x;
    s32 min_y_side;

    bounds_page = (volatile s32 *)0x80100000;
    ASM_KEEP(bounds_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    first_min_x = *(volatile s32 *)((s8 *)bounds_page - 0x1AE0);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    hit_sides = 0;
    if (first_min_x != 0x80000000) {
        min_y_side = 2;
        bounds = (volatile s32 *)((s8 *)bounds_page - 0x1AE0);
        do {
            edge_dist[0] = *x - bounds[0];
            if (edge_dist[0] > 0) {
                edge_dist[1] = bounds[1] - *x;
                if (edge_dist[1] > 0) {
                    edge_dist[2] = *y - bounds[2];
                    if (edge_dist[2] > 0) {
                        edge_dist[3] = bounds[3] - *y;
                        if (edge_dist[3] > 0) {
                            if (edge_dist[1] < edge_dist[0]) {
                                edge_dist[0] = edge_dist[1];
                                nearest_side[0] = 1;
                            } else {
                                nearest_side[0] = 0;
                            }
                            if (edge_dist[2] > edge_dist[3]) {
                                edge_dist[2] = edge_dist[3];
                                nearest_side[1] = 3;
                            } else {
                                nearest_side[1] = min_y_side;
                            }
                            if (edge_dist[0] > edge_dist[2]) {
                                if (nearest_side[1] == min_y_side) {
                                    hit_sides |= 0x100;
                                    *y = bounds[2];
                                } else {
                                    hit_sides |= 0x1000;
                                    *y = bounds[3];
                                }
                            } else if (nearest_side[0] == 0) {
                                hit_sides |= 1;
                                *x = bounds[0];
                            } else {
                                hit_sides |= 0x10;
                                *x = bounds[1];
                            }
                        }
                    }
                }
            }
            bounds += 4;
        } while (bounds[0] != 0x80000000);
    }
    return hit_sides;
}
