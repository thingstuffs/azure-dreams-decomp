/* Relink of matched dungeon/func_80F8A6D4; every changed retail word is a paired relocation. */
#define func_80171138 func_80152EE4
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800ACE34();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_80156580(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800ACE34(state, action, source, target) != 0) {
        state->callback = func_80152EE4;
    }
}

