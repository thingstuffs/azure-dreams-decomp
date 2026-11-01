#include "common.h"
#include "shared/town_object.h"
#include "m2c_compat.h"
#include "town/person/object.h"

extern M2C_UNK D_800D68E8;


/* Checks whether the object's referenced value is the address of D_800D68E8. */
s32 is_default_object_data(TownObjectRecord *object) {
    return *object->unk_7C.as_pps32 == &D_800D68E8;
}
