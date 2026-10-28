#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */


#include "town/person/object_setup.h"
/* Decrement the object countdown and call initialize_reaction_movement when it expires. */
void decrement_reaction_timer_and_reinitialize(Rec_func_80094268_arg0 *object, void *context, void *param) {
    u16 countdown;

    countdown = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        initialize_reaction_movement(object, context, param);
    }
}
