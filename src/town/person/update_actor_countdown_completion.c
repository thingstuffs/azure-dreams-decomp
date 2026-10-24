#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object_setup.h"
void func_800CB73C(Rec_func_80094268_arg0 *);                            /* extern */
void allocate_variant_object(s32, s32, s32);                /* extern */


/* Decrement the actor's countdown and run its expiration actions when it expires. */
void update_actor_countdown_completion(Rec_func_80094268_arg0 *actor, void *update_context, void *setup_context) {
    u16 countdown;

    countdown = actor->unk_6C.as_u16 - 1;
    actor->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800CB73C(actor);
        allocate_variant_object(actor->unk_96.as_s8, actor->unk_88, actor->unk_8A);
        apply_object_setup_and_update(actor, update_context, setup_context);
    }
}
