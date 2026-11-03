#include "town/scene.h"
#include "town/player.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"
#include "town/player/state.h"


/* Start keima, select the fixed data pointer, and clear its script flag. */
void start_keima_and_clear_flag(void)
{
    town_scene_root->services->callback_1EC();
    D_80017AA4 = D_8001798C;
    clear_script_flag_bit(0x591);
}
