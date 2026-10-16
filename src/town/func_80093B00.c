#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"


extern s32 testResidentBitmapBit();
extern void func_8008B158();
extern s32 townReadMapCellAtWorldPosition();
extern void townInitializeSceneActionRecord();
extern void func_80093E58();
extern void townInitializeRandomizedObjectAction();
extern void func_80093FC8();
extern void func_80094088();
extern void func_800942B0();
extern void dungeonInitializeActionObject();
extern void func_800943B8();
extern void dungeonInitializeActionObjectWithCounter();
extern void func_8009451C();
extern void townTriggerEventHex519IntervalMultiplesEnabled();
extern void townStoreTheValidSharedAngleInOffsetHex10();
extern void townHandleAdjustVectorTowardSelectedAngleLimitMagnitude();
extern void townReduceObjectCoordinatesTowardDirectionDependentLimitsWithoutOvershooting();
extern void townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58();
extern void townMoveTheActorPerpendicularSelectedDirectionUnlessStepChangesSides();
extern s32 townSelectAnAvailableEntryMatchingDirectionReturnsStatus();
extern s32 townSelectAnEligibleSourceEntryStoresPointerInDestination();
extern s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();
extern void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();
extern void townInitializeRecordAndSelectActiveData();
extern s32 townCheckMaskedValueInCurrentRange();

extern s32 D_800CFCB4[];
extern u8 D_800CFCEF[];


typedef struct S_80091260_2 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x14];
    s32 unk_2C;
    u8 pad_30[0xE];
    union { u16 u; s16 s; } unk_3E;   /* accessed as both */
} S_80091260_2;   /* arg0 in townDispatchActorInputActions */

/* Dispatch actor actions from input flags and position checks. */
void townDispatchActorInputActions(S_80091260_2 *actor, EntityRec *position, s32 context) {
    GameWork *input_state = &gameWork;
    s32 input_flags;
    s32 action_result;
    s32 tile_id;
    s16 height;
    s16 remaining_count;
    s32 *action_data;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(position);
    townMoveTheActorPerpendicularSelectedDirectionUnlessStepChangesSides(position);

    height = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(position, ((u8 *)&D_800FE488));
    if ((height - position->z.w.i) >= 4) {
        if (D_800CFCEF[0] == 0) {
            dungeonInitializeActionObject(actor, position, context);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(position, height, ((u8 *)&D_800FE488));
    }

    input_flags = ((s32)input_state->unk_010);
    if (input_flags & 0x10) {
        func_800942B0(actor, position, context);
        return;
    }

    if (input_flags & 0x40) {
        action_result = townSelectAnEligibleSourceEntryStoresPointerInDestination(actor, D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                func_8009451C(actor, position, context);
                return;
            } else {
                dungeonInitializeActionObjectWithCounter(actor, position, context);
                return;
            }
        } else if (testResidentBitmapBit(0xA4) != 0) {
            func_80094088(actor, position, context);
            return;
        }
        return;
    }

    action_data = D_800CFCB4;
    action_result = townSelectAnAvailableEntryMatchingDirectionReturnsStatus(action_data);
    if (action_result != 0) {
        if (action_result == -1) {
            townStoreTheValidSharedAngleInOffsetHex10(actor);
            townInitializeRecordAndSelectActiveData(actor, position, context);
            actor->unk_2C = 0;
            func_8008B158(action_data[4]);
            return;
        } else {
            func_800943B8(actor, position, context);
            return;
        }
        return;
    }

    input_flags = input_state->buttons;
    if (input_flags & 0x20) {
        if (actor->unk_16 == 1) {
            tile_id = townReadMapCellAtWorldPosition(position->x.w.i, position->y.w.i);
            if (townCheckMaskedValueInCurrentRange((u16)tile_id) != 0 &&position->z.v > 0) {
                func_80093FC8(actor, position, context);
                return;
            } else {
                func_80093E58(actor, position, context);
                return;
            }
        } else {
            townInitializeRandomizedObjectAction(actor, position, context);
            townStoreTheValidSharedAngleInOffsetHex10(actor);
            townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58(position);
            return;
        }
        return;
    }

    if (input_flags & 0xF000) {
        remaining_count = actor->unk_3E.u - 1;
        actor->unk_3E.s = remaining_count;
        townTriggerEventHex519IntervalMultiplesEnabled(remaining_count, 12);
        townStoreTheValidSharedAngleInOffsetHex10(actor);
        townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(position);
        townReduceObjectCoordinatesTowardDirectionDependentLimitsWithoutOvershooting(position);
        return;
    } else {
        townInitializeSceneActionRecord(actor, position, context);
    }
}
