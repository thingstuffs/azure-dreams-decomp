/* Relink of matched dungeon/func_80CEB818; every changed retail word is a paired relocation. */
#define dungeonUpdateStagedTargetMotion func_8016F018
#define dungeonUpdateActorBehavior D_8016C4BC
/* Relink of matched dungeon/func_80F89D44; every changed retail word is a paired relocation. */
#define dungeonUpdateBankActorState dungeonUpdateActorBehavior
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 dungeonUpdateActorHopAndGrow();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_8016F018(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (dungeonUpdateActorHopAndGrow(state, action, source, target) != 0) {
        state->callback = dungeonUpdateActorBehavior;
    }
}

