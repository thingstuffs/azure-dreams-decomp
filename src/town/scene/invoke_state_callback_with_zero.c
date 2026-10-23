#include "town/scene/invoke_state_callback_with_zero.h"
#include "town/scene/invoke_state_callback_with_zero.h"

/* Select D_800174BC and invoke the state callback with zero. */
void invoke_state_callback_with_zero(void) {
    D_8001758C = D_800174BC;
    town_scene_root->services->callback_190(0);
}
