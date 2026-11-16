#include "town/scene/start_casino_scene.h"

/* Select D_800174BC and invoke the state callback with zero. */
void start_casino_scene(void) {
    D_8001758C = D_800174BC;
    town_scene_root->services->callback_190(0);
}
