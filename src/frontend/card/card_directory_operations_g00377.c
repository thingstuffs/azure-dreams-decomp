/* Card directory operations; G00377; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_8000EA04, PD:main/image_25c800:80027F18, PD:main/image_25c800:80028570. */
#include "frontend/card/card_directory_operations_g00377.h"
#include "frontend/card.h"

/* Collect directory entries matching the selected search path and return their count. */
s32 count_entries_matching_search_path(void)
{
    u8 search_path[32];
    u8 *dir_entry;
    s32 *path_ptr;
    s32 file_count;

    file_count = 0;
    dir_entry = (*(u8 (*)[])(&boot_card_directory));
    path_ptr = boot_card_paths;
    if (card_selected_channel_alias[0] != 0) {
        path_ptr++;
    }

    strcpy(search_path, *path_ptr);
    strcat(search_path, D_80020084);

    if (firstfile2(search_path, (*(u8 (*)[])(&boot_card_directory))) != 0) {
        do {
            file_count++;
            dir_entry += 40;
        } while (nextfile(dir_entry) == dir_entry);
    }

    return file_count;
}

/* Returns the blocks remaining after summing the entry sizes in 8192-byte units. */
s32 card_boot_calc_remaining_8k_blocks(s32 entry_count) {
    func_8000E9B8_EntryT *entry;
    s32 total_size;
    s32 entry_index;
    s32 size_value;

    entry_index = 0;
    total_size = entry_index;
    size_value = (s32)&(*(func_8000E9B8_EntryT (*)[])(&boot_card_directory))[0];
    if (entry_count > 0) {
        entry = (func_8000E9B8_EntryT *)size_value;
        do {
            size_value = entry->field18;
            entry_index += 1;
            total_size += size_value;
            entry += 1;
        } while (entry_index < entry_count);
    }
    size_value = total_size;
    total_size = (size_value / 8192);
    return 0xF - total_size;
}

/* Return whether any record matches text through its terminator or the first 21 bytes. */
s32 card_boot_has_directory_name_prefix(s32 count, u8 *text)
{
    s32 record_index;
    s32 found;
    u8 *records;

    record_index = 0;
    found = record_index;
    records = (*(u8 (*)[])(&boot_card_directory));
    if (count > 0) {
        u8 *record;

        record = records;
        do {
            s32 mismatch;
            s32 char_index;

            mismatch = 0;
            char_index = mismatch;
            do {
                u8 character;

                character = text[char_index];
                if (character == 0) {
                    break;
                }
                if (character != record[char_index]) {
                    mismatch++;
                    break;
                }
                char_index++;
            } while (char_index < 0x15);
            if (mismatch == 0) {
                found = 1;
                break;
            }
            record_index++;
            record += 0x28;
        } while (record_index < count);
    }
    return found;
}

/* Format the selected memory card and return its completion status. */
s32 card_boot_format_card_and_wait(s32 card_slot) {
    s32 *card_device;
    s32 status;
    s32 result;

    _card_wait(0);
    _card_wait(1);
    card_boot_drain_hardware_events();
    card_device = &boot_card_paths[0];
    if (card_slot != 0) {
        card_device = &boot_card_paths[1];
    }
    format(*card_device);
    do {
        status = card_boot_take_hardware_status();
        if (status == 0) {
            VSync(0);
        }
    } while (status == 0);
    if (status != 1) {
        if (status == 3) {
            status = 4;
        } else {
            status = 5;
        }
    }
    result = status;
    return result;
}

/* Builds a string from the selected prefix, a separator, and an indexed suffix. */
void card_boot_build_slot_path(s32 dest, s32 suffix_index) {
    s32 *prefix_ptr;

    prefix_ptr = &(*(u8 *)(&boot_card_paths));
    if ((*(s32 *)(&card_selected_channel_alias)) != 0) {
        prefix_ptr = &(*(u8 *)(&boot_card_paths)) + 4;
    }
    strcpy(dest, *prefix_ptr);
    strcat(dest, &(*(s32 *)(&D_80027F20)));
    strcat(dest, (&(*(s32 *)(&boot_card_slot_names)))[suffix_index]);
}
