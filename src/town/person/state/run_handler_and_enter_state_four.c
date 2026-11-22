#include "common.h"
#include "shared/town_object.h"
#include "town/person/state.h"
#include "town/data.h"

/* extern */

void func_800CEB00(TownObjectRecord *, ObjectPosition *, SpriteFrameState *);
/* Call func_800CEB00, clear D_80082688, and set the object state to 4. */
void run_handler_and_enter_state_four(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    func_800CEB00(object, position, sprite);
    person_slot_reset_byte = 0;
    object->unk_90 = 4;
}
