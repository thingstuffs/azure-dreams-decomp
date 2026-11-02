#include "engine/graphics/frame_context.h"
#include "shared/object_node.h"
#include "engine/graphics/sprite_packet.h"
#include "engine/text/glyph_body.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "engine/item.h"
#include "sdk/libgpu.h"
#include "engine/graphics.h"

/* Builds character sprites and draw modes for a linked list of text records. */
s32 build_text_glyph_sprites(TextGlyphBody *first_text)
{
    TextGlyphBody *text_record = first_text;
    FrameDrawContextSlot *render_state = (FrameDrawContextSlot *)&g_game_work.draw_buffer;
    TextGlyphBody *text;
    int texture_page;
    ObjectNodeHeader *next_node;
    do {
        s32 char_index = 0;
        s32 cursor_x;
        text = text_record;
        cursor_x = text->x;
        if (text->text[0] != 0) {
            do {
                u8 glyph_rect[4];
                TexturedSpritePacket *sprite;
                func_8004E21C(glyph_rect, text->text[char_index]);
                sprite = render_state->context->packetCursor;
                render_state->context->packetCursor = sprite + 1;
                sprite->x = cursor_x;
                sprite->y = text->y;
                sprite->clut = text->clut;
                sprite->color_code = text->color;
                sprite->texture.bytes.u = glyph_rect[0];
                sprite->texture.bytes.v = glyph_rect[1];
                sprite->width = glyph_rect[2];
                sprite->height = glyph_rect[3];
                cursor_x = cursor_x + glyph_rect[2];
                SetSprt(sprite);
                if (text->flags & 1) {
                    SetSemiTrans(sprite, 1);
                }
                if (!(text->flags & 2)) {
                    sprite->tag.addr = ((GpuLinkTag *) (&render_state->context->orderTag070))->addr;
                    ((GpuLinkTag *) (&render_state->context->orderTag070))->addr = (u32) sprite;
                }
                char_index++;
            }
            while (text->text[char_index] != 0);
        }
        {
            GpuLinkTag *draw_mode = render_state->context->packetCursor;
            render_state->context->packetCursor = ((u8 *) draw_mode) + 0xC;
            SetDrawMode(draw_mode, 0, 0, texture_page = GetTPage(0, text->blend_mode, 0x3C0, 0) & 0xFFFF, 0);
            draw_mode->addr = ((GpuLinkTag *) (&render_state->context->orderTag070))->addr;
            ((GpuLinkTag *) (&render_state->context->orderTag070))->addr = (u32) draw_mode;
        }
        next_node = ((ObjectNodeHeader *)text_record - 1)->chain_next;
        if (next_node == 0)
            break;
        text_record = (TextGlyphBody *)(next_node + 1);
    }
    while (1);
    return 0;
}
