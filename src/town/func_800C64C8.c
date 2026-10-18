#include "common.h"

void install_object_handler_and_clear_slot_flag(void *object);

typedef struct S_800C3C28_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800C3C28_0;   /* arg2 in dispatch_status_triggered_handler */

/* Calls the object handler when either monitored status flag is set. */
void dispatch_status_triggered_handler(s32 object, s32 unused, S_800C3C28_0 *status) {
    if (status->unk_14 & 0x6000) {
        install_object_handler_and_clear_slot_flag(object);
    }
}
