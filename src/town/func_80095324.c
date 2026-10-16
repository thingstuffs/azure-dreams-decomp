#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

void func_80035208();
void func_8008B158();
M2C_UNK func_8009451C();
void func_800945B8();
M2C_UNK func_80094660();
M2C_UNK func_800946A0();
void townTriggerEventHex519IntervalMultiplesEnabled();
void townCallTheHandlerSelectsNonzeroEntry();
void townStoreTheValidSharedAngleInOffsetHex10();
void townHandleAdjustVectorTowardSelectedAngleLimitMagnitude();
void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();
s32 townSelectAnAvailableEntryMatchingDirectionReturnsStatus();
s32 townGetStatusActiveEntryMatchingDirection();
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();
M2C_UNK func_800988C8();
s32 townIsUnk18N12Unk1ABetweenN37N41();
s32 func_800A9D74();

extern M2C_UNK D_80093B00;
extern M2C_UNK D_8009B828;
extern M2C_UNK D_8009B8E8;
extern u8 D_8009B9BC[];
extern s32 D_800CFCB4;
extern u8 D_800CFCEF;
extern M2C_UNK D_800D0128;
extern s32 *D_800FE5D8;

typedef struct S_80092A84_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80092A84_1;   /* state in townUpdateActorPositionAndInteraction */


typedef struct S_80092A84_3 {
    u8 pad_00[0x50];
    void * unk_50;
} S_80092A84_3;   /* entity in townUpdateActorPositionAndInteraction */

typedef struct S_80092A84_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80092A84_4;   /* base in townUpdateActorPositionAndInteraction */

/* Updates the actor's position and dispatches town actions from input and interaction state. */
void townUpdateActorPositionAndInteraction(Rec_func_80094268_arg0 *actor, EntityRec *body, s32 context) {
    GameWork *input_state;
    u8 *position_data;
    s32 *interaction_ctrl;
    s16 position;
    s32 input_flags;
    s32 action_result;
    S_80092A84_3 *entity;
    void *handler;
    S_80092A84_4 *interaction_state;

    input_state = &gameWork;
    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(body);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(body);

    position_data = ((u8 *)&D_800FE488);
    position = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(body, position_data);
    if ((position - body->z.w.i) >= 4) {
        if (D_800CFCEF == 0) {
            func_80094660(actor, body, context);
            return;
        }
    } else if (D_800CFCEF == 0) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(body, position, position_data);
    }

    input_flags = ((s32)input_state->unk_010);
    if (input_flags & 0x10) {
        func_800945B8(actor, body, context);
        return;
    }
    if (input_flags & 0x40) {
        func_800946A0(actor, body, context);
        return;
    }

    interaction_ctrl = &D_800CFCB4;
    if ((townGetStatusActiveEntryMatchingDirection(interaction_ctrl) == -1) && (townIsUnk18N12Unk1ABetweenN37N41() == 0)) {
        townSelectAnAvailableEntryMatchingDirectionReturnsStatus(interaction_ctrl);
        townStoreTheValidSharedAngleInOffsetHex10(actor);
        townCallTheHandlerSelectsNonzeroEntry(&D_800D0128, actor, context);
        func_800988C8(actor, body, context);

        entity = actor->unk_2C;
        handler = entity->unk_50;
        if ((handler != &D_8009B828) && (handler != &D_8009B8E8)) {
            if (handler != D_8009B9BC) {
                actor->unk_2C = 0;
            }
        }

        interaction_state = &D_800CFCB4;
        action_result = func_800A9D74(interaction_state->unk_10, actor->unk_2C);
        if (action_result != 0) {
            func_80035208(action_result);
        } else {
            func_8008B158(interaction_state->unk_10);
        }
        D_800FE5D8 = (s32 *)&D_80093B00;
        return;
    }

    if (input_state->buttons & 0xF000) {
        position = actor->unk_3E.as_u16 - 1;
        actor->unk_3E.as_u16 = position;
        townTriggerEventHex519IntervalMultiplesEnabled(position, 0xC);
        townStoreTheValidSharedAngleInOffsetHex10(actor);
        townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(body);
        return;
    }

    func_8009451C(actor, body, context);
}
