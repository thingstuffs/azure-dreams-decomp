#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800C5D80_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C5D80_0;   /* arg1 in advance_effect_motion_and_fade */

typedef struct S_800C5D80_2 {
    u16 unk_00;
    u8 pad_02[0xC];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
} S_800C5D80_2;   /* arg0 in advance_effect_motion_and_fade; pointer addresses record offset 0x2 */

extern void func_800478B8();

/* Advance effect motion, fade its color, and mark it finished when its timer expires. */
void advance_effect_motion_and_fade(void *effect_data, S_800C5D80_0 *motion, SpriteFrameState *primitive) {
    s16 ticks_left;
    u8 brightness;

    motion->unk_08 += motion->unk_14;
    motion->unk_14 += 0x2000;
    func_800478B8(primitive);
    brightness = primitive->color.c.r
        - ((s32) primitive->color.c.r / (s16) ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_12);
    primitive->color.c.r = brightness;
    primitive->color.c.g = brightness;
    primitive->color.c.b = brightness;
    ticks_left = (u16) ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_12 - 1;
    ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_12 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        if (((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_0E == 0) {

            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        }
        ((S_800C5D80_2 *)((u8 *)effect_data - 0x2))->unk_00 = (u16) (((S_800C5D80_2 *)((u8 *)effect_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}

/* MECHANISM: Separate compound RMWs preserve retail's shared +0x14 load and v1 copy.
   A named D_80083460 base keeps +0xA as a displacement; the corrected u8 quotient
   expression restores the divide sequence, with cdk-G0 providing the retail schedule. */
