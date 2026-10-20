#include "dungeon/level/generate.h"

void mark_random_eligible_region_tiles(floor_generate_isolated_8028A328_S_8001D328_0 *region, s32 setup_arg1) {
    s32 random_bits;
    u16 tile_flags;
    s16 count;
    s32 entry_index;
    s32 x_offset;
    s32 y_offset;
    u8 *state;
    u8 *state_prefix;
    floor_generate_isolated_8028A328_S_8001D328_1 *coords;
    s32 sum;
    u8 *state_base;
    u8 *prefix_base;
    s32 state_offset;

    random_bits = generate_random_value();
    sum = ((region->unk_06 * region->unk_04) >> 6) + (random_bits & 7) + 4;
    count = sum;
    if ((s16)sum >= 0x3D) {
        count = 0x3C;
    }
    entry_index = count;
    if (entry_index >= 0) {
        state_base = D_800E3549;
        prefix_base = state_base - 1;
        state_offset = entry_index * 4;
        state_prefix = state_offset + prefix_base;
        state = state_offset + state_base;
        do {
            coords = (floor_generate_isolated_8028A328_S_8001D328_1 *)((u8 *)D_800E36C8 + entry_index * 0xC);
            x_offset = random_dungeon_range_16(0, (region->unk_04 - 1) & 0xFFFF) & 0xFFFF;
            y_offset = random_dungeon_range_16(0, (region->unk_06 - 1) & 0xFFFF) & 0xFFFF;
            coords->unk_00 = region->unk_00 + x_offset;
            coords->unk_01 = region->unk_02 + y_offset;
            if (((get_offset_map_cell_value_and_flags(coords->unk_00 - 1, coords->unk_01, 0, &tile_flags) << 16) == 0) || !(tile_flags & 0xFF20)) {
                cycle_map_cell_flags(coords->unk_00, coords->unk_01, 0x800);
                select_floor_item_with_special_overrides(state, state_prefix, 0, 1);
            }
            state_prefix -= 4;
            state -= 4;
            entry_index--;
        } while (entry_index >= 0);
    }
}
