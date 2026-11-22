#include "common.h"
#include "town/person.h"
#include "town/person/object.h"
#include "town/person/state.h"

/* Call func_800C4804 and set the object pointer to run_object_handlers_supplied_state. */
void initialize_object_with_supplied_state_handlers(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    init_person_target_move(object, position, sprite);
    object->handler = &run_object_handlers_supplied_state;
}
