#include "shared/runtime_dispatch.h"
#include "common.h"

extern s32 D_80080A7C;
extern s32 D_8008148C;
extern s32 D_80081480;

extern u8 D_80126804[];

extern void load_dispatch_entry_files(u16);
extern void queue_mode_selected_resource_table(void);
extern s32 read_combined_controller_buttons(s32);
extern void load_scene_resource_group(s16);

/* Selects the next mode, clears transient state, and dispatches mode setup. */
void select_next_scene_mode(void)
{
    RuntimeDispatchState *state_ptr = &D_80082E60;
    RuntimeDispatchState *reset_state;
    s32 saved_data_addr;
    s32 buffer_size;
    s32 next_mode;
    u8 flags;

    buffer_size = 0x38000;
    saved_data_addr = D_8008148C;
    D_80080A7C = buffer_size;
    D_80081480 = saved_data_addr;
    flags = state_ptr->field_B;
    if (flags != 0) {
        next_mode = 3;
    } else {
        D_8008148C = (s32)D_80126804;
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
    reset_state = &D_80082E60;
    buffer_size = reset_state->field_B;
    flags = reset_state->flags0F;
    reset_state->field_D = 0;
    reset_state->field_C = 0;
    reset_state->field_18 = 0;
    reset_state->flags0F = flags & 0x7E;
    load_scene_resource_group(buffer_size);
}
