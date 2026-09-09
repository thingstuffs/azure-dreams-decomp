#include "common.h"

typedef struct S_80174424_0_pre {
    u16 unk_00;
} S_80174424_0_pre;   /* the 0x2 bytes before arg0 in func_80174424, addressed as arg0[-1] */

typedef struct S_80174424_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    u8 pad_A0[0x8];
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
} S_80174424_0;   /* arg0 in func_80174424 */

typedef struct S_80174424_1 {
    u8 pad_00[0x208];
    s16 unk_208;
    u8 pad_20A[0x6];
    s16 unk_210;
    u8 pad_212[0x6];
    s16 unk_218;
} S_80174424_1;   /* out in func_80174424 */



extern void func_80067014(s32 arg0);
extern void func_800672D8(void *arg0, void *arg1);
extern void func_8006733C(void *arg0, void *arg1);

/* Blend palette colors for the current animation frame and flag completion. */
void func_80174424(void *effect)
{
    s16 buffer[270];
    register s16 *buffer_base ASM_REG("$9");
    register s16 *color_ptr;
    register s16 *channel_pair;
    register s16 blend_frame;
    register s32 blend_scale;
    s32 palette_row;
    register s32 palette_index;
    register s32 sample_count;
    register s32 column;
    register s32 sample_index;
    register s32 sample_offset;
    register u16 packed_color;
    register u16 result_color;
    register u16 next_frame;
    register u16 duration;
    register u16 frame;
    register s32 *flags_page;

    next_frame = ((S_80174424_0 *)effect)->unk_96 + 1;
    ((S_80174424_0 *)effect)->unk_96 = next_frame;
    if (((S_80174424_0 *)effect)->unk_A8.s < (s16)next_frame) {
        flags_page = (s32 *)(u32)0x80080000;
        ((S_80174424_0_pre *)effect)[-1].unk_00 = ((S_80174424_0_pre *)effect)[-1].unk_00 | 0x8000;
        flags_page[0x14A0 / 4] |= 0x8000;
        return;
    }

    flags_page = (s32 *)(u32)0x80080000;

    func_8006733C((s8 *)effect + 0xA0, &buffer[4]);
    buffer[0] = 0x340;
    buffer[2] = 0x80;
    buffer[3] = 2;
    if (((S_80174424_0 *)effect)->unk_9E == 0) {
        buffer[1] = 0x100;
        blend_frame = ((S_80174424_0 *)effect)->unk_96;
    } else {
        buffer[1] = 0x102;
        duration = ((S_80174424_0 *)effect)->unk_A8.u;
        frame = ((S_80174424_0 *)effect)->unk_96;
        blend_frame = duration - frame;
    }
    func_80067014(0);

    palette_row = 12;
    buffer_base = buffer;
    ASM_KEEP(buffer_base);
    blend_scale = blend_frame;
    ASM_KEEP(blend_scale);
    column = 15;
    do {
        palette_index = (palette_row << 4) + 15;
blend_color:
        sample_count = 0;
        channel_pair = buffer_base;
        sample_index = palette_index;
unpack_pair:
        sample_offset = sample_index << 1;
        sample_index += 0x30;
        packed_color = *(u16 *)(u32)(sample_offset + (u32)(s8 *)buffer_base + 8);
        sample_count++;
        ((S_80174424_1 *)channel_pair)->unk_208 = packed_color & 0x1F;
        ((S_80174424_1 *)channel_pair)->unk_210 = ((packed_color << 16) >> 21) & 0x1F;
        ((S_80174424_1 *)channel_pair)->unk_218 = ((packed_color << 16) >> 26) & 0x1F;
        channel_pair++;
        if (sample_count < 2) {
            goto unpack_pair;
        }

        buffer[0x104] = (u16)buffer[0x104] +
            ((buffer[0x105] - buffer[0x104]) * blend_scale) / ((S_80174424_0 *)effect)->unk_A8.s;
        buffer[0x108] = (u16)buffer[0x108] +
            ((buffer[0x109] - buffer[0x108]) * blend_scale) / ((S_80174424_0 *)effect)->unk_A8.s;
        {
            s32 blue_step;
            s32 pixel_offset;

            blue_step = ((buffer[0x10D] - buffer[0x10C]) * blend_scale) /
                ((S_80174424_0 *)effect)->unk_A8.s;
            pixel_offset = palette_index << 1;
            palette_index--;
            buffer[0x10C] = (u16)buffer[0x10C] + blue_step;
            color_ptr = (s16 *)(u32)(pixel_offset + (u32)(s8 *)buffer_base);
            result_color = *(u16 *)((s8 *)color_ptr + 8);
            column--;
            result_color &= 0x8000;
            *(u16 *)((s8 *)color_ptr + 8) = result_color;
            {
                s32 red;
                register s32 green ASM_REG("$4");
                s32 blue;

                blue = (u16)buffer[0x10C];
                green = (u16)buffer[0x108];
                red = (u16)buffer[0x104];
                blue <<= 10;
                green <<= 5;
                blue += green;
                red += blue;
                result_color += red;
                *(u16 *)((s8 *)color_ptr + 8) = result_color;
            }
        }
        if (column >= 0) {
            goto blend_color;
        }
        palette_row -= 4;
        column = 15;
    } while (palette_row >= 0);

    func_800672D8(buffer, &buffer[4]);
    func_80067014(0);
}
