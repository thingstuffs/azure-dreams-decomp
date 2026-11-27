#include "common.h"
#include "shared/town_object.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"




/* extern */
extern M2C_UNK D_800D62C4;

#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
/* Set the object data pointer and clear its indexed flag before calling apply_object_setup_and_update. */
void replace_object_entry_and_apply_setup(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    object->descriptor->entries[1] = &D_800D62C4;
    object_index_slots[object->slot].motion_id = 0;
    apply_object_setup_and_update(object, position, sprite);
}
