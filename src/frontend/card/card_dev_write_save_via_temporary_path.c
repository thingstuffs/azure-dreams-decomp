#include "common.h"
#include "frontend/card.h"
#include "frontend/card/service.h"
#include "frontend/card/server_imports.h"

extern void configure_target_for_active_state_and_entry(void *buffer, s32 index);
extern void compute_store(struct CardDevSaveWork *request_id);
extern s32 write_byte(void *buffer, void *request_id, s32 value1, s32 value2, s32 entry_value);

/* Processes an entry using its table value and a temporary slot-5 buffer. */
s32 card_dev_write_save_via_temporary_path(s32 entry_id, struct CardDevSaveWork *request_id) {
    u8 entry_buffer[32];
    u8 work_buffer[32];
    s32 result;

    configure_target_for_active_state_and_entry(entry_buffer, entry_id);
    configure_target_for_active_state_and_entry(work_buffer, 5);
    if (card_slot_header_cache[entry_id].fields.marker != 0) {
        rename_8007CAD8(entry_buffer, work_buffer);
    }
    compute_store(request_id);
    result = write_byte(work_buffer, request_id, 0xC0, 0, card_slot_header_cache[entry_id].fields.marker);
    if (result != 0) {
        card_dev_cache_save_header(entry_id, request_id);
    }
    rename_8007CAD8(work_buffer, entry_buffer);
    return result;
}
