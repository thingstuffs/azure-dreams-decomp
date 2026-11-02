#include "engine/graphics/line_packet.h"
#include "engine/graphics/frame_context.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "engine/graphics.h"

/* Draw a shaded horizontal line with dimmer translucent lines above and below. */
void draw_shaded_horizontal_line(s16 x, s16 y, s16 width, s16 shade_step)
{
    FrameDrawContextSlot *render_state;
    ShadedLinePacket *center_line;
    ShadedLinePacket *upper_line;
    ShadedLinePacket *lower_line;
    s16 red_green;
    s16 blue;

    render_state = (FrameDrawContextSlot *)&g_game_work.draw_buffer;
    if (shade_step < 0x11) {
        blue = shade_step * 8 + 0x80;
        if (blue == 0x100) {
            blue = 0xFF;
        }
        red_green = shade_step * 8 + 0x40;
    } else {
        blue = 0x200 - shade_step * 16;
        red_green = 0x100 - shade_step * 8;
    }

    center_line = render_state->context->packetCursor;
    render_state->context->packetCursor = center_line + 1;
    center_line->tag.bytes.len = 3;
    center_line->code = 0x40;
    center_line->r0 = red_green;
    center_line->g0 = red_green;
    center_line->b0 = blue;
    if (x > 0) {
        center_line->x0 = 0;
        center_line->y0 = y;
        center_line->x1 = x + width - 1;
        center_line->y1 = y;
    } else {
        center_line->x0 = x;
        center_line->y0 = y;
        center_line->x1 = x + width - 1;
        center_line->y1 = y;
    }
    center_line->tag.word = (center_line->tag.word & 0xFF000000) | (render_state->context->orderTag230 & 0xFFFFFF);
    render_state->context->orderTag230 = (render_state->context->orderTag230 & 0xFF000000)
    | ((u32)center_line & 0xFFFFFF);

    blue = blue / 3;
    blue = blue * 2;
    red_green = red_green / 3;
    red_green = red_green * 2;

    upper_line = render_state->context->packetCursor;
    render_state->context->packetCursor = upper_line + 1;
    upper_line->tag.bytes.len = 3;
    upper_line->code = 0x42;
    upper_line->r0 = red_green;
    upper_line->g0 = red_green;
    upper_line->b0 = blue;
    if (x > 0) {
        upper_line->x0 = 0;
        upper_line->y0 = y - 1;
        upper_line->x1 = x + width - 1;
        upper_line->y1 = y - 1;
    } else {
        upper_line->x0 = x;
        upper_line->y0 = y - 1;
        upper_line->x1 = x + width - 1;
        upper_line->y1 = y - 1;
    }
    upper_line->tag.word = (upper_line->tag.word & 0xFF000000) | (render_state->context->orderTag230 & 0xFFFFFF);
    render_state->context->orderTag230 = (render_state->context->orderTag230 & 0xFF000000)
    | ((u32)upper_line & 0xFFFFFF);

    lower_line = render_state->context->packetCursor;
    render_state->context->packetCursor = lower_line + 1;
    lower_line->tag.bytes.len = 3;
    lower_line->code = 0x42;
    lower_line->r0 = red_green;
    lower_line->g0 = red_green;
    lower_line->b0 = blue;
    if (x > 0) {
        lower_line->x0 = 0;
        lower_line->y0 = y + 1;
        lower_line->x1 = x + width - 1;
        lower_line->y1 = y + 1;
    } else {
        lower_line->x0 = x;
        lower_line->y0 = y + 1;
        lower_line->x1 = x + width - 1;
        lower_line->y1 = y + 1;
    }
    lower_line->tag.word = (lower_line->tag.word & 0xFF000000) | (render_state->context->orderTag230 & 0xFFFFFF);
    render_state->context->orderTag230 = (render_state->context->orderTag230 & 0xFF000000)
    | ((u32)lower_line & 0xFFFFFF);
}
