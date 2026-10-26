#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/script_flags.h"


/* Process ID 0xD51 and return its preceding query result. */
s32 query_and_process_event_d_51(void) {
    s32 query_result;

    query_result = get_script_flag_mask(Ftt_pad32);
    set_script_flag_bit(Ftt_pad32);
    return query_result;
}
