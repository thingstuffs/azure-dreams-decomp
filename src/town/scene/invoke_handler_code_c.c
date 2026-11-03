#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Calls func_8001A418 with F_sbs22_pad04. */
void invoke_handler_with_code_780(void) {
    set_script_flag_bit(F_sbs22_pad04);
}
