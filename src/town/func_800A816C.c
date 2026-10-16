#include "shared/position_query.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "m2c_compat.h"

typedef struct S_800A58CC_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A58CC_0;   /* (void *) shared_s0 in townUpdateObjectViewTransition */

typedef struct S_800A58CC_2 {
    void * unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800A58CC_2;   /* arg0 in townUpdateObjectViewTransition */


s32 townReadMapCellAtWorldPosition();                        /* extern */
s16 townStepAngle12Toward();               /* extern */
void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();                      /* extern */
void townAddHex20000SSignedOffsetHex14();                 /* extern */
void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2();                 /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      /* extern */
s32 townComputeHeightBasedOffset();                          /* extern */
s32 townCheckMaskedValueInCurrentRange();                             /* extern */
extern s32 D_800A5A98;
extern u8 D_800D0000[];
extern int abs(int);

/* Updates the object and interpolates town angles before advancing the state. */
void townUpdateObjectViewTransition(S_800A58CC_2 *state_arg, void *object) {
    s16 threshold;
    s32 pitch_step;
    s16 yaw;
    s32 object_ref;
    s32 target_yaw;
    s32 yaw_delta;
    s32 pitch;
    u16 ticks;
    GameWork *town;
    EntityRec *coords;

         /* MATCH: Order the s2 parameter copy before the s0 copy. */
    object_ref = (s32) object;
    town = &gameWork;
    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile((void *) object_ref);
    threshold = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated((void *) object_ref, &D_800FE488);
    if (((S_800A58CC_0 *)((void *) object_ref))->unk_0A >= threshold) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown((void *) object_ref, threshold, &D_800FE488);
    } else {
        if (D_800D0000[-0x311] != 0) {
            ((S_800A58CC_0 *)((void *) object_ref))->unk_14 = 0;
            townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2((void *) object_ref);
        } else {
            townAddHex20000SSignedOffsetHex14((void *) object_ref);
        }
    }
    coords = &D_80083780;
    if (townCheckMaskedValueInCurrentRange(townReadMapCellAtWorldPosition(coords->x.w.i, coords->y.w.i) & 0xFFFF) != 0) {
        pitch_step = ((S_800A58CC_0 *)((void *) object_ref))->unk_14 - townComputeHeightBasedOffset((void *) object_ref);
        ((S_800A58CC_0 *)((void *) object_ref))->unk_14 = pitch_step;
    }
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero((void *) object_ref);
    townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero((void *) object_ref);
    target_yaw = (state_arg->unk_10 - 0x800) & 0xFFF;
    yaw = townStepAngle12Toward(town->view.viewAngle, target_yaw, 0x80);
    town->view.viewAngle = yaw;
    yaw_delta = abs((yaw & 0xFFF) - target_yaw);
    if (yaw_delta < 0x80) {
        town->view.viewAngle = target_yaw;
    }
    ticks = state_arg->unk_0A.s - 1;
    state_arg->unk_0A.s = ticks;
    {
        s32 shifted_ticks;
        s32 ticks_left;
        shifted_ticks = (s32) ticks << 16;
        ticks_left = shifted_ticks >> 16;
        pitch_step = -0x2B0;
        if (ticks_left <= 0) {
            state_arg->unk_0A.u = 0;
        }
        pitch = ticks_left > 0
            ? (pitch_step -= town->view.unk_0AC, pitch_step /= ticks_left,
               ((u16)town->view.unk_0AC) + pitch_step)
        : -0x2B0;
        town->view.unk_0AC = pitch;
    }
    if ((state_arg->unk_0A.u == 0) && (town->view.viewAngle == target_yaw)) {
        state_arg->unk_0A.u = 0;
        state_arg->unk_00 = &D_800A5A98;
    }
}
