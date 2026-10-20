#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(EntityRec *);                            /* extern */
extern s8 D_800CFCE8;


/* Set the record value, clear its secondary value, and refresh it with the global flag set. */
void set_the_clear_secondary_refresh_global_flag_set(EntityRec *record, s32 value) {
    D_800CFCE8 = 1;
    record->z.v = value;
    record->flags14 = 0;
    clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(record);
}
