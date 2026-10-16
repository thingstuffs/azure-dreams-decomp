#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_800942B0();        /* extern */
void dungeonInitializeActionObject();        /* extern */
void townStoreTheValidSharedAngleInOffsetHex10();                         /* extern */
void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();                      /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      /* extern */
extern M2C_UNK D_800CFCEF;


typedef struct S_80091000_1 {
    u8 unk_00;
} S_80091000_1;   /* &D_800CFCEF in townUpdateActorGroundAndInput */

typedef struct S_80091000_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80091000_2;   /* state in townUpdateActorGroundAndInput */

/* Update the actor against ground height, then dispatch input actions. */
void townUpdateActorGroundAndInput(s32 controller, EntityRec *actor, s32 context) {
    s16 ground_height;
    GameWork *input_state = &gameWork;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(actor);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(actor);
    ground_height = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(actor, &D_800FE488);
    if ((ground_height - actor->z.w.i) >= 4) {
        if (((S_80091000_1 *)(&D_800CFCEF))->unk_00 == 0) {
            dungeonInitializeActionObject(controller, actor, context);
            return;
        }
    } else {
        if (((S_80091000_1 *)(&D_800CFCEF))->unk_00 == 0) {
            townComputeAndClampsVectorBasedAdjustmentUpdatesTown(actor, ground_height, &D_800FE488);
        }
    }
    if (((s32)input_state->unk_010) & 0x10) {
        func_800942B0(controller, actor, context);
        return;
    }
    if (input_state->buttons & 0xF000) {
        townStoreTheValidSharedAngleInOffsetHex10(controller);
    }
}
