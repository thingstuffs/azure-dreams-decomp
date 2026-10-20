#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_800AA844;


/* Initialize the record, set its first pointer to D_800AA844, and store code 0x54. */
void initialize_record_with_pointer_and_code(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D0138, record, ptr2);
    record->unk_00.as_pm = &D_800AA844;
    record->unk_0A.as_s16 = 0x15;
}
