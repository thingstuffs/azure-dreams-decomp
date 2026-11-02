#include "common.h"
#include "shared/town_object.h"
#include "town/person/state.h"
#include "town/data.h"

/* extern */

void func_800CEB00(TownObjectRecord *, s32, s32);
/* Call func_800CEB00, clear D_80082688, and set the object state to 4. */
void call_state_handler_and_set_four(TownObjectRecord *object, s32 context, s32 update_data) {
    func_800CEB00(object, context, update_data);
    person_slot_reset_byte = 0;
    object->unk_90.as_s16 = 4;
}
