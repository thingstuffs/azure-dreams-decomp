#include "sdk/libgte.h"
#include "dungeon/effect.h"

/* Compute direction angles between two points, with the third angle set to zero. */
void compute_direction_angles_between_points(s16 start_x, s16 start_y, s16 start_z, s16 end_x, s16 end_y,
                   s16 end_z, s16 *angles)
{
    PositionDelta delta;
    s32 divisor;

    delta.x = end_x - start_x;
    delta.y = end_y - start_y;
    delta.z = end_z - start_z;

    divisor = delta.z;
    if (divisor == 0) {
        divisor = 1;
    }
    angles[0] = -ratan2(delta.y, divisor);

    divisor = SquareRoot0(delta.y * delta.y + delta.z * delta.z);
    if (divisor == 0) {
        divisor = 1;
    }
    angles[1] = ratan2(delta.x, divisor);
    angles[2] = 0;
}
