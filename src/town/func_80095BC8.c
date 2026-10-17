#include "common.h"
#include "records/Rec_func_80094268_arg0.h"



void townInitializeSharedSceneData();       /* extern */
void townInitializeSceneActionRecord();       /* extern */
void townCallTheHandlerSelectsNonzeroEntry();       /* extern */
s32 townRunTheActionSequenceContextUnlessFlagHexA5Set();           /* extern */
void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();       /* extern */
void townRunTheThreeUpdateRoutinesContext();       /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();       /* extern */
void townClearEntityRecordFields();       /* extern */
extern M2C_UNK D_800D0078;
extern s32 D_800FE518;


/* Updates the entity and dispatches a state transition when its countdown expires. */
void townUpdateEntityAndDispatchTimedState(void *state, void *entity, s32 transition_arg) {
    s16 countdown;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(entity);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(entity);
    countdown = ((Rec_func_80094268_arg0 *)state)->unk_0A.as_u16 - 1;
    ((Rec_func_80094268_arg0 *)state)->unk_0A.as_u16 = countdown;
    if (countdown < 0) {
        townClearEntityRecordFields(entity);
        townRunTheThreeUpdateRoutinesContext(entity);
        if (D_800FE518 != 0 && townRunTheActionSequenceContextUnlessFlagHexA5Set(state - 0x20) != 0) {
            townCallTheHandlerSelectsNonzeroEntry(&D_800D0078, state, transition_arg);
            townInitializeSharedSceneData(state, entity, transition_arg);
            return;
        }
        townInitializeSceneActionRecord(state, entity, transition_arg);
    }
}
