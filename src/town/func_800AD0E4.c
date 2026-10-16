#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad0[0xA];
    u16 field_A;
} Obj800AD0E4;

extern void townInitializeSceneActionRecord(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void townInitializeMotionAction(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void func_800942B0(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void dungeonInitializeActionObject(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(Obj800AD0E4 *);
extern s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(Obj800AD0E4 *, void *);
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown(Obj800AD0E4 *, s16, void *);
extern void func_800A9F14(Obj800AD0E4 *);

extern u8 D_800CFCEF[9];

/* Update the object and dispatch actions based on its value, timer, and state flags. */
void func_800AA844(Obj800AD0E4 *timer_obj, Obj800AD0E4 *object, s32 action_arg) {
    GameWork *state = &gameWork;
    s16 next_value;
    u16 timer;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(object);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(object);
    next_value = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(object, ((u8 *)&D_800FE488));

    if ((next_value - (s16)object->field_A) >= 4) {
        if (D_800CFCEF[0] == 0) {
            dungeonInitializeActionObject(timer_obj, object, action_arg);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(object, next_value, ((u8 *)&D_800FE488));
    }

    timer = timer_obj->field_A - 1;
    timer_obj->field_A = timer;
    if ((s16)timer < 0) {
        townInitializeSceneActionRecord(timer_obj, object, action_arg);
        return;
    }

    if (((u32)state->buttons) & 0xF000) {
        townInitializeMotionAction(timer_obj, object, action_arg);
        return;
    }

    if (((u32)state->unk_010) & 0x10) {
        func_800942B0(timer_obj, object, action_arg);
        return;
    }

    func_800A9F14(object);
}
