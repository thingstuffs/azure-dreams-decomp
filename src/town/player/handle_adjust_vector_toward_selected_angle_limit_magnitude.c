#include "town/player/position_handlers.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "engine/resource.h"
#include "sdk/libgte.h"
#include "town.h"
#include "town/player.h"

typedef struct {
    u8 pad[0xC];
    s32 x;
    s32 y;
} Func97514Object;

/*
 * Adds sine/cosine input acceleration scaled by 64 and limits the resulting vector to its previous
 * magnitude or 0x80000, whichever is larger.
 */
void handle_adjust_vector_toward_selected_angle_limit_magnitude(ObjectPosition *object) {
    s16 angle;
    s32 delta_x;
    s32 delta_y;
    s32 old_magnitude;
    s32 new_magnitude;

    angle = input_angle_with_offset(g_game_work.buttons, g_game_work.view.camera_rotation.parts.viewAngle);
    if (angle != -1) {
        delta_x = rsin(angle) << 6;
        delta_y = rcos(angle) << 6;
        old_magnitude = runtime_estimate_vector_length(object->velocity_x, object->velocity_y);
        if (old_magnitude <= 0x7FFFF) {
            old_magnitude = 0x80000;
        }
        object->velocity_x += delta_x;
        object->velocity_y += delta_y;
        new_magnitude = runtime_estimate_vector_length(object->velocity_x, object->velocity_y);
        if (old_magnitude < new_magnitude) {
            object->velocity_x = object->velocity_x / ((new_magnitude + 0xFFF) / 0x1000) * (old_magnitude / 0x1000);
            object->velocity_y = object->velocity_y / ((new_magnitude + 0xFFF) / 0x1000) * (old_magnitude / 0x1000);
        }
    }
}
