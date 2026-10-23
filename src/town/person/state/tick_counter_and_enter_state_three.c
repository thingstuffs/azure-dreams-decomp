#include "common.h"

#include "records/Rec_func_80094268_arg0.h"
typedef struct ReactionState ReactionState;

/* extern */
void func_800CDF00(Rec_func_80094268_arg0 *actor, ReactionState *state, s8 *output);


s32 select_object_setup_path(void *object, s32 request_data, s32 request_param, s32 check_param);
/* Decrement the counter when the check returns zero and enter state 3 when it expires. */
void tick_counter_and_enter_state_three(Rec_func_80094268_arg0 *object, s32 context_a, s32 context_b, s32 check_arg) {
    u16 remaining_count;

    if (select_object_setup_path(object, context_a, context_b, check_arg) == 0) {
        remaining_count = object->unk_6C.as_u16 - 1;
        object->unk_6C.as_u16 = remaining_count;
        if ((remaining_count << 0x10) <= 0) {
            object->unk_90.as_s16 = 3;
            func_800CDF00(object, context_a, context_b);
        }
    }
}
