#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026920();                         /* extern */
void cardBootCloseEventsAndResumeTimer();                            /* extern */
M2C_UNK func_80040AA0();                     /* extern */

/* Processes the object header and invokes two follow-up routines. */
void inventoryCopyAndSignExtendRecordFields(s32 object_data) {
    func_80026920(object_data - 0x20);
    cardBootCloseEventsAndResumeTimer();
    func_80040AA0(3);
}
