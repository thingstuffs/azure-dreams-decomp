#include "shared/position_query.h"
#include "common.h"

extern s16 townGetSmallerQueryResultCappedHex80WritesAssociatedOutput(void *, void *);
extern void townSetTheStateFlagInitializeSFixedPointClearPairedField(void *, void *, s16);
extern void townCallTheSameContextBothProcessingRoutines(void *, void *);
extern void townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(void *, void *);
extern void townDispatchActiveTownObjectScript(void *, void *, void *, void *);
extern void townSetActorDropState(void *, void *, void *, void *);

extern u8 D_8009B454[];
extern u8 D_8009B594[];
extern u8 D_8009BDC0[];

/* Update movement and height, transition the actor state, and copy its value to the context. */
void townUpdateActorSurfaceMotion(void *actor, void *subject, void *motion, void *context) {
    s16 surface_height;
    void *actor_callback;
    s32 *actor_value;

    surface_height = townGetSmallerQueryResultCappedHex80WritesAssociatedOutput(motion, ((u8 *)&D_800FE488));
    townCallTheSameContextBothProcessingRoutines(subject, motion);
    townHandleResolveBoundingBoxOverlapsLinkedCollidersAlongLeastPenetratingAxis(subject, motion);
    if (*(u8 *)((u8 *)subject + 0x3B) == 0) {
        if (surface_height - *(s16 *)((u8 *)motion + 0xA) >= 4) {
            townSetActorDropState(actor, subject, motion, context);
        } else {
            townSetTheStateFlagInitializeSFixedPointClearPairedField(subject, motion, surface_height);
            *(s32 *)((u8 *)motion + 0xC) = 0;
            *(s32 *)((u8 *)motion + 0x10) = 0;
            *(s32 *)((u8 *)motion + 0x14) = 0;
            *(void **)((u8 *)actor + 0x50) = D_8009B594;
        }
    }
    townDispatchActiveTownObjectScript(actor, subject, motion, context);
    actor_callback = *(void **)((u8 *)actor + 0x50);
    if (actor_callback != D_8009B454 && actor_callback != D_8009B594 && actor_callback != D_8009BDC0) {
        actor_value = *(s32 **)((u8 *)actor + 0x7C);
        if (actor_value != 0)
            *(s32 *)((u8 *)context + 8) = *actor_value;
    }
}
