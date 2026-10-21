#include "common.h"
#include "shared/game_work.h"

extern void update_projected_effect_points(void *, s32, s32, s32);
extern void queue_adjacent_shaded_quads(void *);
extern s32 find_target_byte_index_in_list(void);
extern s32 ring_segment_counts[];
extern s32 ring_segment_count;

/* Draws a closed ring of shaded quads using evenly spaced angular samples. */
void draw_shaded_quad_ring(s32 shape, s32 source)
{
    u32 *scratch;
    s32 segment;
    s16 angle_sum;
    s16 angle;
    u32 saved_outer_xy;
    u32 saved_inner_xy;
    u32 saved_middle_xy;
    u32 saved_color;

    angle_sum = 0;
    scratch = (u32 *)0x1F800000;
    ring_segment_count = ring_segment_counts[find_target_byte_index_in_list()];
    scratch[0x24 / 4] = (s32)g_game_work.draw_buffer + 0xB0;
    update_projected_effect_points(scratch, 0, source, shape);
    saved_color = scratch[0x118 / 4] = scratch[0x114 / 4];
    saved_inner_xy = scratch[0xF0 / 4] = scratch[0xE8 / 4];
    saved_middle_xy = scratch[0xF4 / 4] = scratch[0xEC / 4];
    saved_outer_xy = scratch[0x128 / 4] = scratch[0x124 / 4];

    for (segment = 0; segment < ring_segment_count - 1; segment++) {
        angle = angle_sum + 0x1000 / ring_segment_count;
        angle_sum = angle;
        update_projected_effect_points(scratch, angle, source, shape);
        if (scratch[0xC4 / 4] < 0x1E0U) {
            queue_adjacent_shaded_quads(scratch);
        }
        scratch[0x118 / 4] = scratch[0x114 / 4];
        scratch[0xF0 / 4] = scratch[0xE8 / 4];
        scratch[0xF4 / 4] = scratch[0xEC / 4];
        scratch[0x128 / 4] = scratch[0x124 / 4];
    }

    angle = angle_sum + 0x1000 / ring_segment_count;
    update_projected_effect_points(scratch, angle, source, shape);
    scratch[0x114 / 4] = saved_color;
    scratch[0xE8 / 4] = saved_inner_xy;
    scratch[0xEC / 4] = saved_middle_xy;
    scratch[0x124 / 4] = saved_outer_xy;
    if (scratch[0xC4 / 4] < 0x1E0U) {
        queue_adjacent_shaded_quads(scratch);
    }
}
