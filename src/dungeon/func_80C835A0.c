/* Relink of matched dungeon/func_80F88C30; every changed retail word is a paired relocation. */
#define dungeonUpdateBankActorState func_80159650
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AD9B4();
extern s32 func_800AB378();
/* Select the bank actor callback when the resident checks succeed. */
void func_8015ADA0(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((func_800AB378(state, action, source, target) != 0) && ((func_800AD9B4(source, target) << 0x10) > 0)) {
        state->callback = func_80159650;
    }
}

