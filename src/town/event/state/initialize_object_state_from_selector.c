#include "common.h"

extern void configure_the_set_mode_n_3(void *record, s32 setup_value, void *setup_param);
extern void initialize_optional_object_state(void *object, s32 context, void *state, void *init_value);

extern s32 town_object_resource_table[];
extern s32 D_800F8CEC[];

// Assigns the state's data table and invokes the shared handlers.
void initialize_object_state_from_selector(void *context, s32 selector, void *state) {
    *(void **)((u8 *)state + 8) = D_800F8CEC;
    configure_the_set_mode_n_3(context, selector, town_object_resource_table);
    initialize_optional_object_state(context, selector, state, 0);
}
