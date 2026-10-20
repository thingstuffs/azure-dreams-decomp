#include "common.h"

extern s32 find_target_byte_index_in_list(void);
extern s32 D_800D0728[];

/* Clears the first byte of each 0x54-byte entry using the selected entry count. */
void clear_selected_scene_entry_flags(void) {
    s32 table_index = find_target_byte_index_in_list();
    s32 entry_count = D_800D0728[table_index];
    s32 entry_index;

    for (entry_index = 0; entry_index < entry_count; entry_index++) {
        s32 offset = entry_index * 0x54;
        *(u8 *)(offset + 0x80010AC4) = 0;
    }
}
