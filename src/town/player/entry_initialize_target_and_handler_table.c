#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80097D54_arg0.h"
s32 service_script_controller(Rec_func_80097D54_arg0 *, s32, s32, s32);                                /* extern */
#include "records/Rec_func_80094268_arg0.h"
void init_flagged_entity_action(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);    /* extern */
void initialize_target_and_handler_table();    /* extern */
extern M2C_UNK D_800CFFF0;

/* Check the record, tick its countdown, and dispatch the appropriate handler. */
void advance_timed_script_controller(Rec_func_80097D54_arg0 *record, s32 call_arg_1, s32 call_arg_2, s32 check_arg) {
    u16 countdown;

    if (service_script_controller(record, call_arg_1, call_arg_2, check_arg) == 0) {
        countdown = record->unk_0A - 1;
        record->unk_0A = countdown;
        if ((countdown << 0x10) > 0) {
            return;
        }
        if (record->unk_1C == &D_800CFFF0) {
            init_flagged_entity_action(record, call_arg_1, call_arg_2);
            return;
        }
    }
    initialize_target_and_handler_table(record, call_arg_1, call_arg_2);
}
