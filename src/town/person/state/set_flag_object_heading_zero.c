#include "common.h"
#include "m2c_compat.h"
#include "town/person/state.h"


/* Clear the value at 0x72 and increment the counter at 0x68. */
void set_flag_object_heading_zero(TownObjectRecord *state) {
    state->heading = 0;
    state->unk_68 = (u16) (state->unk_68 + 1);
}
