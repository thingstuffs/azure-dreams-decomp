#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AC5C8();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_80173E9C(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800AC5C8(state, action, source, target) != 0) {
        state->callback = func_80171138;
    }
}

