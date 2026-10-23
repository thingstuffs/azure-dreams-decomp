#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void apply_object_setup_and_update(void *, s32, s32);    /* extern */
void set_object_referenced_data_pointers(Rec_func_80094268_arg0 *);                            /* extern */


/* Decrement the record's countdown and run its follow-up calls when it expires. */
void run_record_countdown_follow_up(Rec_func_80094268_arg0 *record, s32 update_context, s32 setup_context) {
    u16 countdown;

    countdown = record->unk_6C.as_u16 - 1;
    record->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        set_object_referenced_data_pointers(record);
        apply_object_setup_and_update(record, update_context, setup_context);
    }
}
