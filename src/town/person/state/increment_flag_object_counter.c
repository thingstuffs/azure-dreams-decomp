#include "common.h"
#include "m2c_compat.h"
#include "town/person/state.h"


/* Increment the object's 16-bit counter at offset 0x68. */
void increment_flag_object_counter(TownObjectRecord *object) {
    object->unk_68 = (u16) (object->unk_68 + 1);
}
