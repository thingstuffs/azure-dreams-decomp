#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"

s32 testResidentBitmapBit();                         /* extern */
void func_8008B158();                         /* extern */
void townInitializeMotionAction();     /* extern */
M2C_UNK func_80094088();     /* extern */
void func_800942B0();     /* extern */
M2C_UNK dungeonInitializeActionObject();     /* extern */
void func_800943B8();     /* extern */
M2C_UNK dungeonInitializeActionObjectWithCounter();     /* extern */
M2C_UNK func_8009451C();     /* extern */
void townStoreTheValidSharedAngleInOffsetHex10();                      /* extern */
void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();                      /* extern */
s32 townSelectAnAvailableEntryMatchingDirectionReturnsStatus();            /* extern */
s32 townSelectAnEligibleSourceEntryStoresPointerInDestination();               /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      /* extern */
void townInitializeRecordAndSelectActiveData();     /* extern */
extern s32 D_800CFCB4;
extern M2C_UNK D_800CFCEF;


typedef struct S_80090A74_1 {
    u8 unk_00;
} S_80090A74_1;   /* &D_800CFCEF in townDispatchActorInteractionActions */

typedef struct S_80090A74_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80090A74_2;   /* temp_s4 in townDispatchActorInteractionActions */


typedef struct S_80090A74_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80090A74_4;   /* temp_s3 in townDispatchActorInteractionActions */

/* Update the actor and dispatch town actions from input and interaction state. */
void townDispatchActorInteractionActions(Rec_func_8009431C_arg0 *actor, EntityRec *record, s32 context) {
    s16 height;
    s32 action_result;
    s32 interaction_result;
    u8 *page_base;
    u8 *height_data;
    u8 *shared_data;
    GameWork *input_state = &gameWork;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(record);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(record);
    {
        void *height_record = record;

        height_data = ((u8 *)&D_800FE488);
        height = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(height_record, height_data);
    }
    if ((height - record->z.w.i) >= 4) {
        if (((S_80090A74_1 *)(&D_800CFCEF))->unk_00 == 0) {
            dungeonInitializeActionObject(actor, record, context);
            return;
        }
    } else if (((S_80090A74_1 *)(&D_800CFCEF))->unk_00 == 0) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(record, height, height_data);
    }
    if (((s32)input_state->unk_010) & 0x10) {
        func_800942B0(actor, record, context);
        return;
    }
    if (((s32)input_state->unk_010) & 0x40) {
        action_result = townSelectAnEligibleSourceEntryStoresPointerInDestination(actor, &D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                func_8009451C(actor, record, context);
                return;
            }
            dungeonInitializeActionObjectWithCounter(actor, record, context);
            return;
        }
        if (testResidentBitmapBit(0xA4) != 0) {
            func_80094088(actor, record, context);
            return;
        }
    } else {
        shared_data = (u8 *)&D_800CFCB4;
        interaction_result = townSelectAnAvailableEntryMatchingDirectionReturnsStatus(shared_data);
        if (interaction_result != 0) {
            if (interaction_result == -1) {
                townStoreTheValidSharedAngleInOffsetHex10(actor);
                townInitializeRecordAndSelectActiveData(actor, record, context);
                actor->unk_2C = 0;
                func_8008B158(((S_80090A74_4 *)shared_data)->unk_10);
                return;
            }
            func_800943B8(actor, record, context);
            return;
        }
        page_base = (u8 *)(u32)(input_state->buttons & 0xF000);
        if (page_base != 0) {
            townInitializeMotionAction(actor, record, context);
        }
    }
}
