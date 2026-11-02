#include "engine/graphics/frame_context.h"
#include "shared/object_node.h"
#include "engine/graphics/sprite_packet.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "frontend/settings.h"
#include "sdk/libgpu.h"


#define setaddr(packet, address) (((GpuLinkTag *)(packet))->addr = (u32)(address))
#define getaddr(packet) ((u32)(((GpuLinkTag *)(packet))->addr))
#define addPrim(ordering_table, primitive) \
(setaddr((primitive), getaddr(ordering_table)), \
    setaddr((ordering_table), (primitive)))

/* Builds layered sprite tiles and texture-page commands for each linked node. */
s32 build_settings_sprite_tiles(void *node_data, void *scroll_state)
{
    FrameDrawContextSlot *ctx_ptr;
    s32 layer_offset;
    s32 tile_row;
    s32 tile_col;
    s32 tile_y;
    s32 page_x;
    u16 scroll_y;
    s32 screen_y;
    s16 screen_x;
    s32 clut_x;
    TexturedSpritePacket *sprite;
    void *draw_mode;
    ObjectNodeHeader *next_node;
    GpuContext *ctx;

    ctx_ptr = (FrameDrawContextSlot *)&g_game_work.draw_buffer;

    do {
        layer_offset = 2;
        do {
            tile_row = 0;
            do {
                tile_col = 1;
                tile_y = tile_row << 8;
                page_x = 0x280;
                do {
                    sprite = ctx_ptr->context->packetCursor;
                    ctx_ptr->context->packetCursor = sprite + 1;
                    sprite->color_code = 0x505050;
                    SetSprt(sprite);
                    SetSemiTrans(sprite, 1);
                    clut_x = 0;
                    screen_x = tile_col;
                    screen_x <<= 8;
                    screen_x += layer_offset;
                    sprite->x = screen_x;
                    scroll_y = ((ObjectPosition *)scroll_state)->y.unsigned_parts.integer;
                    sprite->width = 0x100;
                    sprite->height = 0x100;
                    sprite->texture.packed = 0;
                    screen_y = (tile_y - scroll_y) + layer_offset;
                    sprite->y = screen_y;
                    sprite->clut = GetClut(clut_x, 0x1F0);
                    addPrim(&ctx_ptr->context->orderTag82C, sprite);

                    ctx = ctx_ptr->context;
                    draw_mode = ctx->packetCursor;
                    ctx->packetCursor = (u8 *)draw_mode + 0xC;
                    SetDrawMode(draw_mode, 0, 0,
                                  GetTPage(1, 3, page_x, tile_y) & 0xFFFF, 0);
                    tile_col -= 1;
                    addPrim(&ctx_ptr->context->orderTag82C, draw_mode);
                    page_x -= 0x80;
                } while (tile_col >= 0);
                tile_row += 1;
            } while (tile_row < 2);
            layer_offset -= 1;
        } while (layer_offset >= 0);

        next_node = ((ObjectNodeHeader *)node_data - 1)->chain_next;
        if (next_node == 0) {
            break;
        }
        node_data = next_node + 1;
        scroll_state = next_node->position;
    } while (1);
    return 0;
}
