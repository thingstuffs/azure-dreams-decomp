#include "common.h"
#include "m2c_compat.h"
#include "town/person/state.h"

extern s8 D_800826B8;


/* Clear the global flag and set the object's field at 0x6E to 0xC00. */
void reset_reaction_global_flag_and_angle(TownObjectRecord *object) {
    D_800826B8 = 0;
    object->unk_6E = 0xC00;
}
