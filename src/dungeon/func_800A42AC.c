#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 advance_status_timers();                      /* extern */
void refresh_actor_proximity_state();                      /* extern */
void reduce_actor_food_meter();             /* extern */


/* Process an entity's pending updates and clear its update flags. */
void update_actor_status_and_food(EntityRec *entity) {
    s8 updates_left;
    u8 entity_type;

    entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2800)) {
        if (entity->unk_6D != 0) {
            do {
                if (!(*(u16 *)0x80013714 & 8)) {
                    if (!(entity->flags1C & 8) && ((entity_type = (*(u8 *)((u8 *)&entity->unk_10 + 3)), ((entity_type
                        < 0x2FU) != 0)) || (entity_type == 0x39))) {
                        reduce_actor_food_meter(entity, 4);
                    }
                    advance_status_timers(entity);
                }
                updates_left = (u8) entity->unk_6D - 1;
                entity->unk_6D = updates_left;
            } while ((updates_left << 0x18) != 0);
        }
        entity->unk_46 = (u16) (entity->unk_46 & 0x7FFF);
        refresh_actor_proximity_state(entity);
    }
}
