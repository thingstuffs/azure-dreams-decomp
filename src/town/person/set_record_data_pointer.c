#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person.h"

   /* ((TownObjectRecord *)arg0)->unk_80 in set_record_data_pointer */

extern M2C_UNK D_800D6924;

/* Sets the record's associated data pointer to D_800D6924. */
void set_record_data_pointer(TownObjectRecord *record) {
    record->descriptor->entries[1] = &D_800D6924;
}
