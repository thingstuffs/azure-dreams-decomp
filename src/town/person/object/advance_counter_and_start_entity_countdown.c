#include "common.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"
#include "town/person/object.h"

/* Count the object's timer down; when it expires, reload its entries and start a six-tick
 * advance_entity_countdown. */
void advance_counter_and_start_entity_countdown(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    s16 remaining_ticks;

    remaining_ticks = object->timer - 1;
    object->timer = remaining_ticks;
    if (remaining_ticks <= 0) {
        initialize_object_entries(object, sprite, entity_countdown_entries);
        object->handler = advance_entity_countdown;
        object->timer = 6;
    }
}
