#include "engine/scene/slot_transition.h"
#include "shared/runtime_dispatch.h"

s16 D_800814E8 = 0;

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

/* Runs the state update and registers the next callback when the current slot becomes inactive. */
void func_80041B98(void)
{
    render_scene_frame_with_timing();
    if (D_80083120[D_800814E8].type == 0) {
        set_scene_phase_callback((int)func_80041BE4);
    }
}

/* Runs the state update, then allocates a slot and advances the callback if enabled, or invokes the fallback. */
void func_80041BE4(void)
{
    render_scene_frame_with_timing();
    if (D_80082E60.unk_0E != 0) {
        if (D_80083120[D_800814E8].type == 0) {
            D_800814E8 = reserve_runtime_slot(6, 8);
        }
        set_scene_phase_callback((int) func_80041C64);
    } else {
        update_shoulder_button_angle();
    }
}

/* Runs the state update, then sets flag bit 0 and invokes scene_save_previous_mode_and_reset_callbacks when the current slot is inactive. */
void func_80041C64(void)
{
    render_scene_frame_with_timing();
    if (D_80083120[D_800814E8].type == 0) {
        D_80082E60.field_0 |= 1;
        scene_save_previous_mode_and_reset_callbacks();
    }
}
