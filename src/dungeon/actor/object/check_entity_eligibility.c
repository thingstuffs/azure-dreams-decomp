#include "common.h"

extern s32 get_entity_effect_value(void *entity, s32 effect_id);
extern s32 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);

/* Checks entity eligibility using status flags and the linked entity's position. */
s32 check_entity_eligibility(void *entity) {
    u16 tile_flags;
    void *linked_entity;
    s32 check_result;

    if ((*(u8 *)((u8 *)entity + 0x28) + *(s16 *)((u8 *)entity + 0x64)) > 0) {
        if (*(s32 *)((u8 *)entity + 0x1C) & 0x2000) {
            linked_entity = *(void **)((u8 *)entity - 0x14);
            get_offset_map_cell_value_and_flags(*(u8 *)((u8 *)linked_entity + 0x24) - 1,
                          *(u8 *)((u8 *)linked_entity + 0x25), 0, &tile_flags);
            if (tile_flags & 2) {
                return 0;
            }
        }
        if (!(*(s32 *)((u8 *)entity + 0x1C) & 0x290000)) {
            check_result = get_entity_effect_value(entity, 0x1B) << 16;
            return check_result == 0;
        }
        return 0;
    }
    return 0;
}
