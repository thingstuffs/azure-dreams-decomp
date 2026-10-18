/* Relink of matched dungeon/func_80F8A664; every changed retail word is a paired relocation. */
#define update_bank_actor_state func_8015F138
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 interpolate_actor_to_terrain_tile();
/* Restore the bank actor callback after the resident state check succeeds. */
void update_paired_actor_movement_tile_placement_animations_restored_flags(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (interpolate_actor_to_terrain_tile(state, action, source, target) != 0) {
        state->callback = func_8015F138;
    }
}

