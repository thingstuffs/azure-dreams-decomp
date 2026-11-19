#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/window.h"
#include "town/event.h"
#include "town/person.h"
#include "town/event/object.h"

/* Randomize color during an update, then reset it when the timer expires or state changes. */
void randomize_person_color(TownObjectRecord *object, TownObjectRecord *context, ObjectPosition *position, SpriteFrameState *sprite) {
    s32 previous_state;
    s16 ticks_left;

    sprite->color.c.r = scale_random_by_limit(0x100);
    sprite->color.c.g = scale_random_by_limit(0x100);
    sprite->color.c.b = scale_random_by_limit(0x100);
    previous_state = object->unk_50.as_s32;
    update_actor_surface_motion(object, context, position, sprite);
    ticks_left = object->timer - 1;
    object->timer = ticks_left;
    if ((ticks_left < 0) || (object->unk_50.as_s32 != previous_state)) {
        select_object_value_by_height_band(object, context, position, sprite);
        sprite->color.c.r = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.b = 0x80;
    }
}
