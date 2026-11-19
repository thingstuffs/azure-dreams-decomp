#include "town/person/motion_callbacks_api.h"
#include "town/person/offset_target_data.h"
#include "common.h"

#include "town/person/object_setup.h"
#include "town/person/object.h"
#include "town/person/motion.h"

/* Move toward the offset target position and finish when the timer expires. */
void move_toward_offset_target(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *finish_arg)
{
    TownOffsetTargetCoords *target;
    s32 raw_x;
    s32 raw_y;
    s32 coord_x;
    s32 coord_y;
    s32 frames_left;
    u32 target_x;
    u32 target_y;
    u16 timer;

    target = person_offset_target_owner->coords;
    raw_x = target->x;
    raw_y = target->y;
    timer = object->timer - 1;
    object->timer = timer;
    frames_left = (s16)timer;
    coord_x = raw_x + 0x60;
    coord_y = raw_y + 0x20;
    target_x = (u32)coord_x << 16;
    coord_x = target_x;
    target_y = (u32)coord_y << 16;
    coord_y = target_y;

    if (frames_left <= 0) {
        position->x.v = target_x;
        position->y.v = target_y;
        apply_object_setup_and_update(object, position, finish_arg);
        return;
    }

    position->x.v += (u32)((s32)(coord_x - position->x.v) / frames_left);
    position->y.v +=
        (u32)((s32)(coord_y - position->y.v) / (s16)object->timer);
}
