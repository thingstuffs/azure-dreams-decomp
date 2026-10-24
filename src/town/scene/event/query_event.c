#include "town/player.h"
#include "script_symbols.h"
#include "common.h"

/* Call get_script_flag_mask with request 0xD82. */
void query_event_d_82(void) {
    get_script_flag_mask(Ftt_pad81);
}
