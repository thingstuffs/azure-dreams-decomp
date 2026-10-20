#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void clear_slot_n_3_copies_slot_n_0(EntityRec *);                            /* extern */
extern s8 D_800CFCEB;


/* Set D_800CFCEB, initialize the record, and call clear_slot_n_3_copies_slot_n_0. */
void set_global_800_cfceb_initialize_call_callee_800954_c_4(EntityRec *record, s32 initial_value) {
    D_800CFCEB = 1;
    record->x.v = initial_value;
    record->unk_0C = 0;
    clear_slot_n_3_copies_slot_n_0(record);
}
