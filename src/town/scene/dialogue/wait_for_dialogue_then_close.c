#include "modules/town_ovl_3ef1c8.h"

/* Returns one when func_80019928 is nonzero; otherwise runs func_800187AC and returns zero. */
s32 wait_for_dialogue_then_close(void) {
    if (func_80019928() != 0) {
        return 1;
    }
    func_800187AC();
    return 0;
}
