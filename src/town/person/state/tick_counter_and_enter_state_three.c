#include "common.h"

#include "records/Rec_func_80094268_arg0.h"
#include "town/person/state.h"
typedef struct ReactionState ReactionState;

/* extern */

#include "town/person/object_setup.h"
/* Decrement the counter when the check returns zero and enter state 3 when it expires. */
void tick_counter_and_enter_state_three(Rec_func_80094268_arg0 *object, void *context_a, void *context_b, s32 check_arg) {
    u16 remaining_count;

    if (select_object_setup_path(object, context_a, context_b) == 0) {
        remaining_count = object->unk_6C.as_u16 - 1;
        object->unk_6C.as_u16 = remaining_count;
        if ((remaining_count << 0x10) <= 0) {
            object->unk_90.as_s16 = 3;
            func_800CDF00(object, context_a, context_b);
        }
    }
}
