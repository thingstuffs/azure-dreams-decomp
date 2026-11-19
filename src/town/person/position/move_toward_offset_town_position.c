#include "town/person/position_callbacks_api.h"
#include "town/person/offset_target_data.h"
#include "common.h"

#include "town/person/object_setup.h"
#include "town/person/object.h"

/* Moves the position toward the town coordinates plus a vertical offset until the countdown expires. */
void move_toward_offset_town_position(TownObjectRecord *actor, ObjectPosition *position, SpriteFrameState *completion_arg)
{
    TownOffsetTargetCoords *coords;
    s32 coord_x;
    s32 base_y;
    s32 coord_y;
    s32 ticks_left;
    u32 target_x;
    u32 target_y;
    u16 countdown;

    coords = person_offset_target_owner->coords;
    coord_x = coords->x;
    base_y = coords->y;
    countdown = actor->timer - 1;
    actor->timer = countdown;
    ticks_left = (s16)countdown;
    coord_y = base_y + 0x60;
    target_x = (u32)coord_x << 16;
    coord_x = target_x;
    target_y = (u32)coord_y << 16;
    coord_y = target_y;

    if (ticks_left <= 0) {
        position->x.v = target_x;
        position->y.v = target_y;
        apply_object_setup_and_update(actor, position, completion_arg);
        return;
    }

    position->x.v +=
        (u32)((s32)(coord_x - position->x.v) / ticks_left);
    position->y.v +=
        (u32)((s32)(coord_y - position->y.v) / (s16)actor->timer);
}
