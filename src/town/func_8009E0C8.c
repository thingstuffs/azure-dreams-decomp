#include "common.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009B828_arg0.h"

void townCallTheSameContextBothProcessingRoutines();             /* extern */
void townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis();             /* extern */
void townAddMotionDeltasToPosition();                 /* extern */
void townInitializeTargetMotion(); /* extern */
extern s32 D_800D0428;


/* Update motion toward the shared target and advance state when the countdown expires. */
void townUpdateMotionTowardSharedTarget(Rec_func_8009B828_arg0 *state, s32 context, EntityRec *motion, s32 transition_arg) {
    s32 position;
    u16 ticks_left;

    position = motion->z.v;
    motion->flags14 = (s32) ((s32) ((D_80083780.z.v + D_800D0428) - position) / 2);
    townAddMotionDeltasToPosition(motion, position);
    townCallTheSameContextBothProcessingRoutines(context, motion);
    townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(context, motion);
    ticks_left = state->unk_6C.as_u16 - 1;
    state->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        townInitializeTargetMotion(state, context, motion, transition_arg);
    }
}
