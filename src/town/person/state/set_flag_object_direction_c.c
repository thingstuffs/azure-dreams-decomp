#include "common.h"
#include "m2c_compat.h"
#include "town/person/state.h"


/* Sets unk_72 to 0xC00 and increments the unk_68 counter. */
void set_flag_object_direction_12_c(TownObjectRecord *state) {
    state->heading = 0xC00;
    state->unk_68 = (u16) (state->unk_68 + 1);
}
