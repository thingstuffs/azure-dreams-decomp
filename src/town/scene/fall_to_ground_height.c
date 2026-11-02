#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

short func_8025E01C(void *position);                          /* extern */


/* Advance the accumulator and reset it when lowering the stored value. */
void fall_to_ground_height(s32 unused, ObjectPosition *position) {
    ObjectPosition *object = position;
    s32 shifted_value;
    s32 new_value;

    shifted_value = func_8025E01C(object) << 0x10;
    object->velocity_z = (s32) (object->velocity_z + 0x1D000);
    new_value = shifted_value >> 0x10;
    if (new_value < object->z.w.i) {
        object->z.w.i = (s16) new_value;
        object->velocity_z = 0;
    }
}

/* MECHANISM: The unused first parameter puts the object pointer in $a1, held in $s0
   across func_8025E01C; this restores both the pre-save move and call-slot a0 copy.
   The seed's 24-byte frame, signed halfword compare, and RMW body were already exact. */
