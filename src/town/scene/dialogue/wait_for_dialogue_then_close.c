#include "modules/town_ovl_3ef1c8.h"

/* Returns one when func_80019928 (process_checked_entry) accepts the entry; otherwise runs
 * func_800187AC and returns zero. */
s32 wait_for_dialogue_then_close(void *object, s32 entry_index) {
    if (func_80019928(object, entry_index) != 0) {
        return 1;
    }
    func_800187AC();
    return 0;
}
