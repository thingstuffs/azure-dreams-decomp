#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8016A8E8_0 {
    u16 unk_00;
    u8 pad_02[0x96];
    s16 unk_98;
    u8 pad_9A[0x12];
    s16 unk_AC;
} S_8016A8E8_0;   /* arg0 in update_lifetime_output_components; pointer addresses record offset 0x2 */

/* Updates three output components from the remaining lifetime and flags expiry. */
void update_lifetime_output_components(void *record_data, void *unused, SpriteFrameState *output) {
    s16 ticks_left;
    s32 fade_level;

    fade_level = (s32) (((S_8016A8E8_0 *)((u8 *)record_data - 0x2))->unk_98
        << 7) / (s16) ((S_8016A8E8_0 *)((u8 *)record_data - 0x2))->unk_AC;
    output->color.c.b = (s8) fade_level;
    output->color.c.g = (s8) fade_level;
    output->color.c.r = (s8) fade_level;
    func_800478B8(output);
    ticks_left = (u16) ((S_8016A8E8_0 *)((u8 *)record_data - 0x2))->unk_98 - 1;
    ((S_8016A8E8_0 *)((u8 *)record_data - 0x2))->unk_98 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_8016A8E8_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_8016A8E8_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}
