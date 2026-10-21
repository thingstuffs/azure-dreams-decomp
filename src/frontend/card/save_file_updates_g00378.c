/* Save file updates; G00378; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_8000EB98, CL:main/func_8000EC4C, CL:main/func_8000EDF4, CL:main/func_8000EEB8, CL:main/func_8000EEE0. */
#include "frontend/card/save_file_updates_g00378.h"
#include "frontend/card.h"

/* Checks the stored checksum against the XOR of 6014 data words. */
s32 card_boot_verify_save_xor_checksum(void *save_data) {
    s32 *data_word;
    s32 checksum;
    s32 word_index;

    checksum = 0;
    data_word = (s32 *) ((u8 *) save_data + 0x208);
    word_index = checksum;
    for (;;) {
        checksum ^= *data_word++;
        word_index += 1;
        if (word_index < 6014) continue;
        break;
    }
    return (*(s32 *) ((u8 *) save_data + 0x204) ^ checksum) == 0;
}

/* Updates slot data using a temporary filename before restoring the slot filename. */
s32 card_boot_write_save_via_temporary_path(s32 slot, void *data) {
    s32 slot_name[8];
    s32 temporary_name[8];
    s32 *slot_table;
    s32 *slot_entry;
    s32 result;

    card_boot_build_slot_path(slot_name, slot);
    card_boot_build_slot_path(temporary_name, 5);
    slot_table = (s32 *)&(*(s32 (*)[][32])(&card_save_slot_metadata));
    slot_entry = (s32 *)((u8 *)slot_table + (slot << 7));
    if (*slot_entry != 0) {
        rename(slot_name, temporary_name);
    }
    *(s32 *)((u8 *)data + 0x204) = 0;
    card_boot_store_save_xor_checksum(data);
    result = card_boot_write_file_units_128(temporary_name, data, 0xC0, 0, *slot_entry);
    if (result != 0) {
        card_boot_cache_save_header(slot, data);
        card_boot_refresh_directory_summary();
    }
    rename(temporary_name, slot_name);
    return result;
}

/* Marks quest data as loaded, optionally refreshing its indexed entry while preserving its state. */
void card_boot_load_save_and_clear_marker(s32 entry_index, void *data, s32 update_entry) {
    s32 context[8];
    s32 *entry_table;
    s32 *entry;
    s32 saved_state;

    card_boot_build_slot_path(context, entry_index);
    if (card_boot_read_file_units_128(context, data, 0xC0, 0) == 0) {
        return;
    }
    if (card_boot_verify_save_xor_checksum(data) == 0) {
        return;
    }
    if (update_entry != 0) {
        saved_state = *(s16 *)((u8 *)data + 0x208);
        *(s16 *)((u8 *)data + 0x208) = 0;
        *(s32 *)((u8 *)data + 0x204) = 0;
        card_boot_store_save_xor_checksum(data);
        entry_table = (s32 *)&(*(s32 (*)[][32])(&card_save_slot_metadata));
        entry = (s32 *)((u8 *)entry_table + (entry_index << 7));
        *(s16 *)((u8 *)entry + 8) = 0;
        *(s32 *)((u8 *)entry + 4) = *(s32 *)((u8 *)data + 0x204);
        card_boot_write_file_units_128(context, entry, 1, 4, entry[0]);
        card_boot_write_file_units_128(context, data, 1, 0, entry[0]);
        *(s16 *)((u8 *)data + 0x208) = saved_state;
        return;
    }
    *(s16 *)((u8 *)data + 0x208) = 0;
}
