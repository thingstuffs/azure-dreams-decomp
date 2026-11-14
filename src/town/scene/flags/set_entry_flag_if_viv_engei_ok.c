#include "script_symbols.h"
#include "town/scene/entry_flag_queries.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"

/* Raise event 0x5BC and, when check 0x9A passes, forward the pair to the handler. */
s32 set_entry_flag_if_viv_engei_ok(void *target, s32 value) {
    s32 result;

    clear_script_flag_bit(F_sbs11_pad25);
    if (get_script_flag_mask(F_viv_engei_ok) == 0) {
        result = 0;
    } else {
        set_indexed_entry_flag(target, value);
        result = 1;
    }

    return result;
}
