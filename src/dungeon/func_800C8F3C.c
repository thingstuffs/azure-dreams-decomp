#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/dungeon_floor.h"


extern s32 create_dual_grid_trap_effect(s32 center_x, s32 center_y, s16 unused_value, void *unused_data, s32 reverse_offset);

/* Return success if either global high flag is set, otherwise test the record lookup. */
s32 check_trap_record_or_global_override(void *record) {
    void *source_record;

    if (D_800E296C & 0xC0000000) {
        return 1;
    }
    source_record = *(void **)((s8 *)record - 0x14);
    return create_dual_grid_trap_effect(((u8 *)source_record)[0x24], ((u8 *)source_record)[0x25], *(s16 *)((s8 *)record + 0x88),
        record, 0) != 0;
}
