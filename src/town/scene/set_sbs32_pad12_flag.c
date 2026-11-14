#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Calls func_8001A554 with F_sbs32_pad12. */
void set_sbs32_pad12_flag(void) { set_script_flag_bit(F_sbs32_pad12); }
