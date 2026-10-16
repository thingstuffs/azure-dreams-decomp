/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "shared/position_query.h"
#include "common.h"

extern void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(void *object);
extern void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(void *object);
extern s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(void *object, void *data);
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown(void *object, s16 value, void *data);
extern void dungeonInitializeActionObject(void *state, void *object, s32 context);
extern void func_800942B0(void *state, void *object, s32 context);

extern u8 D_800CFCEF[];

void func_80091F64(void *state, void *object, s32 context) {
    s16 target_value;
    u16 countdown;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(object);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(object);
    target_value = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(object, ((u8 *)&D_800FE488));
    if (target_value - *(s16 *)((u8 *)object + 0xA) >= 4) {
        if (D_800CFCEF[0] == 0) {
            dungeonInitializeActionObject(state, object, context);
            return;
        }
    } else {
        if (D_800CFCEF[0] == 0) {
            townComputeAndClampsVectorBasedAdjustmentUpdatesTown(object, target_value, ((u8 *)&D_800FE488));
        }
    }

    countdown = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = countdown;
    if ((s16)countdown < 0) {
        func_800942B0(state, object, context);
    }
}
