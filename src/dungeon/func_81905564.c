#include "shared/entity.h"
#include "modules/dungeon_ovl_1924800.h"

/* Retail 81905564 (draw_brightness_scaled_linked_tiles): projects each linked point and queues a brightness-scaled shaded tile
 * followed by a draw-mode packet for it. */
s32 draw_brightness_scaled_linked_tiles(PointRecord *first_point, EntityRec *first_position)
{
    PointRecord *point = first_point;
    EntityRec *position = first_position;
    GameWork *render_state = &g_game_work;
    u32 addr_mask = 0x00FFFFFF;
    GpuContext *render_ctx = g_game_work.unk_000;
    u8 *packet_start;
    u32 tag_mask = 0xFF000000;
    Scratch80024D64 *scratch =
        (Scratch80024D64 *)0x1F800000;
    PointPacket *tile;
    PointPacket *draw_mode;
    GpuContext *final_render_ctx;
    s32 color_value;
    s32 draw_page;
    ObjectNodeHeader *next_node;

    packet_start = render_ctx->packetCursor;
    scratch->ot = (u32 *)&render_ctx->orderTag;
    scratch->cursor = packet_start;

    for (;;) {
        tile = (PointPacket *)scratch->cursor;
        scratch->x = (u16)position->x.w.i;
        scratch->y = (u16)position->y.w.i;
        scratch->z = (u16)position->z.w.i;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = func_80065420(scratch, (u8 *)tile + 8,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            *(u32 *)&tile->r = point->color;

            color_value = (s32)tile->r * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->r = color_value >> 8;

            color_value = (s32)tile->g * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->g = color_value >> 8;

            color_value = (s32)tile->b * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->b = color_value >> 8;

            ((GpuLinkTag *)&tile->tag)->len = 2;
            tile->code = 0x6A;
            ((GpuLinkTag *)&tile->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = func_80066460(0, 1, 0, 0);
            func_80067F20(draw_mode, 0, 0, (u16)draw_page, 0);

            ((GpuLinkTag *)&draw_mode->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)draw_mode;
        }

        next_node = ((ObjectNodeHeader *)point - 1)->chain_next;
        if (next_node != 0) {
            point = (PointRecord *)(next_node + 1);
            position = next_node->unk_08;
            continue;
        }

        break;
    }

    final_render_ctx = render_state->unk_000;
    final_render_ctx->packetCursor = scratch->cursor;
    return 0;
}
