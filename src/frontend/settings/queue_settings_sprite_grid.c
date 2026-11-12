#include "engine/graphics/sprite_packet.h"
#include "engine/graphics/frame_context.h"
#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "frontend/settings.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_types.h"
#include "shared/entity.h"
#include "shared/object_node.h"



#define PTR32(address) ((u32)(unsigned long)(address))
#define setaddr(packet, address) (((GpuLinkTag *)(packet))->addr = PTR32(address))
#define getaddr(packet) ((u32)(((GpuLinkTag *)(packet))->addr))
#define addPrim(ordering_table, primitive) \
(setaddr((primitive), getaddr(ordering_table)), \
    setaddr((ordering_table), (primitive)))



/* Queue a 2x2 grid of textured sprites for each linked entry. */
s32 queue_settings_sprite_grid(u8 *entry_data, u8 *scroll_data)
{
    ObjectPosition *position = (ObjectPosition *)scroll_data;
    FrameDrawContextSlot *main_state;
    TexturedSpritePacket *sprite;
    DR_MODE *draw_mode;
    ObjectNodeHeader *next_entry;
    s32 row;
    s32 column;
    s32 texture_page;
    s32 texture_x;
    s32 base_y;

    main_state = ((FrameDrawContextSlot *)&g_game_work.draw_buffer);
    for (;;) {
        row = 0;
        do {
            column = 1;
            base_y = row << 8;
            texture_x = 0x280;
            do {
                sprite = main_state->context->packetCursor;
                main_state->context->packetCursor = sprite + 1;
                sprite->color_code = 0x808080;
                SetSprt(sprite);
                SetShadeTex(sprite, 1);
                sprite->x = column << 8;
                sprite->y = base_y - position->y.unsigned_parts.integer;
                sprite->width = 0x100;
                sprite->height = 0x100;
                sprite->texture.packed = 0;
                sprite->clut = GetClut(0, 0x1F0);
                addPrim(&main_state->context->orderTag82C, sprite);

                draw_mode = main_state->context->packetCursor;
                main_state->context->packetCursor = draw_mode + 1;
                texture_page = GetTPage(1, 0, texture_x, base_y);
                SetDrawMode(draw_mode, 0, 0, texture_page & 0xFFFF, 0);
                column--;
                addPrim(&main_state->context->orderTag82C, draw_mode);
                texture_x -= 0x80;
            } while (column >= 0);
            row++;
        } while (row < 2);

        next_entry = ((ObjectNodeHeader *)entry_data - 1)->chain_next;
        if (next_entry == 0) {
            return 0;
        }
        entry_data = NODE_BODY(next_entry);
        position = next_entry->position;
    }
}
