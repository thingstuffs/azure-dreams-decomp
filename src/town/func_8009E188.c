#include "common.h"
#include "shared/entity_objects.h"


extern void townAddMotionDeltasToPosition(void *motion);
extern void townCallTheSameContextBothProcessingRoutines(void *value, void *context);
extern void townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(void *collider, void *position);
extern void townInitializeObjectAndMaybePlaySound(void *context, s32 object, void *state, s32 extra);

/* Update target-relative motion and advance when the countdown expires. */
void townUpdateMotionTowardTownTarget(void *state, s32 context, void *motion, s32 next_arg) {
    u16 ticks_left;

    *(s32 *)((u8 *)motion + 0xC) = (D_80083780.x.v - *(s32 *)motion) / 2;
    *(s32 *)((u8 *)motion + 0x10) = (D_80083780.y.v - *(s32 *)((u8 *)motion + 4)) / 2;
    townAddMotionDeltasToPosition(motion);
    townCallTheSameContextBothProcessingRoutines(context, motion);
    townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(context, motion);
    ticks_left = *(u16 *)((u8 *)state + 0x6C) - 1;
    *(u16 *)((u8 *)state + 0x6C) = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        townInitializeObjectAndMaybePlaySound(state, context, motion, next_arg);
    }
}
