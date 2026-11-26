#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "town/map.h"
#include "town/map/effect.h"
#include "town/shop.h"
#include "town/data.h"

/* Draws a closed ring of shaded quads using evenly spaced angular samples. */
void draw_shaded_quad_ring(SpriteFrameState *shape, ObjectPosition *source)
{
    TownRingProjection *scratch;
    GpuContext *draw_buffer;
    s32 segment;
    s16 angle_sum;
    s16 angle;
    u32 saved_outer_xy;
    u32 saved_inner_xy;
    u32 saved_middle_xy;
    u32 saved_color;

    angle_sum = 0;
    scratch = (TownRingProjection *)0x1F800000;
    ring_segment_count = ring_segment_counts[find_target_index_in_list()];
    draw_buffer = g_game_work.draw_buffer;
    scratch->ordering_table = &draw_buffer->orderTag[GPU_ORDER_DEPTH_BASE];
    update_projected_effect_points(scratch, 0, source, shape);
    saved_color = scratch->previous_color.word = scratch->color.word;
    saved_inner_xy = scratch->previous_inner_xy = scratch->inner_xy;
    saved_middle_xy = scratch->previous_middle_xy = scratch->middle_xy;
    saved_outer_xy = scratch->previous_outer_xy = scratch->outer_xy;

    for (segment = 0; segment < ring_segment_count - 1; segment++) {
        angle = angle_sum + 0x1000 / ring_segment_count;
        angle_sum = angle;
        update_projected_effect_points(scratch, angle, source, shape);
        if ((u32)scratch->depth_index < 0x1E0U) {
            queue_adjacent_shaded_quads(scratch);
        }
        scratch->previous_color.word = scratch->color.word;
        scratch->previous_inner_xy = scratch->inner_xy;
        scratch->previous_middle_xy = scratch->middle_xy;
        scratch->previous_outer_xy = scratch->outer_xy;
    }

    angle = angle_sum + 0x1000 / ring_segment_count;
    update_projected_effect_points(scratch, angle, source, shape);
    scratch->color.word = saved_color;
    scratch->inner_xy = saved_inner_xy;
    scratch->middle_xy = saved_middle_xy;
    scratch->outer_xy = saved_outer_xy;
    if ((u32)scratch->depth_index < 0x1E0U) {
        queue_adjacent_shaded_quads(scratch);
    }
}
