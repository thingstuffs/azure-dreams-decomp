#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"





/* Looks up a slot's record and processes it when present. */
s32 card_boot_load_slot_metadata(s32 slot) {
    s32 record_data[8];
    s32 *source_id;
    u8 *state_base;
    s32 *slot_state;
    s32 lookup_result;
    s32 result;

    result = 1;
    card_boot_build_slot_path(record_data, slot);
    source_id = &card_directory_counts[0];
    if ((*(s32 *)(&card_selected_channel_alias)) != 0) {
        source_id = &card_directory_counts[1];
    }
    lookup_result = card_boot_has_directory_name_prefix(*source_id, (u8 *)record_data + 5);
    state_base = (u8 *)(*(s32 (*)[])(&card_save_slot_metadata));
    slot_state = (s32 *)(state_base + (slot << 7));
    *slot_state = lookup_result;
    if (lookup_result != 0) {
        result = card_boot_read_file_units_128(record_data, slot_state, 1, 4);
        *slot_state = 1;
    }
    return result;
}
