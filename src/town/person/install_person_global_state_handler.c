#include "common.h"
#include "town/person.h"
#include "town/person/state.h"

/* Sets the object's pointer at offset 0x50 to update_person_global_state. */
void install_person_global_state_handler(TownObjectRecord *object) {
    object->unk_50.as_pm = &update_person_global_state;
}
