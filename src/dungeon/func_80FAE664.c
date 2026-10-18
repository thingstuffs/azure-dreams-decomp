/* Relink of matched dungeon/func_80F8A664; every changed retail word is a paired relocation. */
#define update_bank_actor_state update_actor_action_and_facing
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 interpolate_actor_to_terrain_tile();
/* Restore the bank actor callback after the resident state check succeeds. */
void update_paired_actor_movement_and_tiles(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (interpolate_actor_to_terrain_tile(state, action, source, target) != 0) {
        state->callback = update_actor_action_and_facing;
    }
}

