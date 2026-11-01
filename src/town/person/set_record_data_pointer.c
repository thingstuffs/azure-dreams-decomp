#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person.h"


typedef struct S_800CB04C_1 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800CB04C_1;   /* ((TownObjectRecord *)arg0)->unk_80 in set_record_data_pointer */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D6924;


/* Sets the record's associated data pointer to D_800D6924. */
void set_record_data_pointer(TownObjectRecord *record) {
    record->descriptor->entries[1] = &D_800D6924;
}
