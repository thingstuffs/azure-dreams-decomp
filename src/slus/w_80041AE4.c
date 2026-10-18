#include "slus/slot_transition.h"

/* Refreshes controller input and runs the current entry's handlers, starting a state transition if none signals completion. */
void func_80041AE4(void)
{
    unsigned int copied_value;
    struct SlotTransitionState *state;

    copied_value = D_8008148C;
    D_80081480 = copied_value;
    update_controller_buttons_and_triggers();

    state = &D_80082E60;
    upload_dispatch_entry_images(state->field_B);
    upload_dispatch_entry_vram_rows(state->field_B);
    load_dispatch_entry_files(state->field_B);
    if (run_dispatch_entry_callbacks(state->field_B)) {
        scene_save_previous_mode_and_reset_callbacks();
    } else {
        D_80082E60.field_0 &= ~1;
        D_800814E8 = reserve_runtime_slot(5, 8);
        set_scene_phase_callback((s32)func_80041B98);
    }
}
