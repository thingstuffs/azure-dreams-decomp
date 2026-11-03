#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Calls func_8001A490 with Fp_far_kenkatyu. */
void invoke_alternate_handler_with_code_11_fb(void) {
    clear_script_flag_bit(Fp_far_kenkatyu);
}
