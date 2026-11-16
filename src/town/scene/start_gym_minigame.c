#include "script_symbols.h"
#include "town/scene/start_gym_minigame.h"
#include "town/player/state.h"

void start_gym_minigame(void) {
    town_scene_root->services->callback_2C0();
    D_80017698 = &D_800175E4;
    clear_script_flag_bit(F_sbs08_pad04);
}
