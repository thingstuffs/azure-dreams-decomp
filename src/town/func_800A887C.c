#include "shared/position_query.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"

typedef struct S_800A5FDC_0 {
    s32 unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5FDC_0;   /* state in townUpdateTownMovementAndActions */


extern s32 scaleRandomToUnsignedHalfwordLimit();
extern s32 runtimeEstimateVectorLength();
extern void SD_Call();
extern s32 townReadMapCellAtWorldPosition();
extern s16 townInputAngleWithOffset();
extern void townStoreTheValidSharedAngleInOffsetHex10();
extern void townAddADirectionalStepVectorScaleDownExceedsLengthLimit();
extern void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();
extern void townAddHex20000SSignedOffsetHex14();
extern void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2();
extern s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();
extern void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();
extern void townSpawnDirectionalEffects();
extern void townInitializeEffectAndAdjustValue();
extern s32 townComputeHeightBasedOffset();
extern s32 townCheckMaskedValueInCurrentRange();
extern int abs(int);

extern s32 D_800A58CC;
extern u8 D_800CFCEE[];
extern s32 D_80100E20[];


/* Updates town movement, terrain response, facing, and action state from input. */
void townUpdateTownMovementAndActions(u8 *state, EntityRec *table, void *action_context)
{
    u8 *context;
    GameWork *globals;
    s32 random_choice;
    s32 tile_id;
    s32 speed;
    s32 speed_delta;
    s32 sound_interval;
    s32 input_flags;
    s32 turn_angle;
    s16 direction;
    s16 ground_height;

    context = action_context;
    globals = &gameWork;
    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(table);

    ((S_800A5FDC_0 *)state)->unk_0A.s--;
    if (((S_800A5FDC_0 *)state)->unk_0A.u <= 0) {
        ((S_800A5FDC_0 *)state)->unk_0A.s = scaleRandomToUnsignedHalfwordLimit(3) + 5;
        random_choice = scaleRandomToUnsignedHalfwordLimit(2);
        townSpawnDirectionalEffects(table, (u16)random_choice + 2);
    }

    input_flags = globals->buttons;
    if (input_flags & 0xF000) {
        townStoreTheValidSharedAngleInOffsetHex10(state);
        direction = townInputAngleWithOffset(globals->buttons,
                                  globals->view.viewAngle);
        if (direction != -1) {
            townAddADirectionalStepVectorScaleDownExceedsLengthLimit(direction, D_80100E20[0], table);
        }
        random_choice = scaleRandomToUnsignedHalfwordLimit(1);
        townSpawnDirectionalEffects(table, (u16)random_choice);
    } else {
        if (input_flags & 0x10) {
            townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(table);
        }
        townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(table);
    }

    ground_height = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(table, ((u8 *)&D_800FE488));
    if (table->z.w.i >= ground_height) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(table, ground_height, ((u8 *)&D_800FE488));
    } else if (D_800CFCEE[1] != 0) {
        table->flags14 = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(table);
    } else {
        townAddHex20000SSignedOffsetHex14(table);
    }
    tile_id = townReadMapCellAtWorldPosition(D_80083780.x.w.i,
                            D_80083780.y.w.i);
    if (townCheckMaskedValueInCurrentRange((u16)tile_id) != 0) {
        table->flags14 -= townComputeHeightBasedOffset(table);
    }

    speed = runtimeEstimateVectorLength(table->unk_0C,
                          table->unk_10);
    if (D_80100E20[0] != 0) {
        speed_delta = abs(D_80100E20[0] - speed);
        sound_interval = (s32)((u32)speed_delta * 7U) / D_80100E20[0];
        if ((globals->unk_004 % (sound_interval + 2)) == 0) {
            SD_Call(0x60A);
        }
    }

    if (speed == 0) {
        globals->view.viewAngle =
            (((u16)globals->view.viewAngle) + 8) & 0xFFF0;
    }

    speed /= 0x10000;
    if (globals->buttons & 4) {
        turn_angle = ((u16)globals->view.viewAngle) + 0x10;
        globals->view.viewAngle = turn_angle + speed;
    }
    if (globals->buttons & 8) {
        turn_angle = ((u16)globals->view.viewAngle) - 0x10;
        globals->view.viewAngle = turn_angle - speed;
    }

    if ((((s32)globals->unk_010) & 0x10) &&
        (D_800CFCEE[0] == 0)) {
        townInitializeEffectAndAdjustValue(state, table, context);
        return;
    }

    if (((s32)globals->unk_010) & 0x100) {
        ((S_800A5FDC_0 *)state)->unk_00 = (s32)&D_800A58CC;
        ((S_800A5FDC_0 *)state)->unk_0A.u = 8;
    }
    return;
}
