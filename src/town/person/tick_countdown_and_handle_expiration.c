#include "common.h"
#include "shared/town_object.h"
void func_800CDFF8(void *, void *, void *);    /* extern */

#include "town/person/object_setup.h"
#include "town/person.h"
/* Decrement the object's countdown when its update returns zero and handle expiration. */
void tick_countdown_and_handle_expiration(TownObjectRecord *object, void *context_a, void *context_b, s32 update_arg) {
    u16 countdown;

    if (select_object_setup_path(object, context_a, context_b) == 0) {
        countdown = object->timer - 1;
        object->timer = countdown;
        if ((countdown << 0x10) <= 0) {
            object->unk_90 = 0;
            func_800CDFF8(object, context_a, context_b);
        }
    }
}
