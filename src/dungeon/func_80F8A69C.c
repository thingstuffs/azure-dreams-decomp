#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_spinning_actor_fall();
/* Restore the bank actor callback after the resident state check succeeds. */
void restore_bank_actor_callback_c(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (update_spinning_actor_fall(state, action, source, target) != 0) {
        state->callback = update_bank_actor_state;
    }
}

