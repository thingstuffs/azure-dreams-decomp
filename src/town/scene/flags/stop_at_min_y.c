#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

typedef struct S_8008F548_0 {
    u8 pad_00[0x38];
    s8 unk_38;
} S_8008F548_0;   /* arg0 in stop_at_min_y */


/*
 * Sets the object flag at offset 0x38, stores the supplied initial state at offset 4, and clears
 * its motion word at offset 0x10.
 */
void stop_at_min_y(S_8008F548_0 *object, ObjectPosition *state, s32 initial_value) {
    object->unk_38 = 1;
    state->y.v = initial_value;
    state->velocity_y = 0;
}
