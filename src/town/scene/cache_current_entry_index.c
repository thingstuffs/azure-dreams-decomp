#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


typedef struct S_805D3860_1 {
    s32 unk_00;
    u8 pad_04[0x2];
    u8 unk_06;
} S_805D3860_1;


extern s32 scene_charge;
extern s32 selected_scene_row_index;

/* Cache the selected record's index and value, then return its value. */
s32 cache_current_entry_index(void) {
    S_805D3860_1 *selected_record;

    selected_record = (S_805D3860_1 *)(((s32)town_scene_root->event_data) + (town_scene_root->entry_index * 8));
    selected_scene_row_index = (s32) selected_record->unk_06;
    scene_charge = selected_record->unk_00;
    return selected_record->unk_00;
}
