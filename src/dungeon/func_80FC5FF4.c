/* Relink of matched dungeon/func_80F89D44; every changed retail word is a paired relocation. */
#define dungeonUpdateBankActorState func_8015EF6C
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800ABDBC();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_801617F4(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800ABDBC(state, action, source, target) != 0) {
        state->callback = func_8015EF6C;
    }
}

