#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

typedef struct S_805D21D8_1 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_805D21D8_1;   /* ((D_80016000->unk_08.at00_s32.v * 8) + D_80016000->unk_40.as_s32) in set_indexed_entry_flag_b */

/* Set the indexed entry's flag to 1. */
void set_indexed_entry_flag_b(void) {
    ((S_805D21D8_1 *)(((town_scene_root->entry_index * 8) + ((u8 *)town_scene_root->event_data))))->unk_04 = 1;
}
