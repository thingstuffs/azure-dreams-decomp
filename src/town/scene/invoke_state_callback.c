#include "script_symbols.h"
#include "town/scene/invoke_state_callback.h"
#include "town/player/state.h"

void invoke_state_callback(void) {
    town_scene_root->services->callback_2C0();
    D_80017698 = &D_800175E4;
    clear_script_flag_bit(F_sbs08_pad04);
}
