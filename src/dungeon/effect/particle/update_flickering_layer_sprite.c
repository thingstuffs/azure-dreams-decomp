#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80167540_0 {
    u16 unk_00;
    u8 pad_02[0x18];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80167540_0;   /* arg0 in update_flickering_layer_sprite; pointer addresses record offset 0x2 */

/* cfail-repair: tf7-phase1-cache-v3 */
s32 rand();                   /* extern */
s16 func_80167088();                         /* extern */

/* Scale effect channels by remaining lifetime, randomize flags, and mark expiration. */
void update_flickering_layer_sprite(void *effect_data, void *unused, SpriteFrameState *effect) {
    s16 selected_channel;
    s32 channel_1_scale;
    s32 channel_2_scale;
    s32 channel_0_scale;

    selected_channel = func_80167088(3);
    channel_2_scale = 0x20;
    channel_1_scale = 0x20;
    ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1E = selected_channel;
    channel_0_scale = 0x20;
    if (selected_channel == 0) {
        channel_0_scale = 0x50;
    }
    if (selected_channel == 1) {
        channel_1_scale = 0x50;
    }
    if (selected_channel == 2) {
        channel_2_scale = 0x50;
    }
    effect->color.c.r = (s8) ((s32) (channel_0_scale * ((S_80167540_0 *)((u8 *)effect_data
        - 0x2))->unk_1A) / (s16) ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1C);
    effect->color.c.g = (s8) ((s32) (channel_1_scale * ((S_80167540_0 *)((u8 *)effect_data
        - 0x2))->unk_1A) / (s16) ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1C);
    effect->color.c.b = (s8) ((s32) (channel_2_scale * ((S_80167540_0 *)((u8 *)effect_data
        - 0x2))->unk_1A) / (s16) ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1C);
    ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1A = (s16) ((u16) ((S_80167540_0 *)((u8 *)effect_data
        - 0x2))->unk_1A - 1);
    if (rand() & 1) {
        effect->flags = (u16) (effect->flags | 1);
    } else {
        effect->flags = (u16) (effect->flags & 0xFFFE);
    }
    if (rand() & 1) {
        effect->flags = (u16) (effect->flags | 2);
    } else {
        effect->flags = (u16) (effect->flags & 0xFFFD);
    }
    func_800478B8(effect);
    if (((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_1A <= 0) {
        ((S_80167540_0 *)((u8 *)effect_data - 0x2))->unk_00 = (u16) (((S_80167540_0 *)((u8 *)effect_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}
