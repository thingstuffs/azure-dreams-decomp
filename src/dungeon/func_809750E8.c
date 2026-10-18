#include "modules/dungeon_ovl_9950e8.h"

void apply_countdown_scaled_effect_intensity(void *record_data, void *unused, Rec_D_80082E80 *color_target) {
    s16 remaining_ticks;
    s32 intensity;

    intensity = (s32) (((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_98
        << 7) / (s16) ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_AC;
    color_target->unk_0C.at02_s8.v = (s8) intensity;
    color_target->unk_0C.at01_s8.v = (s8) intensity;
    color_target->unk_0C.at00_s8.v = (s8) intensity;
    func_800478B8(color_target);
    remaining_ticks = (u16) ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_98 - 1;
    ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_98 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_809750E8_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}
