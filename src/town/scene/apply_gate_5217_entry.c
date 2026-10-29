#include "town/scene.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/flags.h"
#include "town/scene/hooks.h"

extern u8 D_8001C33C[];
extern u8 D_8001E36C[];
extern s32 advance_floor_event_counter(SquareSceneEntry *, s32);
extern void *select_record_by_mode(SquareSceneEntry *, s32, s32);
extern s32 process_checked_entry(void *, s32);

s32 apply_gate_5217_entry(SquareSceneEntry *entry, s32 entry_index) {
    if (get_script_flag_mask(5217) != 0) {
        set_current_entry_script_flag();
    }
    return apply_selected_entry_values(entry, entry_index);
}

/* Complete choice array, including its terminal fallback record. */
TownSceneChoice square_gate_choices[4] = {
    { apply_gate_5217_entry, get_shared_entry_buffer, D_8001C33C, 3463, 0 },
    { advance_floor_event_counter, get_shared_entry_buffer, D_8001C33C, 3464, 0 },
    { return_zero_fn, select_record_by_mode, D_8001E36C, 3465, 0 },
    { return_zero_fn, get_shared_entry_buffer, D_8001C33C, 0, 0 },
};
