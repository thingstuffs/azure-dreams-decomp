#include "town/person.h"
#include "town/person/object.h"


/* Select descriptor list +0x24, then forward all three callback inputs. */
void init_person_target_move(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *output) {
    initialize_object_entries(object, output, object->descriptor->entries[9]);
    start_person_target_move(object, position, output);
}
