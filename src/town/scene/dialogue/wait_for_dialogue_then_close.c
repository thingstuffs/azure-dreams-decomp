#include "modules/town_ovl_3ef1c8.h"
#include "town/scene/dialogue.h"
#include "town/scene/event.h"

/* Returns one when func_80019928 (process_checked_entry) accepts the entry; otherwise runs
 * func_800187AC and returns zero. */
s32 wait_for_dialogue_then_close(void *object, s32 entry_index) {
    if (process_checked_entry(object, entry_index) != 0) {
        return 1;
    }
    invoke_callback_event_11();
    return 0;
}
