#include "modules/main_server_ship.h"
#include "common.h"

extern void rename(void *old_name, void *new_name);



/* Updates slot data using a temporary filename before restoring the slot filename. */
s32 card_boot_write_save_via_temporary_path(s32 slot, void *data) {
    s32 slot_name[8];
    s32 temporary_name[8];
    s32 *slot_table;
    s32 *slot_entry;
    s32 result;

    card_boot_build_slot_path(slot_name, slot);
    card_boot_build_slot_path(temporary_name, 5);
    slot_table = (s32 *)&(*(s32 (*)[][32])(&D_80083E98));
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
