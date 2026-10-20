#include "engine/scene/slot_transition.h"
s16 D_80081500 = 0;
#include "engine/scene/slot_transition.h"

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
#include "engine/scene/slot_transition.h"

/* Runs the per-tick update and installs func_80043E04 when the current slot is free. */
void func_80043DB8(void) {
    render_object_scene_frame();
    if (D_80083120[D_80081500].type == 0) {
        set_scene_phase_callback((int) func_80043E04);
    }
}
#include "shared/runtime_dispatch.h"
#include "engine/scene/slot_transition.h"

/* Updates the frame, then allocates a slot and installs func_80043E60 if signaled, otherwise calls update_shoulder_button_angle. */
void func_80043E04(void) {
    render_object_scene_frame();
    if (D_80082E60.unk_0E != 0) {
        D_80081500 = reserve_runtime_slot(6, 8);
        set_scene_phase_callback((int) func_80043E60);
    } else {
        update_shoulder_button_angle();
    }
}
#include "engine/scene/slot_transition.h"

/* Updates the frame, then sets bit 0 and calls scene_save_previous_mode_and_reset_callbacks if the current slot is unflagged. */
void func_80043E60(void) {
    render_object_scene_frame();
    if (D_80083120[D_80081500].type == 0) {
        D_80082E60.field_0 |= 1;
        scene_save_previous_mode_and_reset_callbacks();
    }
}
