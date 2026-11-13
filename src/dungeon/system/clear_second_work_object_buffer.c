#include "common.h"
#include "m2c_compat.h"

void *get_second_work_value(void *work);                             /* extern */
void clear_object_buffer_and_state(void *objectAddress);                         /* extern */

typedef struct S_800255D0_0 {
    u8 pad_00[0x14];
    void *unk_14;
} S_800255D0_0;   /* arg0 in clear_second_work_object_buffer */

/* Clears the object buffer of the record's work (the work's second value, +0x48) and returns success. */
s32 clear_second_work_object_buffer(S_800255D0_0 *record) {
    clear_object_buffer_and_state(get_second_work_value(record->unk_14));
    return 1;
}
