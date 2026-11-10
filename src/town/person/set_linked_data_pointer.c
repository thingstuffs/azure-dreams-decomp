#include "common.h"
#include "shared/town_object.h"
#include "m2c_compat.h"
#include "town/person.h"

   /* ((S_800CB060_0 *)arg0)->unk_80 in set_linked_data_pointer */

extern M2C_UNK D_800D6960;

/* Set the object's linked data pointer to D_800D6960. */
void set_linked_data_pointer(TownObjectRecord *object) {
    object->descriptor->entries[1] = &D_800D6960;
}
