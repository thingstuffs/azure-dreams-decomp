#include "common.h"
#include "m2c_compat.h"
#include "town/person/state.h"


/* Clear the value at 0x72 and increment the counter at 0x68. */
void clear_flag_object_direction(TownObjectRecord *state) {
    state->heading.as_s16 = 0;
    state->unk_68 = (u16) (state->unk_68 + 1);
}
