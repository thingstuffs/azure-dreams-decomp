#include "modules/dungeon_resource12_slot0.h"

s32 func_801720B4(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)dungeonRelinkEntityAndClearHighFlag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        func_8017162C(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R12_801720B4_S_80172628_0 *)entity)->unk_9A = 0xE;
        func_800A9A0C(entity);
        result = 0;
        return result;
    case 2:
        func_8017162C(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((R12_801720B4_S_80172628_0 *)entity)->unk_71 = (u8) (((R12_801720B4_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((func_800A2BDC(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((R12_801720B4_S_80172628_0 *)entity)->unk_71 = (u8) (((R12_801720B4_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((dungeonStatus.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((R12_801720B4_S_80172628_0 *)entity)->unk_46 = (u16) (((R12_801720B4_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}
