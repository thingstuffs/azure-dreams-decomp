#include "shared/entity.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"


extern s16 try_claim_dungeon_action_slot(ActorRecord *actor);

/* Resets actor state and updates entity flags when global and entity checks allow it. */
void complete_actor_action(void *actor, ObjectPosition *unused_1, void *unused_2, void *entity) {
    s32 *global_page;
    s32 global_flags;
    u16 actor_flags;

    *(u8 *)((u8 *)entity + 0x71) &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) &&
        (try_claim_dungeon_action_slot(entity) << 16) == 0 &&
        (try_claim_dungeon_action_slot(entity) << 16) == 0) {
        *(s32 *)((u8 *)actor + 0x8C) = 0;
        *(u8 *)((u8 *)actor + 0x9A) = 0x17;
        *(u8 *)((u8 *)actor + 0x9B) = 0;
        *(s16 *)((u8 *)actor + 0x96) = 0;
        *(u8 *)((u8 *)actor + 0xB3) = 0;
        *(u8 *)((u8 *)actor + 0xB1) = 0;
        *(u8 *)((u8 *)actor + 0xB2) = 0;
        *(s32 *)((u8 *)entity + 0x1C) &= 0xFFFBFFFF;
        global_page = (s32 *)0x800E0000;
        global_flags = global_page[0x296C / 4];
        actor_flags = *(u16 *)((u8 *)actor + 0x98);
        global_flags |= 0x40;
        actor_flags |= 8;
        global_page[0x296C / 4] = global_flags;
        *(u16 *)((u8 *)actor + 0x98) = actor_flags;
        advance_status_timers(entity);
        *(u8 *)((u8 *)entity + 0x6D) -= 1;
    }
}
