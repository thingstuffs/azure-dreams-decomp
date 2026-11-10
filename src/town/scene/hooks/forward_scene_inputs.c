#include "common.h"
#include "town/scene/hooks.h"

s32 apply_selected_entry_values(s32, s32);

/* Forward the inputs to func_800176B8. */
void forward_scene_inputs(s32 input_a, s32 input_b, s32 input_c, s32 input_d) {
    apply_selected_entry_values(input_a, input_b);
}
