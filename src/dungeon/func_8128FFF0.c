#define update_actor_fade_in func_800ABAEC
#define update_bank_actor_state update_object_animation_and_facing
/* Relink of matched dungeon/func_80F8A6D4 at file 0xFAA6D4; imports and data use paired retail relocations. */
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800ABAEC();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_801607F0(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800ABAEC(state, action, source, target) != 0) {
        state->callback = update_object_animation_and_facing;
    }
}

