#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "engine/window.h"
#include "town/menu.h"

extern void D_800A7950();


/* Set the object state and initialize both fields with the generated value. */
void initialize_randomized_scale_timer(TownObjectRecord *object) {
    s16 initial_value;

    object->unk_50.as_pm = &D_800A7950;
    initial_value = scale_random_to_unsigned_halfword_limit(0x60) + 0xC0;
    object->unk_90.as_s16 = initial_value;
    object->timer.as_s16 = initial_value;
}
