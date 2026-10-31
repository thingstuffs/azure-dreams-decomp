#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"


extern s16 try_claim_dungeon_action_slot(ActorRecord *actor);

/* Resets actor state and updates entity flags when global and entity checks allow it. */
void complete_actor_action(ActorRecord *actor, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *entity) {
    s32 *global_page;
    s32 global_flags;
    u16 actor_flags;

    entity->movement_queue_state &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) &&
        (try_claim_dungeon_action_slot(entity) << 16) == 0 &&
        (try_claim_dungeon_action_slot(entity) << 16) == 0) {
        actor->unk_8C.run = 0;
        actor->action_id.s = 0x17;
        actor->action_phase.s = 0;
        actor->action_timer.s = 0;
        actor->unk_B0.bytes[3] = 0;
        actor->unk_B0.bytes[1] = 0;
        actor->unk_B0.bytes[2] = 0;
        entity->flags1C &= 0xFFFBFFFF;
        global_page = (s32 *)0x800E0000;
        global_flags = global_page[0x296C / 4];
        actor_flags = actor->action_state_flags;
        global_flags |= 0x40;
        actor_flags |= 8;
        global_page[0x296C / 4] = global_flags;
        actor->action_state_flags = actor_flags;
        advance_status_timers(entity);
        *((u8 *)entity + 0x6D) -= 1;
    }
}
