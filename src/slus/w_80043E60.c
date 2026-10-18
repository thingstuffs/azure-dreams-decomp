#include "slus/slot_transition.h"

/* Updates the frame, then sets bit 0 and calls scene_save_previous_mode_and_reset_callbacks if the current slot is unflagged. */
void func_80043E60(void) {
    render_object_scene_frame();
    if (D_80083120[D_80081500].type == 0) {
        D_80082E60.field_0 |= 1;
        scene_save_previous_mode_and_reset_callbacks();
    }
}
