#include "slus/slot_transition.h"

/* Updates controller and dispatch state, then allocates a slot and schedules func_80043DB8 if callbacks do not signal completion. */
void func_80043D04(void)
{
    unsigned int source_value;
    struct SlotTransitionState *state;

    source_value = D_8008148C;
    D_80081480 = source_value;
    update_controller_buttons_and_triggers();

    state = &D_80082E60;
    upload_dispatch_entry_images(state->field_B);
    upload_dispatch_entry_vram_rows(state->field_B);
    load_dispatch_entry_files(state->field_B);
    if (run_dispatch_entry_callbacks(state->field_B)) {
        scene_save_previous_mode_and_reset_callbacks();
    } else {
        D_80081500 = reserve_runtime_slot(5, 8);
        D_80082E60.field_0 &= ~1;
        set_scene_phase_callback((s32)func_80043DB8);
    }
}
