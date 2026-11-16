#include "modules/town_ovl_4d9100.h"

/* Invokes the callback and points the shared pointer at D_800173FC. */
void init_keima2_scene(void *callback_arg) {
    ((s32 (*)(void *))town_scene_root->services->callback_1F0)(callback_arg);
    D_80017494 = D_800173FC;
}
