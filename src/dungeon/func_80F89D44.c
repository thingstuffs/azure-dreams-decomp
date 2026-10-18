#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_actor_hop_and_grow();
/* Restore the bank actor callback after the resident state check succeeds. */
void restore_bank_actor_callback_a(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (update_actor_hop_and_grow(state, action, source, target) != 0) {
        state->callback = update_bank_actor_state;
    }
}

