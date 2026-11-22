#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person.h"
#include "town/person/object.h"

   /* ((TownObjectRecord *)arg0)->unk_80 in init_mia_person */

extern M2C_UNK D_800D6244;
extern s32 *D_800D62D8[];
extern PersonDescriptor D_800D62E0;
extern s32 D_800D6308[];
extern TownIndexedHandler D_800D630C[];

/* Initialize the object with configuration 0xA and set its associated data pointer. */
void init_mia_person(TownObjectRecord *object, ObjectPosition *position_unused, struct SpriteFrameState *sprite_unused) {
    register_object_slot_with_tables(object, 0xA, D_800D6308, D_800D630C, D_800D62D8, &D_800D62E0);
    object->descriptor->entries[1] = &D_800D6244;
}
