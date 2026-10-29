#include "common.h"
#include "m2c_compat.h"
#include "town/scene/event.h"

extern s32 D_8001E958;
extern M2C_UNK D_80021CC0;

/* Clear D_8001E958 and return the address of D_80021CC0. */
s32 *clear_event_resource_state_and_get_buffer(void) {
    D_8001E958 = 0;
    return &D_80021CC0;
}
