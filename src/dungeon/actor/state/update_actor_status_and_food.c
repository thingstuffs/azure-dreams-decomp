#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 advance_status_timers();                      /* extern */
void refresh_actor_proximity_state();                      /* extern */
void spend_actor_mp();             /* extern */


/* Process an entity's pending updates and clear its update flags. */
void update_actor_status_and_mp(ActorRecord *entity) {
    s8 updates_left;
    u8 entity_type;

    entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2800)) {
        if (entity->pending_turn_updates != 0) {
            do {
                if (!(*(u16 *)0x80013714 & 8)) {
                    if (!(entity->flags1C & 8) && ((entity_type = (*(u8 *)((u8 *)&entity->unk_10 + 3)), ((entity_type
                        < 0x2FU) != 0)) || (entity_type == 0x39))) {
                        spend_actor_mp(entity, 4);
                    }
                    advance_status_timers(entity);
                }
                updates_left = (u8) entity->pending_turn_updates - 1;
                entity->pending_turn_updates = updates_left;
            } while ((updates_left << 0x18) != 0);
        }
        entity->action_flags = (u16) (entity->action_flags & 0x7FFF);
        refresh_actor_proximity_state(entity);
    }
}
