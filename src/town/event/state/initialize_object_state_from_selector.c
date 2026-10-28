#include "common.h"
#include "town/scene/list_setup.h"
#include "shared/sprite_frame_state.h"
#include "town/event/object_setup.h"


extern s32 town_object_resource_table[];
extern s32 D_800F8CEC[];

// Assigns the state's data table and invokes the shared handlers.
void initialize_object_state_from_selector(void *context, void *selector, SpriteFrameState *state) {
    state->source = D_800F8CEC;
    configure_the_set_mode_n_3(context, selector, town_object_resource_table);
    initialize_optional_object_state(context, selector, state, 0);
}
