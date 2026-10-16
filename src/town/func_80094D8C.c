#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"


#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 testResidentBitmapBit(s32);
extern void func_80094088(void *, void *, s32);
extern void func_800942B0(void *, void *, s32);
extern void dungeonInitializeActionObject(void *, void *, s32);
extern void func_80094474(void *, void *, s32);
extern void dungeonInitializeActionObjectWithCounter(void *, void *, s32);
extern void func_8009451C(void *, void *, s32);
extern void townStoreTheValidSharedAngleInOffsetHex10(void *);
extern void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(void *);
extern s32 townSelectAnAvailableEntryMatchingDirectionReturnsStatus(void *);
extern s32 townSelectAnEligibleSourceEntryStoresPointerInDestination(void *, void *);
extern s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(void *, void *);
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown(void *, s16, void *);
extern void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(void *);

extern s32 D_800CFCB4;
extern u8 D_800CFCEF;

/* Update the entity and dispatch its handler according to state flags and checks. */
void townUpdateActorInputActions(void *context, EntityRec *entity, s32 update_arg)
{
    GameWork *state = &gameWork;
    s16 reference_value;
    s32 state_flags;
    s32 check_result;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(entity);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(entity);
    reference_value = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(entity, ((u8 *)&D_800FE488));
    if ((reference_value - entity->z.w.i) >= 4) {
        if (D_800CFCEF == 0) {
            dungeonInitializeActionObject(context, entity, update_arg);
            return;
        }
    }
    else if (D_800CFCEF == 0) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(entity, reference_value, ((u8 *)&D_800FE488));
    }

    state_flags = ((s32)state->unk_010);
    if (state_flags & 0x10) {
        func_800942B0(context, entity, update_arg);
        return;
    }
    if (state_flags & 0x40) {
        check_result = townSelectAnEligibleSourceEntryStoresPointerInDestination(context, &D_800CFCB4);
        if (check_result != 0) {
            if (check_result == 2) {
                func_8009451C(context, entity, update_arg);
                return;
            }
            dungeonInitializeActionObjectWithCounter(context, entity, update_arg);
            return;
        }
        if (testResidentBitmapBit(0xA4) != 0) {
            func_80094088(context, entity, update_arg);
            return;
        }
    }
    else {
        if (state->buttons & 0xF000) {
            townStoreTheValidSharedAngleInOffsetHex10(context);
            if (townSelectAnAvailableEntryMatchingDirectionReturnsStatus(&D_800CFCB4) > 0) {
                return;
            }
        }
        func_80094474(context, entity, update_arg);
    }

    return;
}
