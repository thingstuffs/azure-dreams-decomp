#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Calls func_8001A510 with Ft_far_love. */
s32 has_far_love_flag(void) {
    return get_script_flag_mask(Ft_far_love);
}
