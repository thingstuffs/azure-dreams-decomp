#include "common.h"

s32 func_800177CC(s32, s32);
s32 func_8001860C(s32);

/* Calls the setup handler with 0x98F, then forwards the arguments. */
void advance_floor_event_counter(s32 value, s32 context) {
    func_8001860C(0x98F);
    func_800177CC(value, context);
}
