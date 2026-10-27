#include "town/scene.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"

extern u8 D_8001C33C[];
extern u8 D_8001E240[];
extern u8 D_8001E27C[];
extern u8 D_8001E2E0[];
extern void *process_event_145_c_and_dispatch(SquareSceneEntry *, s32, s32);
extern s32 set_record_flag_on_query_failure(SquareSceneEntry *, s32);
extern void *dispatch_request_by_mode(SquareSceneEntry *, s32, s32);
extern s32 forward_context_request_to_handler(SquareSceneEntry *, s32);
extern s32 dispatch_entry_for_active_flags(SquareSceneEntry *, s32);
extern void *select_event_data_and_fallback(SquareSceneEntry *, s32, s32);
extern s32 func_80017410(SquareSceneEntry *, s32);
extern void *get_shared_entry_buffer(SquareSceneEntry *, s32, s32);
extern s32 return_zero_fn(SquareSceneEntry *, s32);
extern void set_current_entry_script_flag(void);
extern s32 process_checked_entry(void *, s32);

s32 apply_gate_5000_entry(SquareSceneEntry *entry, s32 entry_index) {
    if (get_script_flag_mask(5000) != 0) {
        set_current_entry_script_flag();
    }
    return apply_selected_entry_values(entry, entry_index);
}

/* Complete choice array, including its terminal fallback record. */
TownSceneChoice square_progress_choices[6] = {
    { set_record_flag_on_query_failure, process_event_145_c_and_dispatch, D_8001E240, 3431, 0 },
    { apply_gate_5000_entry, get_shared_entry_buffer, D_8001C33C, 3432, 0 },
    { forward_context_request_to_handler, dispatch_request_by_mode, D_8001E27C, 3433, 0 },
    { dispatch_entry_for_active_flags, get_shared_entry_buffer, D_8001C33C, 3434, 0 },
    { func_80017410, select_event_data_and_fallback, D_8001E2E0, 3435, 0 },
    { return_zero_fn, get_shared_entry_buffer, D_8001C33C, 0, 0 },
};
