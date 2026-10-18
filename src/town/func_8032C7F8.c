#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 check_progress_against_callback();                                /* extern */
s32 process_checked_entry();             /* extern */
void set_script_flag_bit();                         /* extern */
void clear_script_flag_bit();                     /* extern */


/* Process flag 0xD52, conditionally select the object value, and forward the request. */
void process_flag_and_forward_request(Rec_func_800165F4_arg0 *object, s32 request_data) {
    clear_script_flag_bit(0xD52);
    if (check_progress_against_callback() != 0) {
        set_script_flag_bit(object->unk_18);
    }
    process_checked_entry(object, request_data);
}
