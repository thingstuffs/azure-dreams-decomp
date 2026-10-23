#include "script_symbols.h"
#include "town/scene/invoke_state_callback.h"
#include "town/scene/invoke_state_callback.h"

void invoke_state_callback(void) {
    town_scene_root->services->callback_2C0();
    D_80017698 = &D_800175E4;
    func_8001746C(F_sbs08_pad04);
}
