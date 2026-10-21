#include "common.h"
#include "m2c_compat.h"

extern u8 scene_rows[];
extern s32 selected_scene_row_index;

typedef struct S_805D37B4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_805D37B4_0;   /* base + offset in get_selected_row_field_4 */

/* Returns the field at offset 0x04 of the selected 0x18-byte table entry. */
s32 get_selected_row_field_4(void) {
    s32 entry_offset;
    u8 *table_base;

    table_base = scene_rows;
    entry_offset = selected_scene_row_index * 0x18;
    return ((S_805D37B4_0 *)(table_base + entry_offset))->unk_04;
}
