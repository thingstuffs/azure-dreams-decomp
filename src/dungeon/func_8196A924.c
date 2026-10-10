#include "modules/dungeon_ovl_198a800.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_node.h"

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Retail 8196A924 (func_80024124): projects each linked point and queues a brightness-scaled shaded tile
 * followed by a draw-mode packet for it. */
s32 func_80024124(PointRecord *first_point, PointPosition *first_position)
{
    PointRecord *point = first_point;
    PointPosition *position = first_position;
    GameWork *render_state = &gameWork;
    u32 addr_mask = 0x00FFFFFF;
    GpuContext *render_ctx = gameWork.unk_000;
    u8 *packet_start;
    u32 tag_mask = 0xFF000000;
    Scratch80024124 *scratch =
        (Scratch80024124 *)0x1F800000;
    Packet80024124 *tile;
    Packet80024124 *draw_mode;
    GpuContext *final_render_ctx;
    s32 color_value;
    s32 draw_page;
    ObjectNodeHeader *next_node;

    packet_start = render_ctx->packetCursor;
    scratch->ot = (u32 *)&render_ctx->orderTag;
    scratch->cursor = packet_start;

    for (;;) {
        tile = (Packet80024124 *)scratch->cursor;
        scratch->x = position->x;
        scratch->y = position->y;
        scratch->z = position->z;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = func_80065420(scratch, (u8 *)tile + 8,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            *(u32 *)&tile->r = point->color;

            color_value = (s32)tile->r * point->brightness;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->r = color_value >> 7;

            color_value = (s32)tile->g * point->brightness;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->g = color_value >> 7;

            color_value = (s32)tile->b * point->brightness;
            tile->b = (color_value / 128);

            ((GpuLinkTag *)&tile->tag)->len = 2;
            tile->code = 0x6A;
            ((GpuLinkTag *)&tile->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (Packet80024124 *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = func_80066460(0, 1, 0, 0);
            func_80067F20(draw_mode, 0, 0, (u16)draw_page, 0);

            ((GpuLinkTag *)&draw_mode->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)draw_mode;
        }

        next_node = (ObjectNodeHeader *)((ObjectNodeHeader *)point - 1)->unk_18;
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
