#include "town/scene/collision.h"
#include "common.h"
#include "engine/audio.h"
#include "town/event/object.h"
#include "town/event.h"
#include "slus.h"

/* Clear object state, assign the context handler, and trigger effects if the check succeeds. */
void initialize_object_and_maybe_play_sound(TownObjectRecord *object, struct ColliderView *collider, ObjectPosition *motion, struct SpriteFrameState *unused)
{
    collider->enabled = 0;
    motion->velocity_x = 0;
    motion->velocity_y = 0;
    motion->velocity_z = 0;
    object->state_callback.as_pm = resolve_owner_position_and_dispatch;
    if (check_object_type_and_data_tag(&object->unk_4C) != 0) {
        select_sound_stream(0x26, 0);
        SD_Call(0x200);
    }
}
