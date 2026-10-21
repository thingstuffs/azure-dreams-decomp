#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern u8 scene_rows[];
extern s32 selected_scene_row_index;
/* Returns the 32-bit field at offset 0x10 in the selected 24-byte record. */
s32 get_selected_entry_field_10(void)
{
    s32 *record_field;
    s32 record_offset;
    u8 *records;
    records = scene_rows;
    record_offset = ((unsigned int) selected_scene_row_index) * 0x18;
    record_field = (s8 *) (records + record_offset);
    record_field = record_field + 4;
    return *record_field;
}
