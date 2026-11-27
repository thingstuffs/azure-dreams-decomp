#include "town/person.h"

/* Select the fixed entry list and install the callback's initial state. */
void start_countdown_toward_target(TownObjectRecord *object, s32 unused, SpriteFrameState *output) {
    initialize_object_entries(object, output, moving_reaction_entries);
    object->handler = tick_countdown_toward_target;
    object->timer = 0x10;
}
