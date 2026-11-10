#include "frontend/card/save_image.h"
/* Save file updates; G00378; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - main/func_8000EB98, main/func_8000EC4C, main/func_8000EDF4, main/func_8000EEB8, main/func_8000EEE0. */
#include "frontend/card/save_file_updates_g00378.h"
#include "frontend/card.h"

/* Checks the stored checksum against the XOR of 6014 data words. */
s32 card_boot_verify_save_xor_checksum(void *save_data) {
    CardSaveImage *save = save_data;
    s32 *data_word;
    s32 checksum;
    s32 word_index;

    checksum = 0;
    data_word = save->data.words;
    word_index = checksum;
    for (;;) {
        checksum ^= *data_word++;
        word_index += 1;
        if (word_index < 6014) continue;
        break;
    }
    return (save->checksum ^ checksum) == 0;
}

/* Updates slot data using a temporary filename before restoring the slot filename. */
s32 card_boot_write_save_via_temporary_path(s32 slot, void *data) {
    CardSaveImage *save = data;
    s32 slot_name[8];
    s32 temporary_name[8];
    CardSaveSlot *slot_table;
    CardSaveSlot *slot_entry;
    s32 result;

    card_boot_build_slot_path(slot_name, slot);
    card_boot_build_slot_path(temporary_name, 5);
    slot_table = card_save_slot_metadata;
    slot_entry = &slot_table[slot];
    if (slot_entry->words[0] != 0) {
        rename(slot_name, temporary_name);
    }
    save->checksum = 0;
    card_boot_store_save_xor_checksum(data);
    result = card_boot_write_file_units_128(temporary_name, data, 0xC0, 0, slot_entry->words[0]);
    if (result != 0) {
        card_boot_cache_save_header(slot, data);
        card_boot_refresh_directory_summary();
    }
    rename(temporary_name, slot_name);
    return result;
}

/* Marks quest data as loaded, optionally refreshing its indexed entry while preserving its state. Returns zero when
 * the save cannot be read or fails its checksum, else the final write's result (refreshing) or the checksum result. */
s32 card_boot_load_save_and_clear_marker(s32 entry_index, void *data, s32 update_entry) {
    CardSaveImage *save = data;
    s32 context[8];
    CardSaveSlot *entry_table;
    CardSaveSlot *entry;
    s32 saved_state;
    s32 result;

    card_boot_build_slot_path(context, entry_index);
    result = card_boot_read_file_units_128(context, data, 0xC0, 0);
    if (result != 0) {
        result = card_boot_verify_save_xor_checksum(data);
        if (result != 0) {
            if (update_entry != 0) {
                saved_state = save->data.fields.load_marker;
                save->data.fields.load_marker = 0;
                save->checksum = 0;
                card_boot_store_save_xor_checksum(data);
                entry_table = card_save_slot_metadata;
                entry = &entry_table[entry_index];
                entry->halfwords[4] = 0;
                entry->words[1] = save->checksum;
                card_boot_write_file_units_128(context, entry, 1, 4, entry->words[0]);
                result = card_boot_write_file_units_128(context, data, 1, 0, entry->words[0]);
                save->data.fields.load_marker = saved_state;
            } else {
                save->data.fields.load_marker = 0;
            }
        }
    }
    return result;
}
