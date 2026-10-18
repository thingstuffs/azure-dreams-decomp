#include "common.h"

extern void configure_target_for_active_state_and_entry(void *buffer, s32 index);
extern void func_8007CAD8(void *buffer_a, void *buffer_b);
extern void compute_store(s32 request_id);
extern s32 write_byte(void *buffer, s32 request_id, s32 value1, s32 value2, s32 entry_value);
extern void card_dev_cache_save_header(s32 entry_id, s32 request_id);
extern u8 D_8009DDD8[];

/* Processes an entry using its table value and a temporary slot-5 buffer. */
s32 func_8001B084(s32 entry_id, s32 request_id) {
    u8 entry_buffer[32];
    u8 work_buffer[32];
    s32 entry_offset;
    s32 result;

    configure_target_for_active_state_and_entry(entry_buffer, entry_id);
    configure_target_for_active_state_and_entry(work_buffer, 5);
    entry_offset = entry_id << 7;
    if (*(s32 *)(D_8009DDD8 + entry_offset) != 0) {
        func_8007CAD8(entry_buffer, work_buffer);
    }
    compute_store(request_id);
    result = write_byte(work_buffer, request_id, 0xC0, 0, *(s32 *)(D_8009DDD8 + entry_offset));
    if (result != 0) {
        card_dev_cache_save_header(entry_id, request_id);
    }
    func_8007CAD8(work_buffer, entry_buffer);
    return result;
}
