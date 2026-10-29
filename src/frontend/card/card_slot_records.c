/* Copy card slot record fields and refresh the five displayed objects. */

#include "common.h"
#include "m2c_compat.h"
#include "engine/resource.h"
#include "frontend/card.h"
#include "frontend/libcard.h"

/* Processes the object header and invokes two follow-up routines. */

void inventory_copy_and_sign_extend_record_fields(s32 object_data) {
    release_card_record_handles(object_data - 0x20);
    card_boot_close_events_and_resume_timer();
    request_scene_dispatch_state(3);
}


typedef struct S_80026270_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80026270_0;

/* Runs card_boot_refresh_slot_window on each of five stored object addresses. */
void card_boot_refresh_five_slot_objects(void *object_list) {
    s32 object_addr;
    s32 object_index;
    void *entry_cursor;

    object_index = 0;
    entry_cursor = object_list;
    do {
        object_addr = ((S_80026270_0 *)entry_cursor)->unk_0C;
        entry_cursor += 4;
        object_index += 1;
        card_boot_refresh_slot_window(object_addr);
    } while (object_index < 5);
}
