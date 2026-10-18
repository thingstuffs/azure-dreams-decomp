#include "common.h"

s32 func_800B0718();                                /* extern */

/* Returns 20 minus the value reported by func_800B0718. */
s32 get_remaining_slot_capacity(void) {
    return 0x14 - func_800B0718();
}
