#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"


/* Set unk_72 to 0x400 and increment unk_68. */
void set_flag_object_heading_quarter_turn(TownObjectRecord *state) {
    state->heading = 0x400;
    state->unk_68 = (u16) (state->unk_68 + 1);
}
