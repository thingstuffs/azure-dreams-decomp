#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/script_flags.h"

/* Call get_script_flag_mask with request 0xD82. */
s32 get_script_flag_tt_pad81(void) {
    return get_script_flag_mask(Ftt_pad81);
}
