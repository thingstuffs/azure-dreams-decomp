#include "common.h"
#include "shared/game_work.h"
#include "town.h"
#include "town/player.h"

/* D_80083160: shared state table (own view here); this function only touches
 * a u32 field at offset 8 and a s16 field at offset 0xC8 (declared >8 bytes
 * to force %hi/%lo addressing). */

/* Passes the valid shared angle, fixed value 0x120000, and context to accelerate_toward_angle_capped. */
void accelerate_toward_input_angle(ObjectPosition *context)
{
    s16 angle = input_angle_with_offset(g_game_work.buttons, g_game_work.view.camera_rotation.parts.viewAngle);

    if (angle != -1) {
        accelerate_toward_angle_capped(angle, 0x120000, context);
    }
}
