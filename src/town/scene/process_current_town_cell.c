#include "script_symbols.h"
#include "common.h"
#include "town/scene/mode_data.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/state_data.h"
#include "town/scene/record_actions.h"
#include "town/scene.h"
#include "town/player/state.h"
#include "town/scene/event.h"

/* Dispatches the current cell's action and clears its status after completion or a status-1 fallback. */
s32 process_current_town_cell(TownObjectSet *input_value, s32 input) {
    s32 result;
    u8 state;

    state = ((TownEntryStatus *)town_scene_root->event_data)[town_scene_root->entry_index].state;
    scene_cell_dispatch_code = state;
    result = 0;
    if ((state != 2) && (get_script_flag_mask(F_sbs14_pad21) != 0)) {
        result = apply_selected_entry_values(input_value, input);
    }
    if (result != 0) {
        ((TownEntryStatus *)town_scene_root->event_data)[town_scene_root->entry_index].state = 0;
        scene_cell_dispatch_code = 0;
    } else {
        invoke_callback_event_11();
        if (scene_cell_dispatch_code == 1) {
            ((TownEntryStatus *)town_scene_root->event_data)[town_scene_root->entry_index].state = 0;
            scene_cell_dispatch_code = 0;
        }
    }
    return result;
}

/* MECHANISM: The retail prologue is driven by arg0/arg1 held in s1/s2 and
   the conditional helper result held in s0; the if/else around the tail
   (instead of an early `return`) keeps s0 across the zero-edge. The tail
   pseudo-call func_8001709C (true base +0xD8, this row's own epilogue) was
   replaced by a return 2026-09-22 (byte-exact). */
