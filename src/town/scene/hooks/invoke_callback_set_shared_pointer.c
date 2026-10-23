#include "modules/town_ovl_629100.h"
#include "modules/town_ovl_629100.h"

void invoke_callback_and_set_shared_pointer(void) {
    Callback firstCallback;

    firstCallback = ((Callback)town_scene_root->services->callback_28C);
    D_800174D4[0] = D_80017420;
    firstCallback(1);
    ((Callback)town_scene_root->services->callback_290)(1);
}
