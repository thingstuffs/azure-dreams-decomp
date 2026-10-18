#include "modules/dungeon_ovl_7e6b7800.h"

void update_directional_actor_effect(s16 start_x, s16 start_y, s16 start_z, s16 end_x, s16 end_y,
                   s16 end_z, s16 *angles)
{
    struct Row_8194C81C_Delta delta;
    s32 divisor;

    delta.x = end_x - start_x;
    delta.y = end_y - start_y;
    delta.z = end_z - start_z;

    divisor = delta.z;
    if (divisor == 0) {
        divisor = 1;
    }
    angles[0] = -func_80065F90(delta.y, divisor);

    divisor = func_80064710(delta.y * delta.y + delta.z * delta.z);
    if (divisor == 0) {
        divisor = 1;
    }
    angles[1] = func_80065F90(delta.x, divisor);
    angles[2] = 0;
}
