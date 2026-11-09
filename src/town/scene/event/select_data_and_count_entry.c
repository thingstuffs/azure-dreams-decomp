#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/event.h"
#include "town/scene.h"
#include "town/scene/flags.h"

extern s32 D_80018AF8;
extern s32 D_80019A30;

/* Updates shared state and increments the current table entry if the selector-10 check returns zero. */
s32 *select_data_and_count_entry(void *value, s32 unused, s32 selector) {
    Rec_D_80016000 *context;
    u8 *entry;
    s32 *count_ptr;
    u8 **table_ptr;
    u32 entry_offset;

    apply_entry_keyed_values(&D_80018AF8, value, selector);
    if (selector == 10 && resolve_entry_flag(&D_80018AF8, value, 10) == 0) {
        context = town_scene_root;
        count_ptr = (s32 *)((u8 *)context + 8);
        table_ptr = (u8 **)((u8 *)context + 0x40);
        entry_offset = *count_ptr * 8;
        entry = (u8 *)(entry_offset + (unsigned long)*table_ptr);

        *entry += 1;
    }
    return &D_80019A30;
}
