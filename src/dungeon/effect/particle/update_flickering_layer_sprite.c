#include "slus.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libc.h"
#include "dungeon/effect/particle.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80167088(s32 limit);                         /* extern */

/* Scale effect channels by remaining lifetime, randomize flags, and mark expiration. */
void update_flickering_layer_sprite(LayeredSpritePulseBody *effect_data, void *unused, SpriteFrameState *effect) {
    s16 selected_channel;
    s32 channel_1_scale;
    s32 channel_2_scale;
    s32 channel_0_scale;

    selected_channel = func_80167088(3);
    channel_2_scale = 0x20;
    channel_1_scale = 0x20;
    effect_data->unk_1C = selected_channel;
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
    effect->color.c.r = (s8) ((s32) (channel_0_scale * effect_data->unk_18) / (s16) effect_data->unk_1A);
    effect->color.c.g = (s8) ((s32) (channel_1_scale * effect_data->unk_18) / (s16) effect_data->unk_1A);
    effect->color.c.b = (s8) ((s32) (channel_2_scale * effect_data->unk_18) / (s16) effect_data->unk_1A);
    effect_data->unk_18 = (s16) ((u16) effect_data->unk_18 - 1);
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
    advance_sprite_animation_and_textures(effect);
    if (effect_data->unk_18 <= 0) {
        *((u16 *)((u8 *)effect_data - 0x2)) |= 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
