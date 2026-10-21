#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

s32 has_pending_dungeon_activity();                          /* extern */
void update_actor_status_and_mp();                      /* extern */
s32 relink_entity_and_clear_high_flag(); /* extern */
void select_movement_direction_and_advance(); /* extern */

typedef struct S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} S_80172628_0;   /* hold_arg0 in update_entity_state_from_query */

/* Update entity state and flags according to the state query result. */
s32 update_entity_state_from_query(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        select_movement_direction_and_advance(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        select_movement_direction_and_advance(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((S_80172628_0 *)entity)->unk_71 = (u8) (((S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((S_80172628_0 *)entity)->unk_71 = (u8) (((S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((S_80172628_0 *)entity)->unk_46 = (u16) (((S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}
