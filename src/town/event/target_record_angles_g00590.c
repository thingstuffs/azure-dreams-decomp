/* inferred-strong G00590: target_record_angles_g00590; joins CL:town/func_800AC708,CL:town/func_800AC9AC,PD:town/engine:80100D18,PD:town/engine:80100D40,PD:town/engine:80100D42; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC708, CL:town/func_800AC9AC, PD:town/engine:80100D18, PD:town/engine:80100D40, PD:town/engine:80100D42. */
#include "town/event/target_record_angles_g00590.h"

/* Initialize and apply the two town records to the target. */
void apply_two_records_to_target(s32 target, s32 setup_data)
{
    s32 record_value;
    s32 record_value2;

    draw_random_colored_line(setup_data, target);

    record_value = (s16)D_80100D18 / 2;
    D_800D1178.field10 = record_value;
    D_800D1178.field14 = record_value;
    D_800D1178.field18 = record_value;
    D_800D1178.fieldA = -D_80100D40;
    transform_and_queue_mesh_quads(&D_800D1178, target);

    record_value2 = (s16)D_80100D18;
    D_800D119C.field10 = record_value2;
    D_800D119C.field14 = record_value2;
    D_800D119C.field18 = record_value2;
    D_800D119C.field8 = D_80100D42;
    transform_and_queue_mesh_quads(&D_800D119C, target);
}

static inline s32 add_x_and_get_angle(IntVector3 *position, s32 x_offset, PositionRotationPair *rotation)
{
    s32 next_angle = rotation->angle;
    position->x += x_offset;
    return next_angle;
}

/* Update global positions using angle-based and fixed offsets from the origin. */
void update_positions_from_origin(IntVector3 *origin)
{
    s32 angle;
    s32 scale;
    IntVector3 *position = &D_80100D68;
    s16 initial_angle;

    ++origin;
    --origin;
    D_80100D40 += town_motion_x_step;
    {
        PositionRotationPair *rotation = &D_80100D60;

        initial_angle = rotation->angle;
        angle = initial_angle;
        position->x = origin->x;
        position->y = origin->y;
        position->z = origin->z;
        D_80100D42 += town_motion_y_step;
        position->y += func_80064584(add_x_and_get_angle(
            position, func_800644B8(angle) * D_80100D1C, rotation)) * D_80100D1C;
        draw_random_colored_line((s32)position, (s32)origin);
        scale = D_80100D1C;
        D_80100D48.x = origin->x + scale * 0x1800;
        D_80100D48.y = origin->y;
        D_80100D48.z = origin->z;
        apply_two_records_to_target((s32)&D_80100D48, (s32)origin);
    }
}
