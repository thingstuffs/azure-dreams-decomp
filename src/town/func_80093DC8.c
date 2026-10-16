#include "shared/position_query.h"
#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern s32 testResidentBitmapBit(s32 value);
extern s32 scaleRandomToUnsignedHalfwordLimit(s32 value);
extern s32 runtimeEstimateVectorLength(s32 value, s32 other_value);
extern void func_8008B158(s32 value);
extern void townInitializeSceneActionRecord(void *action_state, void *actor, s32 context);
extern void func_80093E18(void *action_state, void *actor, s32 context);
extern void townInitializeMotionAction(void *action_state, void *actor, s32 context);
extern void func_80094088(void *action_state, void *actor, s32 context);
extern void func_800942B0(void *action_state, void *actor, s32 context);
extern void dungeonInitializeActionObject(void *action_state, void *actor, s32 context);
extern void func_800943B8(void *action_state, void *actor, s32 context);
extern void dungeonInitializeActionObjectWithCounter(void *action_state, void *actor, s32 context);
extern void func_8009451C(void *action_state, void *actor, s32 context);
extern void townTriggerEventHex519IntervalMultiplesEnabled(s16 timer, s32 limit);
extern void townStoreTheValidSharedAngleInOffsetHex10(void *action_state);
extern void townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58(void *actor);
extern void townMoveTheActorPerpendicularSelectedDirectionUnlessStepChangesSides(void *actor);
extern s32 townSelectAnAvailableEntryMatchingDirectionReturnsStatus(void *menu_state);
extern s32 townSelectAnEligibleSourceEntryStoresPointerInDestination(void *action_state, void *menu_state);
extern s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(void *actor, void *map_work);
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown(void *actor, s16 height, void *map_work);
extern void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(void *actor);
extern void townSpawnDirectionalEffects(void *actor, s32 value);
extern void townInitializeRecordAndSelectActiveData(void *action_state, void *actor, s32 context);
extern s32 D_800CFCB4;
extern u8 D_800CFCEF;
/* Updates the actor and dispatches town actions from input and interaction state. */
void townUpdateActorInputAndInteraction(void *action_state, void *actor, s32 context)
{
    u8 *input_state = ((u8 *)(&gameWork));
    register s32 saved_context;
    u8 *map_work;
    u8 *menu_state;
    s16 sampled_height;
    u16 timer;
    s32 buttons;
    s32 action_result;
    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(actor);
    townMoveTheActorPerpendicularSelectedDirectionUnlessStepChangesSides(actor);
    map_work = ((u8 *)&D_800FE488);
    sampled_height = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(actor, map_work);
    if ((sampled_height - (*((s16 *) (((u8 *) actor) + 0xA)))) >= 4) {
        if (D_800CFCEF == 0) {
            dungeonInitializeActionObject(action_state, actor, context);
            return;
        }
    }
    else
        if (D_800CFCEF == 0) {
            townComputeAndClampsVectorBasedAdjustmentUpdatesTown(actor, sampled_height, map_work);
        }
    timer = (*((u16 *) (((u8 *) action_state) + 0xA))) - 1;
    *((u16 *) (((u8 *) action_state) + 0xA)) = timer;
    if (((s16) timer) <= 0) {
        timer = scaleRandomToUnsignedHalfwordLimit(4) + 6;
        *((u16 *) (((u8 *) action_state) + 0xA)) = timer;
        townSpawnDirectionalEffects(actor, ((u16) scaleRandomToUnsignedHalfwordLimit(2)) + 2);
    }
    buttons = *((s32 *) (input_state + 0x10));
    if (buttons & 0x10) {
        func_800942B0(action_state, actor, context);
        return;
    }
    if (buttons & 0x40) {
        action_result = townSelectAnEligibleSourceEntryStoresPointerInDestination(action_state, &D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                func_8009451C(action_state, actor, context);
                return;
            }
            dungeonInitializeActionObjectWithCounter(action_state, actor, context);
            return;
        }
        if (testResidentBitmapBit(0xA4) != 0) {
            func_80094088(action_state, actor, context);
            return;
        }
        return;
    }
    menu_state = (u8 *) (&D_800CFCB4);
    action_result = townSelectAnAvailableEntryMatchingDirectionReturnsStatus(menu_state);
    if (action_result != 0) {
        if (action_result == (-1)) {
            townStoreTheValidSharedAngleInOffsetHex10(action_state);
            townInitializeRecordAndSelectActiveData(action_state, actor, context);
            *((s32 *) (((u8 *) action_state) + 0x2C)) = 0;
            func_8008B158(*((s32 *) (menu_state + 0x10)));
            return;
        }
        func_800943B8(action_state, actor, context);
        return;
    }
    buttons = *((s32 *) (input_state + 8));
    if (!(buttons & 0x20)) {
        townInitializeMotionAction(action_state, actor, context);
        townStoreTheValidSharedAngleInOffsetHex10(action_state);
        townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58(actor);
        return;
    }
    if (buttons & 0xF000) {
        timer = (*((u16 *) (((u8 *) action_state) + 0x3E))) - 1;
        *((u16 *) (((u8 *) action_state) + 0x3E)) = timer;
        townTriggerEventHex519IntervalMultiplesEnabled((s16) timer, 8);
        townStoreTheValidSharedAngleInOffsetHex10(action_state);
        townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58(actor);
        return;
    }
    action_result = runtimeEstimateVectorLength(*((s32 *) (((u8 *) actor) + 0xC)), *((s32 *) (((u8 *) actor) + 0x10)));
    if (action_result > 0xFFFFF) {
        func_80093E18(action_state, actor, context);
        return;
    }
    townInitializeSceneActionRecord(action_state, actor, context);
}
