#include "common.h"
#include "shared/town_object.h"
#include "town/person.h"
#include "town/person/object.h"


/* Decrements an object's countdown and invokes both handlers when it expires. */
void advance_object_countdown_and_invoke_handlers(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    u16 remaining_count;

    remaining_count = object->timer.as_u16 - 1;
    object->timer.as_u16 = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        set_record_data_pointer(object);
        apply_object_setup_and_update(object, position, sprite);
    }
}
