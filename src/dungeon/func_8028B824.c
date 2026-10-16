#include "modules/dungeon_floor_spawns.h"

void initRandomFloorItemParameters(void *entity_data) {
    u8 *entity = entity_data;
    s16 output_flags;
    s16 combined_flags;
    s16 output_value;
    s32 minus_128;
    s32 adjusted_value;
    u8 case_value;

    output_flags = 0;
    case_value = ((floor_spawns_isolated_8028B824_S_8001E824_0 *)entity)->unk_01;
    output_value = output_flags;
    switch (case_value) {
    case 4:
        output_value = 1;
        if (((floor_spawns_isolated_8028B824_S_8001E824_0 *)entity)->unk_00 != 0x11) {
            output_value = (func_800A6D30() & 7) | 4;
        }
        output_flags = -0x80;
        break;
    case 15:
        if (((floor_spawns_isolated_8028B824_S_8001E824_0 *)entity)->unk_00 == 9) {
            output_flags |= 0x40;
        }
    case 17:
        if (!(func_800A6D30() & 3)) {
            adjusted_value = (func_800A6D30() & 3) - 1;
            output_value = adjusted_value;
            if (adjusted_value < 0) {
                output_flags |= 0x40;
            }
        }
    case 16:
        minus_128 = -0x80;
        combined_flags = output_flags | minus_128;
        output_flags = combined_flags;
        if (func_800A6D30() & 7) {
            break;
        }
        output_value = -1;
        output_flags = combined_flags | 0x40;
        break;
    case 18:
        output_value = ((u32)(func_800A6D30() & 0xFFFF) % 40U) + 0x3C;
        break;
    case 1:
    default:
        break;
    }
    ((floor_spawns_isolated_8028B824_S_8001E824_0 *)entity)->unk_02 = output_value;
    ((floor_spawns_isolated_8028B824_S_8001E824_0 *)entity)->unk_03 = output_flags;
}
