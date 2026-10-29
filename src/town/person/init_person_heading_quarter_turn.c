#include "town/person.h"

/* Select the fixed entry list and install the callback's initial state. */
void init_person_heading_quarter_turn(PersonObject *object, s32 unused, SpriteFrameState *output) {
    initialize_object_entries(object, output, D_800D72AC);
    object->handler = advance_actor_reaction_downward;
    object->heading = 0x400;
}
