#include "common.h"
#include "frontend/card.h"
#include "frontend/card/service.h"
#include "main/data.h"

extern void configure_target_for_active_state_and_entry(void *target, s32 entry_index);
extern s32 read_file(void *file_path, void *buffer, s32 block_count, s32 block_offset);
extern s32 card_selected_channel[];
extern u8 card_slot_header_cache[];

/* Looks up a slot's data and processes its record when the lookup succeeds. */
s32 card_dev_load_slot_metadata(s32 slot_index) {
    u8 slot_data[32];
    s32 *lookup_key;
    s32 slot_offset;
    s32 lookup_result;
    s32 result;

    result = 1;
    configure_target_for_active_state_and_entry(slot_data, slot_index);
    if (card_selected_channel[0] != 0) {
        lookup_key = dev_card_directory_counts + 1;
    } else {
        lookup_key = dev_card_directory_counts;
    }
    slot_offset = slot_index << 7;
    lookup_result = card_devkit_has_directory_name_prefix(*lookup_key, &slot_data[5]);
    *(s32 *)(card_slot_header_cache + slot_offset) = lookup_result;
    if (lookup_result != 0) {
        result = read_file(slot_data, card_slot_header_cache + slot_offset, 1, 4);
        *(s32 *)(card_slot_header_cache + slot_offset) = 1;
    }
    return result;
}
