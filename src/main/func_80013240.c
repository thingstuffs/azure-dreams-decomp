#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026920();                         /* extern */
void card_boot_close_events_and_resume_timer();                            /* extern */
M2C_UNK func_80040AA0();                     /* extern */

/* Processes the object header and invokes two follow-up routines. */
void inventory_copy_and_sign_extend_record_fields(s32 object_data) {
    func_80026920(object_data - 0x20);
    card_boot_close_events_and_resume_timer();
    func_80040AA0(3);
}
