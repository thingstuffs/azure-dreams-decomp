#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"


extern s32 has_pending_dungeon_activity(void *entity);
extern void begin_actor_flagged_action(void *entity, s32 unused, s32 status, void *event_state);
extern void initialize_actor_object_action(void *object_state, s32 unused_context, s32 properties, void *status);

extern s16 D_800DCE68;


/* Updates actor state from pending entity flags when entity processing is allowed. */
void update_pending_entity_action(Rec_func_800A9E70_arg0 *actor, s32 update_arg1, s32 update_arg2, EntityRec *entity) {
    void *active_entity;
    s32 entity_flags;
    s32 next_state;

    if ((entity->flags1C & 0x2000) || (entity->flags14 & 0x4000)) {
        if ((u32)(actor->unk_9A.as_u8 - 0x13) >= 2U) {
            if (entity->unk_6D == 0) {
                if (D_800DCE68 == 0) {
                    if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
                        return;
                    }
                } else {
                    active_entity = g_dungeon_status.active_actor;
                    if (active_entity != entity) {
                        if (!((((s32)g_dungeon_status.pending_display_owner) == 0) && (active_entity == 0) &&
                              (g_dungeon_status.activity_counts.parts.pending_movement_count == 0) &&
                              !(g_dungeon_status.flags & 0x2008) &&
                              (entity->unk_43 == 0xFD))) {
                            return;
                        }
                        g_dungeon_status.active_actor = entity;
                    }
                    if (entity->unk_43 != 0xFD) {
                        return;
                    }
                }
                if (entity->flags1C & 0x400000) {
                    actor->unk_8C = 0;
                    entity_flags = entity->flags14;
                    entity->flags1C &= 0xFFBFFFFF;
                    if (entity_flags & 0x20000000) {
                        entity->flags14 = entity_flags | 0x400000;
                        actor->unk_AD = 0;
                        begin_actor_flagged_action(actor, update_arg1, update_arg2, entity);
                        return;
                    }
                    entity->flags14 = entity_flags & 0xFFBFFFFF;
                    next_state = entity_flags & 0x4000;
                    if (!next_state) {
                        next_state = 2;
                    } else {
                        next_state = 1;
                    }
                    actor->unk_9A.as_u8 = next_state;
                    actor->unk_9B.as_u8 = 0;
                } else if (entity->flags1C & 0x02000000) {
                    actor->unk_8C = 0;
                    entity->unk_71 = 0;
                    entity->flags1C &= 0xFDFFFFFF;
                    if (entity->flags14 & 0x20000000) {
                        initialize_actor_object_action(actor, update_arg1, update_arg2, entity);
                        return;
                    }
                    actor->unk_9A.as_u8 = 0;
                    actor->unk_9B.as_u8 = 0;
                }
            }
        }
    }
}
