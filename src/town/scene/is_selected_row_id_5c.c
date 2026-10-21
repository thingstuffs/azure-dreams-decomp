#include "common.h"
#include "m2c_compat.h"

extern u8 scene_rows[];
extern s32 selected_scene_row_index;

typedef struct S_805D3A34_0 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_805D3A34_0;   /* base + offset in is_selected_row_id_5c */

/* Check whether the selected record has identifier 0x5C. */
s32 is_selected_row_id_5c(void) {
    s32 record_offset;
    u8 *records;

    records = scene_rows;
    record_offset = selected_scene_row_index * 0x18;
    return ((S_805D3A34_0 *)(records + record_offset))->unk_14 == 0x5C;
}
