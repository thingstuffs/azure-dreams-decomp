/* Scene resource loading, confirmation waits and dispatch while a runtime slot remains active. */
#include "engine/scene/slot_transition.h"
#include "shared/runtime_dispatch.h"
#include "engine/graphics.h"
#include "engine/resource.h"
#include "engine/scene.h"

s16 transition_runtime_slot_index = 0;

/* Refreshes controller input and runs the current entry's handlers, starting a state transition if none signals completion. */
void load_scene_dispatch_resources(void)
{
    unsigned int copied_value;
    struct SlotTransitionState *state;

    copied_value = gpu_scratch_buffer_base;
    gpu_scratch_write_pointer = copied_value;
    update_controller_buttons_and_triggers();

    state = &runtime_dispatch_state;
    upload_dispatch_entry_images(state->field_B);
    upload_dispatch_entry_vram_rows(state->field_B);
    load_dispatch_entry_files(state->field_B);
    if (run_dispatch_entry_callbacks(state->field_B)) {
        scene_save_previous_mode_and_reset_callbacks();
    } else {
        runtime_dispatch_state.field_0 &= ~1;
        transition_runtime_slot_index = reserve_transition_slot(5, 8);
        set_scene_phase_callback((s32)render_scene_until_slot_idle);
    }
}

/* Runs the state update and registers the next callback when the current slot becomes inactive. */
void render_scene_until_slot_idle(void)
{
    render_scene_frame_with_timing();
    if (runtime_transition_slots[transition_runtime_slot_index].type == 0) {
        set_scene_phase_callback((int)await_scene_confirmation);
    }
}

/* Runs the state update, then allocates a slot and advances the callback if enabled, or invokes the fallback. */
void await_scene_confirmation(void)
{
    render_scene_frame_with_timing();
    if (runtime_dispatch_state.unk_0E != 0) {
        if (runtime_transition_slots[transition_runtime_slot_index].type == 0) {
            transition_runtime_slot_index = reserve_transition_slot(6, 8);
        }
        set_scene_phase_callback((int) finish_scene_when_slot_idle);
    } else {
        update_reset_button_hold();
    }
}

/* Runs the state update, then sets flag bit 0 and invokes scene_save_previous_mode_and_reset_callbacks when the current slot is inactive. */
void finish_scene_when_slot_idle(void)
{
    render_scene_frame_with_timing();
    if (runtime_transition_slots[transition_runtime_slot_index].type == 0) {
        runtime_dispatch_state.field_0 |= 1;
        scene_save_previous_mode_and_reset_callbacks();
    }
}
