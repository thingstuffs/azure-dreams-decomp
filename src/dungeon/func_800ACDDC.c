#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"


extern s32 func_800A2BDC(void *arg0);
extern void func_800ACB98(void *entity, s32 unused, s32 status, void *event_state);
extern void func_800ACD74(void *object_state, s32 unused_context, s32 properties, void *status);

extern s16 D_800DCE68;


/* Updates actor state from pending entity flags when entity processing is allowed. */
void func_800B253C(Rec_func_800A9E70_arg0 *actor, s32 update_arg1, s32 update_arg2, EntityRec *entity) {
    void *active_entity;
    s32 entity_flags;
    s32 next_state;

    if ((entity->flags1C & 0x2000) || (entity->flags14 & 0x4000)) {
        if ((u32)(actor->unk_9A.as_u8 - 0x13) >= 2U) {
            if (entity->unk_6D == 0) {
                if (D_800DCE68 == 0) {
                    if ((func_800A2BDC(entity) << 0x10) != 0) {
                        return;
                    }
                } else {
                    active_entity = dungeonStatus.unk_0C;
                    if (active_entity != entity) {
                        if (!((((s32)dungeonStatus.unk_10) == 0) && (active_entity == 0) &&
                              (dungeonStatus.unk_08 == 0) &&
                              !(dungeonStatus.flags & 0x2008) &&
                              (entity->unk_43 == 0xFD))) {
                            return;
                        }
                        dungeonStatus.unk_0C = entity;
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
                        func_800ACB98(actor, update_arg1, update_arg2, entity);
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
                        func_800ACD74(actor, update_arg1, update_arg2, entity);
                        return;
                    }
                    actor->unk_9A.as_u8 = 0;
                    actor->unk_9B.as_u8 = 0;
                }
            }
        }
    }
}
