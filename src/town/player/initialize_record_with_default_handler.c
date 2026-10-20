#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s8 D_80082668;
extern M2C_UNK D_80098078;


/* Initialize the record from global data, clear the global flag, and set its table and counter. */
void initialize_record_with_default_handler(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D00A0, record, ptr2);
    D_80082668 = 0;
    record->unk_04.as_pm = &D_80098078;
    record->unk_0A.as_s16 = 8;
}
