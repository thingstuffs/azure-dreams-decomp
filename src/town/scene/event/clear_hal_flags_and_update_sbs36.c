#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"

/* Apply five operations through func_8001779C, then process 0x9E1. */
void clear_hal_flags_and_update_sbs36(void) {
    clear_script_flag_bit(F_hal_cansel);
    clear_script_flag_bit(F_hal_build);
    clear_script_flag_bit(F_sbs36_pad04);
    clear_script_flag_bit(F_sbs36_pad05);
    clear_script_flag_bit(F_sbs36_pad06);
    set_script_flag_bit(F_sbs36_pad11);
}
