#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/state.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s8 D_80082710;
extern void apply_setup_on_timeout_variant_1();
extern s32 D_800D5360[];


/* Initialize the actor, clear the shared flag, and set its handler and counter. */
void initialize_actor_clear_shared_flag(TownObjectRecord *actor, s32 unused, void *init_param) {
    initialize_object_entries((actor), init_param, D_800D5360);
    D_80082710 = 0;
    actor->handler = &apply_setup_on_timeout_variant_1;
    actor->timer.as_s16 = 0x15;
}
