#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

s32 testResidentBitmapBit();                         /* extern */
M2C_UNK func_80094088();     /* extern */
void func_800942B0();     /* extern */
M2C_UNK dungeonInitializeActionObject();     /* extern */
void func_80094414();     /* extern */
M2C_UNK func_80094474();     /* extern */
M2C_UNK dungeonInitializeActionObjectWithCounter();     /* extern */
M2C_UNK func_8009451C();     /* extern */
void townStoreTheValidSharedAngleInOffsetHex10();                      /* extern */
void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();                      /* extern */
s32 townSelectAnAvailableEntryMatchingDirectionReturnsStatus(void *);            /* extern */
s32 townSelectAnEligibleSourceEntryStoresPointerInDestination();               /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      /* extern */
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800CFCEF;


typedef struct S_80092320_1 {
    u8 unk_00;
} S_80092320_1;   /* &D_800CFCEF in townUpdateActorMovementActions */

typedef struct S_80092320_2 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80092320_2;   /* state in townUpdateActorMovementActions */


/* Update the actor and select an action from the reference value, state flags, and timer. */
void townUpdateActorMovementActions(Rec_func_80094268_arg0 *action, EntityRec *actor, s32 context) {
    GameWork *state = &gameWork;
    s16 reference_value;
    s32 action_result;
    u16 ticks_left;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(actor);
    townStoreTheValidSharedAngleInOffsetHex10(action);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(actor);
    reference_value = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(actor, &D_800FE488);
    if ((reference_value - actor->z.w.i) >= 4) {
        if (((S_80092320_1 *)(&D_800CFCEF))->unk_00 == 0) {
            dungeonInitializeActionObject(action, actor, context);
            return;
        }
    } else if (((S_80092320_1 *)(&D_800CFCEF))->unk_00 == 0) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(actor, reference_value, &D_800FE488);
    }
    if (((s32)state->unk_010) & 0x10) {
        func_800942B0(action, actor, context);
        return;
    }
    ticks_left = action->unk_0A.as_u16 - 1;
    action->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left < 0) {
        func_80094414(action, actor, context);
        return;
    }
    if (((s32)state->unk_010) & 0x40) {
        action_result = townSelectAnEligibleSourceEntryStoresPointerInDestination(action, &D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                func_8009451C(action, actor, context);
                return;
            }
            dungeonInitializeActionObjectWithCounter(action, actor, context);
            return;
        }
        if (testResidentBitmapBit(0xA4) != 0) {
            func_80094088(action, actor, context);
            return;
        }
    } else if (townSelectAnAvailableEntryMatchingDirectionReturnsStatus(&D_800CFCB4) <= 0) {
        func_80094474(action, actor, context);
    }
    return;
}
