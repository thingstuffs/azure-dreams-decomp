#include "modules/dungeon_ovl_fa7000.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_actor_movement_to_tile();
extern s32 check_actor_floor_trap();

/* Select the bank actor callback when the resident checks succeed. */
void select_bank_resident_callback(BankActorState *state, s32 unused, SpriteFrameState *source, EntityRec *target) {
    if (update_actor_movement_to_tile() != 0) {
        reduce_actor_food_meter(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 16) > 0) {
            state->callback = update_bank_actor_state;
            if (g_dungeon_status.flags & 0x80) {
                state->unk_92 = -0x20;
            }
        }
    } else if (g_dungeon_status.flags & 0x80) {
        state->unk_92 = -0x20;
    }
}

