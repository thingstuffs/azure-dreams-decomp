#include "common.h"

extern s32 find_first_enabled_entry_id(void);
extern s32 check_event_value_in_list(s32);

/* Return the candidate if check_event_value_in_list succeeds, otherwise use find_first_enabled_entry_id. */
s32 choose_valid_entry_or_fallback(s32 candidate) {
    if (check_event_value_in_list(candidate) != 0) {
        return candidate;
    }
    return find_first_enabled_entry_id();
}
