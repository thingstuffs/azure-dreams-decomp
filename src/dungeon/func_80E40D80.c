/* Relink of matched dungeon/func_80F8A6D4; every changed retail word is a paired relocation. */
#define dungeonUpdateBankActorState func_8016AEE4
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800ACE34();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_8016E580(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800ACE34(state, action, source, target) != 0) {
        state->callback = func_8016AEE4;
    }
}

