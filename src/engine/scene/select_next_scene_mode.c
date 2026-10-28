#include "shared/runtime_dispatch.h"
#include "common.h"
#include "engine/resource.h"
#include "slus/data.h"

extern s32 gpu_scratch_buffer_base;
extern s32 gpu_scratch_write_pointer;

#include "engine/scene.h"

/* Selects the next mode, clears transient state, and dispatches mode setup. */
void select_next_scene_mode(void)
{
    RuntimeDispatchState *state_ptr = &runtime_dispatch_state;
    RuntimeDispatchState *reset_state;
    s32 saved_data_addr;
    s32 buffer_size;
    s32 next_mode;
    u8 flags;

    buffer_size = 0x38000;
    saved_data_addr = gpu_scratch_buffer_base;
    gpu_scratch_ring_size = buffer_size;
    gpu_scratch_write_pointer = saved_data_addr;
    flags = state_ptr->field_B;
    if (flags != 0) {
        next_mode = 3;
    } else {
        gpu_scratch_buffer_base = (s32)gpu_scratch_ring_buffer;
        load_dispatch_entry_files(0);
        queue_mode_selected_resource_table();
        next_mode = read_combined_controller_buttons(0);
        if (next_mode != 0) {
            next_mode = 3;
        } else {
            next_mode = 1;
        }
    }
    state_ptr->field_B = next_mode;
    reset_state = &runtime_dispatch_state;
    buffer_size = reset_state->field_B;
    flags = reset_state->flags0F;
    reset_state->field_D = 0;
    reset_state->field_C = 0;
    reset_state->field_18 = 0;
    reset_state->flags0F = flags & 0x7E;
    load_scene_resource_group(buffer_size);
}
