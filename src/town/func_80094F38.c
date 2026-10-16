#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"


#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void townInitializeSceneActionRecord();
extern void func_800942B0();
extern M2C_UNK dungeonInitializeActionObject();
extern M2C_UNK func_8009451C();
extern void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();
extern s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();
extern void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();

extern void *D_800CFCC4[3];
extern u8 D_800CFCEF[9];

typedef struct S_80092698_2 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_80092698_2;   /* D_800CFCC4[0] in townUpdateActorWithInteractionState */

/* Update the entity and dispatch its next action from the sampled value, countdown, and global state. */
void townUpdateActorWithInteractionState(Rec_func_80094268_arg0 *controller, EntityRec *entity, s32 context) {
    s16 sampled_value;
    u16 countdown;
    GameWork *state = &gameWork;
    u8 *samples;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(entity);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(entity);
    samples = ((u8 *)&D_800FE488);
    sampled_value = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(entity, samples);
    if ((sampled_value - entity->z.w.i) >= 4) {
        if (D_800CFCEF[0] == 0) {
            dungeonInitializeActionObject(controller, entity, context);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(entity, sampled_value, samples);
    }
    countdown = controller->unk_0A.as_u16 - 1;
    controller->unk_0A.as_u16 = countdown;
    if ((s16)countdown < 0) {
        if (D_800CFCC4[0] != NULL) {
            if (((S_80092698_2 *)(D_800CFCC4[0]))->unk_14 == 2) {
                townInitializeSceneActionRecord(controller, entity, context);
                return;
            }
        }
        func_8009451C(controller, entity, context);
        return;
    }
    if (((s32)state->unk_010) & 0x10) {
        func_800942B0(controller, entity, context);
    }
}
