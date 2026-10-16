#define dungeonUpdateActorFadeIn func_800ABAEC
#define dungeonUpdateBankActorState func_80158514
/* Relink of matched dungeon/func_80F8A6D4 at file 0xFAA6D4; imports and data use paired retail relocations. */
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800ABAEC();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_8015A7F0(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800ABAEC(state, action, source, target) != 0) {
        state->callback = func_80158514;
    }
}

