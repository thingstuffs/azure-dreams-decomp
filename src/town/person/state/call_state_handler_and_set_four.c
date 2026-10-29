#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/person/state.h"

/* extern */
extern s8 person_slot_reset_byte;

void func_800CEB00(Rec_func_80094268_arg0 *, s32, s32);
/* Call func_800CEB00, clear D_80082688, and set the object state to 4. */
void call_state_handler_and_set_four(Rec_func_80094268_arg0 *object, s32 context, s32 update_data) {
    func_800CEB00(object, context, update_data);
    person_slot_reset_byte = 0;
    object->unk_90.as_s16 = 4;
}
