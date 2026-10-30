/* Alternate scene resource loading, confirmation waits and runtime-slot completion. */
#include "engine/scene/slot_transition.h"
#include "shared/runtime_dispatch.h"
#include "engine/graphics.h"
#include "engine/resource.h"
#include "engine/scene.h"

s16 secondary_transition_slot_index = 0;

/*
 * Resets the GPU scratch cursor, updates controller input, and loads the selected dispatch
 * resources. Saves the previous scene mode on callback completion, or reserves slot type 5/8 and
 * schedules rendering otherwise.
 */
void load_object_scene_dispatch_resources(void)
{
    unsigned int source_value;
    struct SlotTransitionState *state;

    source_value = gpu_scratch_buffer_base;
    gpu_scratch_write_pointer = source_value;
    update_controller_buttons_and_triggers();

    state = &runtime_dispatch_state;
    upload_dispatch_entry_images(state->field_B);
    upload_dispatch_entry_vram_rows(state->field_B);
    load_dispatch_entry_files(state->field_B);
    if (run_dispatch_entry_callbacks(state->field_B)) {
        scene_save_previous_mode_and_reset_callbacks();
    } else {
        secondary_transition_slot_index = reserve_runtime_slot(5, 8);
        runtime_dispatch_state.field_0 &= ~1;
        set_scene_phase_callback((s32)render_object_scene_until_slot_idle);
    }
}

/* Renders a scene frame and advances to confirmation once the selected transition slot is free. */
void render_object_scene_until_slot_idle(void) {
    render_object_scene_frame();
    if (runtime_transition_slots[secondary_transition_slot_index].type == 0) {
        set_scene_phase_callback((int) await_object_scene_confirmation);
    }
}

/*
 * Renders a frame, then reserves transition slot type 6/8 and installs the finish phase when
 * signaled; otherwise updates the shoulder-button angle.
 */
void await_object_scene_confirmation(void) {
    render_object_scene_frame();
    if (runtime_dispatch_state.unk_0E != 0) {
        secondary_transition_slot_index = reserve_runtime_slot(6, 8);
        set_scene_phase_callback((int) finish_object_scene_when_slot_idle);
    } else {
        update_shoulder_button_angle();
    }
}

/* Updates the frame, then sets bit 0 and calls scene_save_previous_mode_and_reset_callbacks if the current slot is unflagged. */
void finish_object_scene_when_slot_idle(void) {
    render_object_scene_frame();
    if (runtime_transition_slots[secondary_transition_slot_index].type == 0) {
        runtime_dispatch_state.field_0 |= 1;
        scene_save_previous_mode_and_reset_callbacks();
    }
}
