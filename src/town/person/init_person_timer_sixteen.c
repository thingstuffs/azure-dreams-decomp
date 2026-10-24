#include "town/person.h"

/* Select the fixed entry list and install the callback's initial state. */
void init_person_timer_sixteen(PersonObject *object, s32 unused, s8 *output) {
    initialize_object_entries(object, output, D_800D72AC);
    object->handler = tick_countdown_toward_target;
    object->timer = 0x10;
}
