#include "dungeon/monster/hikewne/apply_countdown_scaled_effect_intensity.h"
#include "shared/sprite_frame_state.h"

void apply_countdown_scaled_effect_intensity(void *record_data, void *unused, SpriteFrameState *color_target) {
    s16 remaining_ticks;
    s32 intensity;

    intensity = (s32) (((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_98
        << 7) / (s16) ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_AC;
    color_target->color.c.b = (s8) intensity;
    color_target->color.c.g = (s8) intensity;
    color_target->color.c.r = (s8) intensity;
    func_800478B8(color_target);
    remaining_ticks = (u16) ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_98 - 1;
    ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_98 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_809750E8_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}
