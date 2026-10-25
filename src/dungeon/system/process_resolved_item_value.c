#include "common.h"
#include "m2c_compat.h"

s32 get_second_work_value();                             /* extern */
void clear_object_buffer_and_state(s32 objectAddress);                         /* extern */

typedef struct S_800255D0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800255D0_0;   /* arg0 in process_resolved_item_value */

/* Processes the value resolved from the record and returns success. */
s32 process_resolved_item_value(S_800255D0_0 *record) {
    clear_object_buffer_and_state(get_second_work_value(record->unk_14));
    return 1;
}
