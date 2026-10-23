#include "common.h"
#include "shared/town_dispatch_object.h"

extern void select_data_for_condition_d_83(s32, s32, s32);
extern void apply_entry_position(s32 *, s32 *, s32, s32);
extern s32 scene_dispatch_started[];
extern s32 D_8001B964[];
extern s32 D_8001B994[];

/* Dispatch a code using the active table, with special handling for code 0x3E. */
void dispatch_active_code(s32 value, s32 special_value, s32 code) {
    s32 *active_table;

    if (scene_dispatch_started[0] != 0) {
        active_table = D_8001B994;
    } else {
        active_table = D_8001B964;
    }
    if ((u32)(code - 0x40) < 3U) {
        scene_dispatch_started[0] = 1;
    }
    if (code != 0x3E) {
        apply_entry_position(active_table, active_scene_dispatch_context, value, code);
    } else {
        select_data_for_condition_d_83(value, special_value, 0x3E);
    }
}
