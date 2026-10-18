#include "modules/dungeon_ovl_ccb000.h"

s32 func_8015A298(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        func_80159810(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((CL_CCB000_80172298_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_food(entity);
        result = 0;
        return result;
    case 2:
        func_80159810(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((CL_CCB000_80172298_S_80172628_0 *)entity)->unk_71 = (u8) (((CL_CCB000_80172298_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((CL_CCB000_80172298_S_80172628_0 *)entity)->unk_71 = (u8) (((CL_CCB000_80172298_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((CL_CCB000_80172298_S_80172628_0 *)entity)->unk_46 = (u16) (((CL_CCB000_80172298_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}
