#define update_bank_actor_state func_80158514
#define interpolate_actor_to_terrain_tile func_800AB138
/* Relink of matched dungeon/func_80F8A664 at file 0xFAA664; imports and data use paired retail relocations. */
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AB138();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_8015A780(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800AB138(state, action, source, target) != 0) {
        state->callback = func_80158514;
    }
}

