#include "shared/position_query.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"


typedef struct {
    void *callback;
    u8 pad04[4];
    u16 mode;
    u16 timer;
    u8 pad0C[4];
    u16 direction;
} State;

typedef struct {
    u8 pad00[10];
    s16 height;
    s32 x;
    s32 y;
    s32 value;
} Actor;

extern u8 D_800CFCEE;
extern s32 D_80100E20;
extern u8 D_800A5DF8;

extern s32 scaleRandomToUnsignedHalfwordLimit();
extern s32 runtimeEstimateVectorLength();
extern void SD_Call();
extern s32 townReadMapCellAtWorldPosition();
extern void townAddADirectionalStepVectorScaleDownExceedsLengthLimit();
extern void townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero();
extern void townAddHex20000SSignedOffsetHex14();
extern void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2();
extern s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();
extern void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();
extern void townSpawnDirectionalEffects();
extern s32 townComputeHeightBasedOffset();
extern s32 townCheckMaskedValueInCurrentRange();


/* Update actor movement, height, turning, and action state from input. */
void townUpdateActorMovementAndActions(State *state, Actor *actor) {
    GameWork *input;
    s32 speed;
    s16 height_limit;
    s32 direction;
    s32 world_value;
    s32 sound_period;

    input = &gameWork;
    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(actor);

    state->timer--;
    if ((s16)state->timer <= 0) {
        state->timer = scaleRandomToUnsignedHalfwordLimit(3) + 5;
        townSpawnDirectionalEffects(actor, (u16)scaleRandomToUnsignedHalfwordLimit(2) + 2);
    }

    direction = (((u16)input->view.viewAngle) + 0x800) & 0xFFF;
    *(u16 *)((u8 *)state + 0x10) = direction;

    if (((u32)input->buttons) & 0x20) {
        townAddADirectionalStepVectorScaleDownExceedsLengthLimit(direction, D_80100E20, actor);
        townSpawnDirectionalEffects(actor, (u16)scaleRandomToUnsignedHalfwordLimit(1));
    }

    if (((u32)input->buttons) & 0x10) {
        townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(actor);
        if ((((u32)input->buttons) & 0x30) == 0x20) {
            townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(actor);
        }
    } else {
        townMoveBothComponentsTowardZeroDirectionDependentStepsClampingZero(actor);
    }
    height_limit = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(actor, ((u8 *)&D_800FE488));
    if (actor->height >= height_limit) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(actor, height_limit, ((u8 *)&D_800FE488));
    } else if ((&D_800CFCEE)[1] != 0) {
        actor->value = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(actor);
    } else {
        townAddHex20000SSignedOffsetHex14(actor);
    }
    world_value = townReadMapCellAtWorldPosition(D_80083780.x.w.i, D_80083780.y.w.i);
    if (townCheckMaskedValueInCurrentRange((u16)world_value) != 0) {
        actor->value -= townComputeHeightBasedOffset(actor);
    }

    speed = runtimeEstimateVectorLength(actor->x, actor->y);
    if (D_80100E20 != 0) {
        {
            s32 speed_delta;
            speed_delta = D_80100E20 - speed;
            sound_period = (((speed_delta < 0 ? -speed_delta : speed_delta) * 7) / D_80100E20) + 2;
        }
        {
            u16 tick_count;
            tick_count = input->unk_004;
            if ((tick_count % sound_period) == 0) {
                SD_Call(0x60A);
            }
        }
    }

    if (speed == 0) {
        input->view.viewAngle = (((u16)input->view.viewAngle) + 8) & 0xFFF0;
    } else {
        if ((((u32)input->buttons) & 0x30) == 0x10) {
            speed = (D_80100E20 * 3) / 2;
        }
    }
    {
        s32 rounded_speed;
        rounded_speed = speed;
        if (speed < 0) {
            s32 rounding_bias;
            rounding_bias = 0xFFFF;
            rounded_speed = speed + rounding_bias;
        }
        speed = rounded_speed >> 16;
    }

    if ((*(u32 *)((u8 *)input + 8)) & 0x2000) {
        {
            s32 angle;
            angle = ((u16)input->view.viewAngle);
            angle = angle - 0x10;
            angle = angle - speed;
            input->view.viewAngle = angle;
        }
        townSpawnDirectionalEffects(actor, (u16)scaleRandomToUnsignedHalfwordLimit(1));
    }

    if ((*(u32 *)((u8 *)input + 8)) & 0x8000) {
        {
            s32 angle;
            angle = ((u16)input->view.viewAngle);
            angle = angle + 0x10;
            angle = angle + speed;
            input->view.viewAngle = angle;
        }
        townSpawnDirectionalEffects(actor, (u16)scaleRandomToUnsignedHalfwordLimit(1));
    }

    if ((((u32)input->unk_010) & 0x10) && (D_800CFCEE == 0)) {
        state->callback = &D_800A5DF8;
        state->timer = 8;
        state->mode = 1;
        return;
    }

    if (((u32)input->unk_010) & 0x100) {
        state->callback = &D_800A5DF8;
        state->timer = 8;
        state->mode = 0;
    }
}
