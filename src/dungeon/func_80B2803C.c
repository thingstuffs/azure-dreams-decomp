/* Relink of matched dungeon/func_80F8A600; every changed retail word is a paired relocation. */
#define func_80171138 func_80164E54
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AD9B4();
extern s32 func_800AC010();
/* Select the bank actor callback when the resident checks succeed. */
void func_8016783C(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((func_800AC010(state, action, source, target) != 0) && ((func_800AD9B4(source, target) << 0x10) > 0)) {
        state->callback = func_80164E54;
    }
}

