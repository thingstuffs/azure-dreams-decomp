#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"

void dungeonBeginPlayerDamageReaction(); /* extern */
void dungeonApplyPendingByteIncrease(); /* extern */
void dungeonBeginPlayerSleepAction(); /* extern */

/* Dispatch state handlers according to the signed state value and actor flags. */
void dungeonDispatchActorStateHandler(Rec_func_8008ACDC_arg0 *actor, s32 context, Rec_D_80082E80 *object, EntityRec *state) {
    s16 state_value;

    state_value = state->unk_64;
    if ((state_value < 0) || (actor->unk_10C & 1)) {
        object->unk_14.at00_u16.v = (u16) (object->unk_14.at00_u16.v & 0xF7FF);
        dungeonBeginPlayerDamageReaction(actor, context, object, state);
        return;
    }
    if (state_value > 0) {
        dungeonApplyPendingByteIncrease(actor, context, object, state);
    }
    if ((actor->unk_9A.as_u8 != 0xD) && (state->flags1C & 0x200)) {
        object->unk_14.at00_u16.v = (u16) (object->unk_14.at00_u16.v & 0xF7FF);
        dungeonBeginPlayerSleepAction(actor, context, object, state);
    }
}
