#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/dungeon_floor.h"

extern s32 dungeonCreateDualGridTrapEffect(s32 center_x, s32 center_y, s16 unused_value, void *unused_data, s32 reverse_offset);

/* Checks the entity at its linked coordinates unless a global override is set. */
s32 dungeonCheckLinkedEntityOrGlobalOverride(void *entity) {
    void *position_record;

    if (D_800E296C & 0xC0000000) {
        return 1;
    }
    position_record = *(void **)((u8 *)entity - 0x14);
    return dungeonCreateDualGridTrapEffect(
        *(u8 *)((u8 *)position_record + 0x24),
        *(u8 *)((u8 *)position_record + 0x25),
        *(s16 *)((u8 *)entity + 0x88),
        entity,
        1) != 0;
}
