#include "common.h"
#include "m2c_compat.h"

void set_script_flag_bit();                     /* extern */
s32 get_script_flag_mask();                         /* extern */

/* Process ID 0xD51 and return its preceding query result. */
s32 query_and_process_event_d_51(void) {
    s32 query_result;

    query_result = get_script_flag_mask(0xD51);
    set_script_flag_bit(0xD51);
    return query_result;
}
