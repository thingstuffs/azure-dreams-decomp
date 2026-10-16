#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townApplyObjectSetupAndUpdate();    /* extern */
void func_800CB73C(Rec_func_80094268_arg0 *);                            /* extern */
void townAllocateVariantObject();                /* extern */


/* Decrement the actor's countdown and run its expiration actions when it expires. */
void townUpdateActorCountdownCompletion(Rec_func_80094268_arg0 *actor, s32 action_arg1, s32 action_arg2) {
    u16 countdown;

    countdown = actor->unk_6C.as_u16 - 1;
    actor->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800CB73C(actor);
        townAllocateVariantObject(actor->unk_96.as_s8, actor->unk_88, actor->unk_8A);
        townApplyObjectSetupAndUpdate(actor, action_arg1, action_arg2);
    }
}
