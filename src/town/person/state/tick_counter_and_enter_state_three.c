#include "common.h"

#include "shared/town_object.h"
#include "town/person/state.h"
typedef struct ReactionState ReactionState;

/* extern */

#include "town/person/object_setup.h"
/* Decrement the counter when the check returns zero and enter state 3 when it expires. */
void tick_counter_and_enter_state_three(TownObjectRecord *object, void *context_a, void *context_b, s32 check_arg) {
    u16 remaining_count;

    if (select_object_setup_path(object, context_a, context_b) == 0) {
        remaining_count = object->timer - 1;
        object->timer = remaining_count;
        if ((remaining_count << 0x10) <= 0) {
            object->unk_90 = 3;
            initialize_actor_reaction_and_fixed_state(object, context_a, context_b);
        }
    }
}
