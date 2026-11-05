#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "engine/window.h"
#include "town/menu.h"

extern void update_scale_effect_and_advance();


/* Set the object state and initialize both fields with the generated value. */
void initialize_randomized_scale_timer(TownObjectRecord *object, void *unused_state, void *unused_context) {
    s16 initial_value;

    object->unk_50.as_pm = &update_scale_effect_and_advance;
    initial_value = scale_random_to_unsigned_halfword_limit(0x60) + 0xC0;
    object->unk_90 = initial_value;
    object->timer = initial_value;
}
