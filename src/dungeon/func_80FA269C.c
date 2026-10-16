/* Relink of matched dungeon/func_80F8A69C; every changed retail word is a paired relocation. */
#define dungeonUpdateBankActorState dungeonUpdateActorBehaviorVariantE
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 dungeonUpdateSpinningActorFall();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_8015BE9C(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (dungeonUpdateSpinningActorFall(state, action, source, target) != 0) {
        state->callback = dungeonUpdateActorBehaviorVariantE;
    }
}

