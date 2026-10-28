#include "town/person.h"
#include "town/person/object_slots.h"

/* Register person slot 8 with its four data tables, then point its referenced data at fixed tables. */
void init_person_slot_eight(void *object, void *context, struct SpriteFrameState *output) {
    initialize_object_and_register_slot(object, 8, D_800D69B8, D_800D69BC, D_800D6988, D_800D6990);
    initialize_object_referenced_data_pointers(object, context, output);
}
