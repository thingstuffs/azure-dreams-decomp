#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801588E8_0 {
    u16 unk_00;
    u8 pad_02[0x96];
    s16 unk_98;
    u8 pad_9A[0x12];
    s16 unk_AC;
} S_801588E8_0;   /* arg0 in apply_countdown_scaled_color_intensity; pointer addresses record offset 0x2 */

/* Apply countdown-scaled intensity, decrement the timer, and flag completion at zero. */
void apply_countdown_scaled_color_intensity(void *record_data, void *unused, SpriteFrameState *color) {
    s16 ticks_left;
    s32 intensity;

    intensity = (s32) (((S_801588E8_0 *)((u8 *)record_data - 0x2))->unk_98
        << 7) / (s16) ((S_801588E8_0 *)((u8 *)record_data - 0x2))->unk_AC;
    color->color.c.b = (s8) intensity;
    color->color.c.g = (s8) intensity;
    color->color.c.r = (s8) intensity;
    advance_sprite_animation_and_textures(color);
    ticks_left = (u16) ((S_801588E8_0 *)((u8 *)record_data - 0x2))->unk_98 - 1;
    ((S_801588E8_0 *)((u8 *)record_data - 0x2))->unk_98 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_801588E8_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_801588E8_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
