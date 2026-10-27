#include "common.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/entry_requests.h"


/* Returns whether every entry in a zero-terminated list passes get_script_flag_mask. */
s32 all_entries_pass_check(s16 *values) {
    s16 *valueCursor;

    for (valueCursor = values; *valueCursor != 0; valueCursor++) {
        if (get_script_flag_mask(*valueCursor) == 0) {
            break;
        }
    }
    return *valueCursor == 0;
}
