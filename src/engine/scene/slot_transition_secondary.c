#include "engine/scene/slot_transition.h"
#include "shared/runtime_dispatch.h"

s16 secondary_transition_slot_index = 0;

/* Updates controller and dispatch state, then allocates a slot and schedules func_80043DB8 if callbacks do not signal completion. */
void func_80043D04(void)
{
    unsigned int source_value;
    struct SlotTransitionState *state;

    source_value = gpu_scratch_buffer_base;
    gpu_scratch_write_pointer = source_value;
    update_controller_buttons_and_triggers();

    state = &D_80082E60;
    upload_dispatch_entry_images(state->field_B);
    upload_dispatch_entry_vram_rows(state->field_B);
    load_dispatch_entry_files(state->field_B);
    if (run_dispatch_entry_callbacks(state->field_B)) {
        scene_save_previous_mode_and_reset_callbacks();
    } else {
        secondary_transition_slot_index = reserve_runtime_slot(5, 8);
        D_80082E60.field_0 &= ~1;
        set_scene_phase_callback((s32)render_object_scene_until_slot_idle);
    }
}

/* Runs the per-tick update and installs func_80043E04 when the current slot is free. */
void render_object_scene_until_slot_idle(void) {
    render_object_scene_frame();
    if (runtime_transition_slots[secondary_transition_slot_index].type == 0) {
        set_scene_phase_callback((int) await_object_scene_confirmation);
    }
}

/* Updates the frame, then allocates a slot and installs func_80043E60 if signaled, otherwise calls update_shoulder_button_angle. */
void await_object_scene_confirmation(void) {
    render_object_scene_frame();
    if (D_80082E60.unk_0E != 0) {
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
        D_80082E60.field_0 |= 1;
        scene_save_previous_mode_and_reset_callbacks();
    }
}
