#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800CFCC4.h"

void func_80035208();                         /* extern */
void func_8008B158();                         /* extern */
void townSetDefaultSceneDataPointer();     /* extern */
void func_8009455C();     /* extern */
void func_800945B8();     /* extern */
M2C_UNK func_80094660();     /* extern */
M2C_UNK func_800946A0();     /* extern */
M2C_UNK func_80094774();     /* extern */
s32 townRunTheActionSequenceContextUnlessFlagHexA5Set();                          /* extern */
void townStoreTheValidSharedAngleInOffsetHex10();                      /* extern */
void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();                      /* extern */
void townRunTheThreeUpdateRoutinesContext();                      /* extern */
s32 townSelectAnAvailableEntryMatchingDirectionReturnsStatus();                   /* extern */
s32 townGetStatusActiveEntryMatchingDirection();                       /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      /* extern */
M2C_UNK func_800988C8();     /* extern */
void townClearEntityRecordFields();                      /* extern */
s32 townIsUnk18N12Unk1ABetweenN37N41();                                /* extern */
s32 func_800A9D74();                     /* extern */
extern M2C_UNK D_80093B00;
extern M2C_UNK D_8009B828;
extern M2C_UNK D_8009B8E8;
extern M2C_UNK D_8009B9BC;
extern M2C_UNK D_800CFCB4;
extern void *D_800CFCC4;
extern u8 D_800CFCEF[];
extern s32 D_800FE518[];
extern s32 *D_800FE5D8;


typedef struct S_800927EC_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800927EC_1;   /* state in townUpdateActorMovementAndInteraction */


typedef struct S_800927EC_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800927EC_4;

typedef struct S_800927EC_5 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800927EC_5;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_2C in townUpdateActorMovementAndInteraction */

/* Update the actor and dispatch town movement and interaction input. */
void townUpdateActorMovementAndInteraction(void *actor, EntityRec *position, s32 context) {
    GameWork *input = &gameWork;
    void *interaction;
    s16 ground_height;
    s32 interaction_result;
    s32 target_handler;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(position);
    townStoreTheValidSharedAngleInOffsetHex10(actor);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(position);
    ground_height = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(position, &D_800FE488);
    if ((ground_height - position->z.w.i) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094660(actor, position, context);
            return;
        }
    } else {
        if (D_800CFCEF[0] == 0) {
            townComputeAndClampsVectorBasedAdjustmentUpdatesTown(position, ground_height, &D_800FE488);
        }
    }
    if (((s32)input->unk_010) & 0x10) {
        func_800945B8(actor, position, context);
        return;
    }
    if (((s32)input->unk_010) & 0x80) {
        if ((D_800CFCC4 != NULL) && (((Rec_D_800CFCC4 *)D_800CFCC4)->unk_14 == 4)) {
            townRunTheThreeUpdateRoutinesContext(position);
            func_80094774(actor, position, context);
            D_800FE518[0] = 1;
            return;
        }
        townClearEntityRecordFields(position);
        townRunTheThreeUpdateRoutinesContext(position);
        if (townRunTheActionSequenceContextUnlessFlagHexA5Set(actor - 0x20) != 0) {
            townSetDefaultSceneDataPointer(actor, position, context);
            D_800FE5D8 = &D_80093B00;
            return;
        }
    } else {
        if (((s32)input->unk_010) & 0x40) {
            func_800946A0(actor, position, context);
            return;
        }
        if ((townGetStatusActiveEntryMatchingDirection(&D_800CFCB4) == -1) && (townIsUnk18N12Unk1ABetweenN37N41() == 0)) {
            townSelectAnAvailableEntryMatchingDirectionReturnsStatus(&D_800CFCB4);
            townStoreTheValidSharedAngleInOffsetHex10(actor);
            func_800988C8(actor, position, context);
            target_handler = ((S_800927EC_5 *)(((Rec_func_80094268_arg0 *)actor)->unk_2C))->unk_50;
            if ((target_handler != &D_8009B828) && (target_handler != &D_8009B8E8)) {
                if (target_handler != &D_8009B9BC) {
                    ((Rec_func_80094268_arg0 *)actor)->unk_2C = NULL;
                }
            }
            interaction = &D_800CFCB4;
            interaction_result = func_800A9D74(((S_800927EC_4 *)interaction)->unk_10,
                ((Rec_func_80094268_arg0 *)actor)->unk_2C);
            if (interaction_result != 0) {
                func_80035208(interaction_result);
            } else {
                func_8008B158(((S_800927EC_4 *)interaction)->unk_10);
            }
            D_800FE5D8 = &D_80093B00;
            return;
        }
        if (input->buttons & 0xF000) {
            func_8009455C(actor, position, context);
        }
    }
}
