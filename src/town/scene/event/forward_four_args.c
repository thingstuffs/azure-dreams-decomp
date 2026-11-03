#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/scene/event.h"
void apply_selected_entry_values(s32, s32, s32, s32);                            /* extern */

/* Forward the inputs to func_800176B8. */
void forward_scene_request_arguments(s32 input_a, s32 input_b, s32 input_c, s32 input_d) {
    apply_selected_entry_values(input_a, input_b, input_c, input_d);
}
