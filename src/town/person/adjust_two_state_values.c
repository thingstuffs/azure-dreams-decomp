#include "common.h"
#include "town/person/object_setup.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person.h"
#include "town/person/state.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s32 D_800D5388[];

/* Initialize the actor and set its counter to 40 and its handler. */
void initialize_two_value_adjustment_action(TownObjectRecord *actor, s32 unused, void *init_param) {
    initialize_object_entries((actor), init_param, D_800D5388);
    actor->timer = 0x28;
    actor->handler = &adjust_two_state_values;
}
