#include "common.h"

extern u8 scene_rows[];
extern s32 selected_scene_row_index;

/* Returns the word at offset 12 in the selected 24-byte table entry. */
s32 get_selected_entry_word_12(void) {
    s32 entry_offset;
    u8 *table_base;

    table_base = scene_rows;
    entry_offset = selected_scene_row_index * 0x18;
    return *(s32 *)(table_base + entry_offset + 12);
}
