#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"


extern void clear_slots_of_type(void *, s32);
struct ActorRecord;
extern s16 try_claim_dungeon_action_slot(struct ActorRecord *actor);

/* Reset action state and decrement the actor counter when the checks pass. */
void reset_action_and_decrement_actor_count(void *action_state, void *unused_1, void *unused_2, void *actor) {
    *(u8 *) ((u8 *) actor + 0x71) &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && (try_claim_dungeon_action_slot(actor) << 0x10) == 0 &&
        (try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
        if ((set_or_clear_actor_status_slot(actor, STATUS_NO_TILE_OCCUPANCY, 0) << 0x10) < 0) {
            *(u16 *) ((u8 *) actor + 0x46) &= 0x7FFF;
            return;
        }
        *(s32 *) ((u8 *) action_state + 0x8C) = 0;
        *((u8 *) action_state + 0x9A) = 0x18;
        *((u8 *) action_state + 0x9B) = 0;
        *(s16 *) ((u8 *) action_state + 0x96) = 0;
        *((u8 *) action_state + 0xB3) = 0;
        *((u8 *) action_state + 0xB1) = 0;
        *((u8 *) action_state + 0xB2) = 0;
        *(s32 *) ((u8 *) actor + 0x1C) &= 0xFFFBFFFF;
        *(u16 *) ((u8 *) action_state + 0x98) |= 8;
        clear_slots_of_type(actor, STATUS_POISON);
        advance_status_timers(actor);
        *((u8 *) actor + 0x6D) -= 1;
    }
}
