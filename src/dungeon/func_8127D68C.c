#define update_bank_actor_state update_object_animation_dispatches_action_adjusts_facing
#define update_actor_hop_and_grow func_800AAA74
/* Relink of matched dungeon/func_80F89D44 at file 0xFA9D44; imports and data use paired retail relocations. */
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AAA74();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_80171E8C(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800AAA74(state, action, source, target) != 0) {
        state->callback = update_object_animation_dispatches_action_adjusts_facing;
    }
}

