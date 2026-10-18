#include "slus/slot_transition.h"

/* Runs the per-tick update and installs func_80043E04 when the current slot is free. */
void func_80043DB8(void) {
    render_object_scene_frame();
    if (D_80083120[D_80081500].type == 0) {
        set_scene_phase_callback((int) func_80043E04);
    }
}
