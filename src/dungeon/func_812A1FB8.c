#define update_spinning_actor_fall func_800AB280
#define update_bank_actor_state func_8014C514
/* Relink of matched dungeon/func_80F8A69C at file 0xFAA69C; imports and data use paired retail relocations. */
#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AB280();
/* Restore the bank actor callback after the resident state check succeeds. */
void func_8014E7B8(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (func_800AB280(state, action, source, target) != 0) {
        state->callback = func_8014C514;
    }
}

