#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 check_actor_floor_trap();
extern s32 update_linked_actor_motion();
/* Select the bank actor callback when the resident checks succeed. */
void select_bank_actor_callback(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((update_linked_actor_motion(state, action, source, target) != 0) && ((check_actor_floor_trap(source, target) << 0x10) > 0)) {
        state->callback = update_bank_actor_state;
    }
}

