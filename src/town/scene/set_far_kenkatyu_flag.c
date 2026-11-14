#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Calls func_8001A418 with Fp_far_kenkatyu. */
void set_far_kenkatyu_flag(void) {
    set_script_flag_bit(Fp_far_kenkatyu);
}
