#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void clear_slot_n_3_copies_slot_n_0(EntityRec *);                            /* extern */
extern s8 D_800CFCEA;


/* Set D_800CFCEA, initialize the record, and call clear_slot_n_3_copies_slot_n_0. */
void set_global_800_cfcea_initialize_call_callee_800954_c_4(EntityRec *record, s32 initial_value) {
    D_800CFCEA = 1;
    record->x.v = initial_value;
    record->unk_0C = 0;
    clear_slot_n_3_copies_slot_n_0(record);
}
