#define dungeonUpdateBankActorState dungeonUpdateObjectAnimationDispatchesActionAdjustsFacing
#define dungeonUpdateActorHopAndGrow func_800AB4A4
/* Relink of matched dungeon/func_80F89D44 at file 0xFA9D44; imports and data use paired retail relocations. */
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AB4A4(s32, s32, s32, s32 *);
/* Restore the bank actor callback after the resident state check succeeds. */
void func_801728B8(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800AB4A4(state, action, source, target) != 0) {
        state->callback = dungeonUpdateObjectAnimationDispatchesActionAdjustsFacing;
    }
}

