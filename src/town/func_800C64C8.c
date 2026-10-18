#include "common.h"
#include "m2c_compat.h"

void install_object_handler_and_clear_slot_flag(M2C_UNK);                            /* extern */

typedef struct S_800C3C28_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800C3C28_0;   /* arg2 in dispatch_status_triggered_handler */

/* Calls the object handler when either monitored status flag is set. */
void dispatch_status_triggered_handler(M2C_UNK object, M2C_UNK unused, S_800C3C28_0 *status) {
    if (status->unk_14 & 0x6000) {
        install_object_handler_and_clear_slot_flag(object);
    }
}
