#include "shared/entity.h"
#include "modules/dungeon_ovl_188e800.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_node.h"

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Retail 8186E96C (begin_view_parameter_transition): projects each linked point and queues a brightness-scaled shaded point
 * followed by a draw-mode packet for it. */
s32 begin_view_parameter_transition(PointRecord *start_node, EntityRec *start_coords)
{
    GpuContext **state_ptr;
    Scratch8002416C *scratch;
    GpuContext *render_state;
    GpuContext *final_state;
    PointPacket *packet;
    PointRecord *node;
    EntityRec *coords;
    ObjectNodeHeader *prev_entry;
    u32 depth_index;
    u16 coord_x;

    node = start_node;
    coords = start_coords;
    state_ptr = (GpuContext **)&g_game_work;
    render_state = *state_ptr;
    scratch = (Scratch8002416C *)0x1F800000;

    scratch->cursor = render_state->packetCursor;
    scratch->ot = (u32 *)&render_state->orderTag;

    for (;;) {
        coord_x = (u16)coords->x.w.i;
        packet = (PointPacket *)scratch->cursor;
        scratch->x = coord_x;
        scratch->y = (u16)coords->y.w.i;
        scratch->z = (u16)coords->z.w.i;
        scratch->cursor = (u8 *)packet + 0xC;

        depth_index = func_80065420(scratch, (u8 *)packet + 8, &scratch->xy, &scratch->depth);
        scratch->index = depth_index;

        if (depth_index < 0x1E0) {
            s32 color_or_tpage;
            PointPacket *mode_packet;

            *(u32 *)&packet->r = node->color;
            color_or_tpage = packet->r * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->r = color_or_tpage >> 8;

            color_or_tpage = packet->g * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->g = color_or_tpage >> 8;

            color_or_tpage = packet->b * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->b = color_or_tpage >> 8;
            ((u8 *)packet)[3] = 2;
            packet->code = 0x6A;

            ((GpuLinkTag *)&packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)packet & 0x00FFFFFF);

            mode_packet = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)mode_packet + 0xC;
            color_or_tpage = func_80066460(0, 1, 0, 0);
            func_80067F20(mode_packet, 0, 0, (u16)color_or_tpage, 0);

            ((GpuLinkTag *)&mode_packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)mode_packet & 0x00FFFFFF);
        }

        prev_entry = ((ObjectNodeHeader *)node - 1)->chain_next;
        node = (PointRecord *)(prev_entry + 1);
        if (prev_entry == 0) {
            break;
        }
        coords = prev_entry->unk_08;
    }

    final_state = *state_ptr;
    final_state->packetCursor = scratch->cursor;
    return 0;
}
