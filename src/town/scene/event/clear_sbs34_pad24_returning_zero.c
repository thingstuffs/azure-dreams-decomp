#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"


/* Calls func_8001860C with 0x998 and returns zero. */
s32 clear_sbs34_pad24_returning_zero(void) {
    clear_script_flag_bit(F_sbs34_pad24);
    return 0;
}
