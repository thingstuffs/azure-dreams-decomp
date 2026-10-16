/* Relink of matched dungeon/func_80F8A664; every changed retail word is a paired relocation. */
#define dungeonUpdateBankActorState updateActorActionAndTargetState
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 dungeonInterpolateActorToTerrainTile();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_80155E64(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (dungeonInterpolateActorToTerrainTile(state, action, source, target) != 0) {
        state->callback = updateActorActionAndTargetState;
    }
}

