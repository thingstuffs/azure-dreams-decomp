#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 dungeonInterpolateActorToTerrainTile();
/* Restore the bank actor callback after the resident state check succeeds. */
void dungeonRestoreBankActorCallbackB(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (dungeonInterpolateActorToTerrainTile(state, action, source, target) != 0) {
        state->callback = dungeonUpdateBankActorState;
    }
}

