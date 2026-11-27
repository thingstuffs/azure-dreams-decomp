#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person.h"
#include "town/person/object.h"

   /* ((TownObjectRecord *)arg0)->unk_80 in init_mia_person */

extern M2C_UNK D_800D6244;
extern s32 *mia_animation_lists[];
extern PersonDescriptor mia_descriptor;
extern s32 mia_state_handlers[];
extern TownIndexedHandler mia_script_action_handlers[];

/* Initialize the object with configuration 0xA and set its associated data pointer. */
void init_mia_person(TownObjectRecord *object, ObjectPosition *position_unused, struct SpriteFrameState *sprite_unused) {
    register_object_slot_with_tables(object, 0xA, mia_state_handlers, mia_script_action_handlers, mia_animation_lists, &mia_descriptor);
    object->descriptor->entries[1] = &D_800D6244;
}
