#include "common.h"

extern s32 DrawSync(s32 mode);
extern void func_8003F80C(void *data, s32 vram, s32 palette, s32 flags);

/* D_8007162C (0x8007162C) is addressed as a literal page + offset pair:
 * gcc 2.6.3 has no TARGET_SPLIT_ADDRESSES, so `&D_8007162C` can only reach
 * the assembler as ONE atomic `la` macro and its lui/addiu halves can never
 * be separated by the two stack-argument loads retail puts between them. */
extern u8 D_8007162C[]; /* 0x8007162C -- referenced as a literal above */

/* Builds and uploads a palette blending three RGB colors. */
void func_8004E6F4(s32 palette_slot, u8 *rgb_start, u8 *rgb_mid, u8 *rgb_end, s32 blend_row, s32 semitrans_end)
{
    register s32 semitrans_limit ASM_REG("$24") = semitrans_end;   /* MATCH pin: slus-diff */
    s16 colors[16];
    s32 color_index;
    s32 start_weight;
    s32 red_end;
    s32 red_start;
    s32 green_end;
    s32 green_start, blue_end;
    register s32 blue_start ASM_REG("$17");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 packed_color;
    s32 channel_sum;
    register s32 saved_s0 ASM_REG("$16");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    u32 table_page;
    s32 weight_scale;
    register u8 *blend_table ASM_REG("$2");   /* MATCH pin: slus-diff */
    u8 *weights;

    ASM_USE_NV(saved_s0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    color_index = 1;
    colors[0] = 0;
    weight_scale = 4;
    table_page = 0x80070000;
    ASM_KEEP_NV(table_page);   /* MATCH pin: slus-diff */
    blend_table = (u8 *)(table_page + 0x162C);
    weights = (u8 *)(blend_row * 8 + (u32)blend_table);
    ASM_USE_NV(weights);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    do {
        packed_color = (color_index < semitrans_limit) << 15;
        if (color_index < 5) {
            red_end = rgb_mid[0] * weights[color_index - 1];
            start_weight = weight_scale - weights[color_index - 1];
            red_start = rgb_start[0] * start_weight;
            green_end = rgb_mid[1] * weights[color_index - 1];
            green_start = rgb_start[1] * start_weight;
            blue_end = rgb_mid[2] * weights[color_index - 1];
            blue_start = rgb_start[2] * start_weight;
            channel_sum = red_end + red_start;
            packed_color += channel_sum >> 5;
            channel_sum = green_end + green_start;
            packed_color += channel_sum & 0x3E0;
        } else {
            red_end = rgb_end[0] * weights[color_index - 1];
            start_weight = weight_scale - weights[color_index - 1];
            red_start = rgb_mid[0] * start_weight;
            green_end = rgb_end[1] * weights[color_index - 1];
            green_start = rgb_mid[1] * start_weight;
            blue_end = rgb_end[2] * weights[color_index - 1];
            blue_start = rgb_mid[2] * start_weight;
            channel_sum = red_end + red_start;
            packed_color += channel_sum >> 5;
            channel_sum = green_end + green_start;
            packed_color += channel_sum & 0x3E0;
        }
        channel_sum = blue_end + blue_start;
        packed_color += (channel_sum & 0x3E0) << 5;
        colors[color_index] = packed_color;
        color_index++;
    } while (color_index < 9);
    func_8003F80C(colors, (palette_slot & 0xF) | 0x7D00, 1, 2);
    DrawSync(0);
}
