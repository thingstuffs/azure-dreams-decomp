#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Set unk_72 to 0x400 and increment unk_68. */
void set_flag_object_direction_400(TownObjectRecord *state) {
    state->heading.as_s16 = 0x400;
    state->unk_68 = (u16) (state->unk_68 + 1);
}
