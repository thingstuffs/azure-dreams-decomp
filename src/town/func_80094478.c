#include "shared/position_query.h"
#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();
void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();
s32 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();
M2C_UNK dungeonInitializeActionObject();
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();
void townCallTheHandlerSelectsNonzeroEntry();
M2C_UNK func_800941D8();

extern u8 D_800CFCEF;
extern M2C_UNK D_800D00E0;


/* Update the entity, handle a large value change, and advance the state countdown. */
void townUpdateThresholdTimedAction(Rec_func_80094268_arg0 *state, EntityRec *entity, M2C_UNK context) {
    s16 sampled_value;
    s16 ticks_left;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(entity);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(entity);
    sampled_value = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(entity, &D_800FE488);
    if ((sampled_value - entity->z.w.i) >= 4) {
        if (D_800CFCEF == 0) {
            dungeonInitializeActionObject(state, entity, context);
            return;
        }
    } else if (D_800CFCEF == 0) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(entity, sampled_value, &D_800FE488);
    }
    if (state->unk_0A.as_s16 == 0) {
        townCallTheHandlerSelectsNonzeroEntry(&D_800D00E0, state, context);
    }
    ticks_left = (u16) state->unk_0A.as_s16 - 1;
    state->unk_0A.as_s16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_800941D8(state, entity, context);
    }
}
