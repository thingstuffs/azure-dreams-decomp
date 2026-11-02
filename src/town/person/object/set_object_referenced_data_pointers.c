#include "common.h"
#include "town/person/actor_data_references_g00663.h"
#include "shared/town_object.h"
#include "m2c_compat.h"
#include "town/person/object.h"




extern M2C_UNK D_800D5820;
extern M2C_UNK D_800D5844;


/* Sets the object's referenced data pointers to the static data blocks. */
void set_object_referenced_data_pointers(TownObjectRecord *object, void *unused_context, struct SpriteFrameState *unused_sprite) {
    /* BYTES: retain the two callback operands forwarded by the slot initializer. */
    *object->unk_7C.as_pps32 = &D_800D5820;
    object->descriptor->entries[1] = &D_800D5844;
}
