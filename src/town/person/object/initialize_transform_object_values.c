#include "common.h"
#include "town/scene/list_setup.h"
#include "m2c_compat.h"
#include "town/person/object.h"

extern M2C_UNK D_800C26C0[3];
extern void *person_transform_defaults[3];


/* Initialize the object values to 0x40, apply its indexed setup, and assign its table. */
void initialize_transform_object_values(TownObjectRecord *object, ObjectPosition *setup_context, SpriteFrameState *unused) {
    object->unk_8C.as_s16 = 0x40;
    object->unk_8E.as_s16 = 0x40;
    configure_the_set_mode_n_1(object, setup_context, *(object->unk_94.as_u8 + person_transform_defaults));
    object->unk_50.as_pm = D_800C26C0;
}
