#include "common.h"
#include "frontend/card/service.h"
#include "main/data.h"

extern void configure_target_for_active_state_and_entry(void *buffer, s32 index);
extern s32 read_file(void *buffer, void *data_ptr, s32 value0, s32 value1);
extern s32 write_byte(void *buffer, void *record_ptr, s32 value0, s32 value1, s32 record_value);
extern s32 func_80401FEC(void *data_ptr);
extern void func_8007BF18(void *data_ptr);
extern u8 card_slot_header_cache[];

/* Reads a selected card file and, after a successful data check, writes its cached slot header. */
s32 read_and_update_indexed_record(s32 index, void *data_ptr) {
    u8 buffer[32];
    s32 result;

    configure_target_for_active_state_and_entry(buffer, index);
    result = read_file(buffer, data_ptr, 0xC0, 0);
    if (result != 0) {
        result = func_80401FEC(data_ptr);
        if (result != 0) {
            result = write_byte(buffer, card_slot_header_cache + (index << 7), 1, 4,
                                   *(s32 *)(card_slot_header_cache + (index << 7)));
        } else {
            func_8007BF18(D_80400138);
        }
    }
    return result;
}
