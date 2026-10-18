#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_80170224_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x3E];
    u16 unk_B0;
} S_80170224_0;   /* base in update_boss_action_result */


extern s16 relink_entity_and_clear_high_flag(void *context, void *position, void *entity, s16 near_range, s16 far_range, s32 state_out_addr);
extern void advance_boss_actor_movement_state(void *, s32, s32, void *);
extern void update_actor_status_and_food(void *);
extern s16 has_pending_dungeon_activity(void *);

/* Updates an entity's state and flags according to its action result. */
s32 update_boss_action_result(Rec_func_800A9E70_arg0 *entity, s32 target_x, s32 target_y, s16 force_action) {
    void *entity_data = entity;
    s16 action_result;

    if (((S_80170224_0 *)entity_data)->unk_B0 != 0) {
        action_result = relink_entity_and_clear_high_flag(target_x, target_y, entity_data, 3, 6, (u8 *)entity_data + 0x9C);
        if (action_result < 0) {
            return 0;
        }
        if (force_action != 0) {
            advance_boss_actor_movement_state(entity_data, target_x, target_y, entity_data);
            return 0;
        }
    } else {
        action_result = 0;
    }

    switch (action_result) {
    case 0:
        entity->unk_9A.as_u8 = 14;
        update_actor_status_and_food(entity_data);
        return 0;

    case 2:
        advance_boss_actor_movement_state(entity, target_x, target_y, entity_data);
        return 0;

    case 1:
        ((S_80170224_0 *)entity_data)->unk_71 &= 0x7F;
        if (has_pending_dungeon_activity(entity_data) != 0) {
            ((S_80170224_0 *)entity_data)->unk_46 &= 0x7FFF;
            return 0;
        }
                        /* fallthrough */
    default:
        ((S_80170224_0 *)entity_data)->unk_71 &= 0x7F;
        if (!(g_dungeon_status.flags & 8)) {
            return 1;
        }
        ((S_80170224_0 *)entity_data)->unk_46 &= 0x7FFF;
        return 0;
    }
}
