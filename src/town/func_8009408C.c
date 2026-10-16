#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) \
(*(type_ptr)((s8 *)(expr) + (offset)))

s32 scaleRandomToUnsignedHalfwordLimit();
M2C_UNK func_80094048();
M2C_UNK dungeonInitializeActionObject();
void townTriggerEventHex519IntervalMultiplesEnabled();
void townStoreTheValidSharedAngleInOffsetHex10();
void townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58();
void townMoveTheActorPerpendicularSelectedDirectionUnlessStepChangesSides();
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();
void townSpawnRadialEffectObjects();
extern u8 D_800CFCEF[];
extern u8 D_800D043C[];
extern s32 D_800FE4E0;


typedef struct S_800917EC_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800917EC_2;   /* temp_s0 in townUpdateActorWithPeriodicEffect */

/* Updates actor height, emits periodic effects, and handles the active state. */
void townUpdateActorWithPeriodicEffect(Rec_func_80094268_arg0 *actor, EntityRec *position, s32 context) {
    GameWork *state = &gameWork;
    s16 surface_height;
    s16 action_timer;
    s32 *effect_pos;
    s32 state_flags;
    u16 effect_timer;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(position);
    townMoveTheActorPerpendicularSelectedDirectionUnlessStepChangesSides(position);
    surface_height = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(position, ((u8 *)&D_800FE488));
    if ((surface_height - position->z.w.i) >= 4) {
        if (D_800CFCEF[0] == 0) {
            dungeonInitializeActionObject(actor, position, context);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(position, surface_height, ((u8 *)&D_800FE488));
    }
    effect_timer = actor->unk_0A.as_u16 - 1;
    actor->unk_0A.as_u16 = effect_timer;
    if ((effect_timer << 0x10) <= 0) {
        actor->unk_0A.as_u16 = (u16)(scaleRandomToUnsignedHalfwordLimit(4) + 3);
        D_800FE4E0 = position->x.v;
        effect_pos = &D_800FE4E0;
        ((S_800917EC_2 *)effect_pos)->unk_04 = position->y.v;
        ((S_800917EC_2 *)effect_pos)->unk_08 =
            position->z.v + 0xFFB00000;
        townSpawnRadialEffectObjects(effect_pos, D_800D043C,
                      (scaleRandomToUnsignedHalfwordLimit(2) & 0xFFFF) + 2);
    }
    state_flags = state->buttons;
    if ((state_flags & 0xF000) && (state_flags & 0x20)) {
        action_timer = actor->unk_3E.as_u16 - 1;
        actor->unk_3E.as_u16 = (u16)action_timer;
        townTriggerEventHex519IntervalMultiplesEnabled(action_timer, 8);
        townStoreTheValidSharedAngleInOffsetHex10(actor);
        townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58(position);
        return;
    }
    func_80094048(actor, position, context);
}
