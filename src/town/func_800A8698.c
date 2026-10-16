#include "shared/position_query.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "m2c_compat.h"

typedef struct S_800A5DF8_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A5DF8_0;   /* var_s0 in townUpdateActorEffectTransition */

typedef struct S_800A5DF8_1 {
    u8 unk_00;
} S_800A5DF8_1;   /* &D_800CFCEF in townUpdateActorEffectTransition */

typedef struct S_800A5DF8_4 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5DF8_4;   /* var_s2 in townUpdateActorEffectTransition */


s32 townReadMapCellAtWorldPosition();                        /* extern */
s16 townStepAngle12Toward();           /* extern */
void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();                      /* extern */
void townAddHex20000SSignedOffsetHex14();                 /* extern */
void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2();                 /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      /* extern */
s32 townComputeHeightBasedOffset();                          /* extern */
void townInitializeEffectAndAdjustValue();                         /* extern */
s32 townCheckMaskedValueInCurrentRange();                             /* extern */
extern u8 D_800CFCEF;
extern u8 D_800A5FDC[];

/* Updates the actor effect and eases scene values before advancing the state. */
void townUpdateActorEffectTransition(S_800A5DF8_4 *state, S_800A5DF8_0 *actor, s32 context) {
    s16 threshold;
    s32 offset_step;
    s16 angle;
    s32 next_offset;
    u16 ticks_left;
    register GameWork *scene_state;
    register u8 *effect_data;

    scene_state = &gameWork;
    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(actor);
    effect_data = ((u8 *)&D_800FE488);
    threshold = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(actor, effect_data);
    if (actor->unk_0A >= threshold) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(actor, threshold, effect_data);
    } else if (((S_800A5DF8_1 *)(&D_800CFCEF))->unk_00 != 0) {
        actor->unk_14 = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(actor);
    } else {
        townAddHex20000SSignedOffsetHex14(actor);
    }

    if (townCheckMaskedValueInCurrentRange(townReadMapCellAtWorldPosition(D_80083780.x.w.i, D_80083780.y.w.i) & 0xFFFF) != 0) {
        offset_step = actor->unk_14 - townComputeHeightBasedOffset(actor);
        actor->unk_14 = offset_step;
    }
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(actor);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(actor);
    angle = townStepAngle12Toward(scene_state->view.viewAngle, 0, 0x80);
    scene_state->view.viewAngle = angle;
    if ((angle & 0xFFF) < 0x80) {
        scene_state->view.viewAngle = 0;
    }
    ticks_left = state->unk_0A.s - 1;
    state->unk_0A.s = ticks_left;
    {
        s32 shifted_ticks;
        s32 ticks;
        shifted_ticks = (s32) ticks_left << 16;
        ticks = shifted_ticks >> 16;
        offset_step = -0x280;
        if (ticks <= 0) {
            state->unk_0A.u = 0;
        }
        next_offset = ticks > 0
            ? (offset_step -= scene_state->view.unk_0AC, offset_step /= ticks,
               ((u16)scene_state->view.unk_0AC) + offset_step)
        : -0x280;
        scene_state->view.unk_0AC = next_offset;
    }
    if ((state->unk_0A.u == 0) &&
        (scene_state->view.viewAngle == 0)) {
        if (state->unk_08 != 0) {
            townInitializeEffectAndAdjustValue(state, actor, context);
        } else {
            state->unk_0A.u = 0;
            state->unk_00 = D_800A5FDC;
        }
    }

    return;
}
