#include "common.h"
#include "shared/types3a_types.h"


extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void draw_random_colored_line(IntVector3 * , IntVector3 *);
extern void apply_two_records_to_target(IntVector3 * , IntVector3 *);
extern s32 D_80100D1C;
extern u16 D_80100D40, D_80100D42, D_80100D80, D_80100D82;
extern IntVector3 D_80100D48, D_80100D68;
extern PositionRotationPair D_80100D60;

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
    D_80100D40 += D_80100D80;
    {
        PositionRotationPair *rotation = &D_80100D60;

        initial_angle = rotation->angle;
        angle = initial_angle;
        position->x = origin->x;
        position->y = origin->y;
        position->z = origin->z;
        D_80100D42 += D_80100D82;
        position->y += func_80064584(add_x_and_get_angle(
            position, func_800644B8(angle) * D_80100D1C, rotation)) * D_80100D1C;
        draw_random_colored_line(position, origin);
        scale = D_80100D1C;
        D_80100D48.x = origin->x + scale * 0x1800;
        D_80100D48.y = origin->y;
        D_80100D48.z = origin->z;
        apply_two_records_to_target(&D_80100D48, origin);
    }
}
