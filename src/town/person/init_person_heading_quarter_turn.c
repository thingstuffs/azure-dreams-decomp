#include "town/person.h"

/* Select the fixed entry list and install the callback's initial state. */
void init_person_heading_quarter_turn(TownObjectRecord *object, s32 unused, SpriteFrameState *output) {
    initialize_object_entries(object, output, moving_reaction_entries);
    object->handler = advance_weedy_reaction;
    object->heading = 0x400;
}
