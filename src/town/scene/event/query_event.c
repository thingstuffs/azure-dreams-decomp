#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

/* Call get_script_flag_mask with request 0xD82. */
s32 query_event_d_82(void) {
    return get_script_flag_mask(Ftt_pad81);
}
