#include "common.h"
#include "sdk/libgte.h"
#include "town/map/animation.h"
#include "town/map/effect.h"
#include "shared/sprite_frame_state.h"





/* Updates three offset points, their projected coordinates, and phase-based intensities. */
void update_projected_effect_points(TownRingProjection *object, s32 phase, ObjectPosition *source, SpriteFrameState *extent) {
    u32 phase_bits;
    s32 offset_phase;
    s32 double_phase;
    s32 y_offset;
    s32 x_offset;
    SVECTOR *start_point;
    s32 *projection_scale;
    s32 *projection_flags;
    SVECTOR *mid_point;
    SVECTOR *end_point;
    u16 z_extent;

    phase_bits = (u32) phase + 0x800;
    offset_phase = (s16)(phase_bits + 0);
    double_phase = offset_phase << 1;
    object->color.c.r = ((rsin((source->velocity_x >> 16) + double_phase) + 0x1000) / 128);
    object->color.c.g = ((rsin((source->velocity_y >> 16) + double_phase) + 0x1000) / 128);
    object->color.c.b = ((rsin((source->velocity_z >> 16) + double_phase) + 0x1000) / 128);
    start_point = &object->start_point;
    copy_position_integer_parts(start_point, source);
    mid_point = &object->mid_point;
    copy_position_integer_parts(mid_point, source);
    end_point = &object->end_point;
    copy_position_integer_parts(end_point, source);
    x_offset = (rsin(offset_phase) * extent->scale_x) / 4096;
    y_offset = (rcos(offset_phase) * extent->scale_y) / 4096;
    projection_scale = &object->projection_scale;
    projection_flags = &object->projection_flags;
    object->start_point.vx = (object->start_point.vx + x_offset);
    object->start_point.vy = (object->start_point.vy + y_offset);
    object->depth_index = RotTransPers(start_point, &object->inner_xy, projection_scale, projection_flags);
    object->mid_point.vx = (object->mid_point.vx + x_offset);
    object->mid_point.vy = (object->mid_point.vy + y_offset);
    z_extent = extent->offset_x;
    object->mid_point.vz = (object->mid_point.vz + ((s16) z_extent / 2));
    object->depth_index = ((object->depth_index + RotTransPers(mid_point, &object->middle_xy,
        projection_scale, projection_flags)) / 2) - 8;
    object->end_point.vx = (object->end_point.vx + x_offset);
    object->end_point.vy = (object->end_point.vy + y_offset);
    object->end_point.vz = (object->end_point.vz + extent->offset_x);
    RotTransPers(end_point, &object->outer_xy, projection_scale, projection_flags);
}
