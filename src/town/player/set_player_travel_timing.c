#include "common.h"
#include "town/person/position.h"
#include "engine/resource.h"
#include "sdk/libc.h"
#include "town/player.h"
#include "town/player/position.h"
#include "shared/object_index_slots.h"
#include "slus.h"
#include "town/data.h"

#include "town/player/initialize_record_with_handler_table_api.h"
#include "shared/sprite_frame_state.h"
/* Set travel timing from distance and speed, or snap motion to the destination. */
void set_player_travel_timing(void *actor, ObjectPosition *motion, SpriteFrameState *sprite)
{
    s32 base_ticks;
    s32 scaled_ticks;
    s32 distance;
    s32 speed_modifier;
    s32 modifier_magnitude;
    s8 *movement_state;
    *(((*((s32 *) (((s8 *) actor) + 0x40))) * 8) + ((u8 *)object_index_slots)) = 0;
    *((s32 **) (((s8 *) actor) + 4)) = &advance_player_position_and_angle;
    distance = estimate_vector_length(((*((s16 *) (((s8 *) actor) + 0x36))) << 0x10) - motion->x.v,
        ((*((s16 *) (((s8 *) actor) + 0x38))) << 0x10) - motion->y.v);
    if (distance < 0) {
        distance += 0x1FFFF;
    }
    movement_state = (s8 *) (((*((s32 *) (((s8 *) actor) + 0x40))) * 8) + ((u8 *)object_index_slots));
    base_ticks = distance >> 0x11;
    *((s16 *) (((s8 *) actor) + 0xA)) = (s16) base_ticks;
    speed_modifier = *((movement_state + 2));
    if (speed_modifier == (-0x80)) {
        motion->x.v = (s32) ((*((s16 *) (((s8 *) actor) + 0x36))) << 0x10);
        motion->y.v = (s32) ((*((s16 *) (((s8 *) actor) + 0x38))) << 0x10);
        motion->z.unsigned_parts.integer = (u16) (motion->z.unsigned_parts.integer - 0x80);
        motion->z.unsigned_parts.integer = query_lowered_transform_position(motion);
        initialize_record_with_handler_table(actor, (motion), sprite);
        return;
    }
    if (speed_modifier > 0) {
        *((s16 *) (((s8 *) actor) + 0xA)) = (s16) ((base_ticks << 4) / (speed_modifier + 0x10));
        return;
    }
    if (speed_modifier < 0) {
        modifier_magnitude = abs(speed_modifier);
        scaled_ticks = base_ticks * (modifier_magnitude + 0x10);
        *((s16 *) (((s8 *) actor) + 0xA)) = (s16) (scaled_ticks / 16);
    }
}
