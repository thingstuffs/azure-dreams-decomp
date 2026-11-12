#include "common.h"
#include "sdk/libgpu.h"
#include "dungeon/monster/mandara.h"
#include "shared/object_node.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x8];
    u16 field_08;
} ColorPtrFieldView_80FB4C24;


   /* the 0x2 bytes before arg0 in blend_animation_palette_and_complete, addressed as arg0[-1] */


typedef struct S_80174424_1 {
    u8 pad_00[0x208];
    s16 unk_208;
    u8 pad_20A[0x6];
    s16 unk_210;
    u8 pad_212[0x6];
    s16 unk_218;
} S_80174424_1;   /* out in blend_animation_palette_and_complete */

/* Blend palette colors for the current animation frame and flag completion. */
void blend_animation_palette_and_complete(MandaraEntryEffectBody *effect)
{
    s16 buffer[270];
    s16 *buffer_base;
    register ColorPtrFieldView_80FB4C24 *color_ptr;
    register s32 channel_pair;
    register s32 blend_frame;
    register s32 blend_scale;
    s32 palette_row;
    register s32 palette_index;
    register s32 sample_count;
    s32 column;
    register s32 sample_index;
    register s32 sample_offset;
    register u16 packed_color;
    register u16 result_color;
    register u16 next_frame;
    register u16 frame;
    register s32 *flags_page;

    next_frame = effect->frame + 1;
    effect->frame = next_frame;
    if (effect->duration.s < (s16)next_frame) {
        flags_page = (s32 *)(u32)0x80080000;
        NODE_HEADER(effect)->flags = NODE_HEADER(effect)->flags | 0x8000;
        flags_page[0x14A0 / 4] |= 0x8000;
        return;
    }

    flags_page = (s32 *)(u32)0x80080000;

    StoreImage((s8 *)effect + 0xA0, &buffer[4]);
    buffer[0] = 0x340;
    buffer[2] = 0x80;
    buffer[3] = 2;
    if (effect->mode == 0) {
        buffer[1] = 0x100;
        blend_frame = effect->frame;
    } else {
        buffer[1] = 0x102;
        column = effect->duration.s;
        frame = effect->frame;
        blend_frame = (u16)column - frame;
    }
    DrawSync(0);

    palette_row = 12;
    buffer_base = buffer;
    blend_scale = blend_frame;
    blend_scale = (s16)blend_scale;
    column = 15;
    do {
        palette_index = (palette_row << 4) + 15;
        do {
            sample_count = 0;
            channel_pair = (s32)buffer_base;
            sample_index = palette_index;
            sample_offset = sample_index << 1;
            sample_index += 0x30;
            packed_color = *(u16 *)(u32)(sample_offset + (u32)(s8 *)buffer_base + 8);
unpack_pair:
            sample_count++;
            ((S_80174424_1 *)channel_pair)->unk_208 = packed_color & 0x1F;
            ((S_80174424_1 *)channel_pair)->unk_210 = ((packed_color << 16) >> 21) & 0x1F;
            ((S_80174424_1 *)channel_pair)->unk_218 = ((packed_color << 16) >> 26) & 0x1F;
            channel_pair += 2;
            if (sample_count < 2) {
                sample_offset = sample_index << 1;
                sample_index += 0x30;
                packed_color = *(u16 *)(u32)(sample_offset + (u32)(s8 *)buffer_base + 8);
                goto unpack_pair;
            }

            channel_pair = effect->duration.s;
            channel_pair = ((buffer[0x105] - buffer[0x104]) * blend_scale) / channel_pair;
            buffer[0x104] = (u16)buffer[0x104] + channel_pair;
            buffer[0x108] = (u16)buffer[0x108] +
                ((buffer[0x109] - buffer[0x108]) * blend_scale) / effect->duration.s;
            {
                s32 blue_step;
                s32 pixel_offset;

                blue_step = ((buffer[0x10D] - buffer[0x10C]) * blend_scale) /
                    effect->duration.s;
                pixel_offset = palette_index << 1;
                palette_index--;
                buffer[0x10C] = (u16)buffer[0x10C] + blue_step;
                color_ptr = (ColorPtrFieldView_80FB4C24 *)(u32)(pixel_offset + (u32)(s8 *)buffer_base);
                sample_index = color_ptr->field_08;
                result_color = (u16)sample_index;
                column--;
                result_color &= 0x8000;
                color_ptr->field_08 = result_color;
                {
                    s16 red;
                    s32 green;
                    s32 blue;

                    blue = (u16)buffer[0x10C];
                    green = (u16)buffer[0x108];
                    red = (u16)buffer[0x104];
                    blue <<= 10;
                    green <<= 5;
                    blue += green;
                    red += blue;
                    result_color += red;
                    color_ptr->field_08 = result_color;
                }
            }
        } while (column >= 0);
        palette_row -= 4;
        column = 15;
    } while (palette_row >= 0);

    LoadImage(buffer, &buffer[4]);
    DrawSync(0);
}
