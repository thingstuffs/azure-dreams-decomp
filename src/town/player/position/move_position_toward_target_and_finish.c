#include "town/player/initialize_record_with_handler_table_api.h"
#include "common.h"
#include "town/player/object.h"
#include "town/player/position.h"


/* Move the position toward its target until the countdown expires, then finish the move. */
void move_position_toward_target_and_finish(u8 *motion, ObjectPosition *position, SpriteFrameState *sprite) {
    s16 steps_left;
    s16 y_steps_left;

    steps_left = (*(u16 *)(motion + 0xA) -= 1);
    if (steps_left > 0) {
        position->x.v += (((s32) *(s16 *)(motion + 0x30) << 16) - position->x.v) / steps_left;
        position->y.v += (((s32) *(s16 *)(motion + 0x32) << 16)
            - position->y.v) / (y_steps_left = *(s16 *)(motion + 0xA));
        return;
    }
    position->x.unsigned_parts.integer = *(u16 *)(motion + 0x30);
    position->y.unsigned_parts.integer = *(u16 *)(motion + 0x32);
    clear_object_velocity(position);
    initialize_record_with_handler_table(motion, (position), sprite);
}
