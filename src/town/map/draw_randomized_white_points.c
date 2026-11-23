#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"
#include "sdk/libgpu_packets.h"
#include "sdk/libgte.h"
#include "town/map.h"

/* Draws randomized white points around each object in the linked chain. */
s32 draw_randomized_white_points(TownMapPhaseObject *object, ObjectPosition *coords)
{
    s16 angle;
    s32 radius_offset;
    TILE_1 *packet;
    s32 point_index;
    WhitePointScratch *scratch;
    u32 addr_mask;
    u32 tag_mask;
    GpuContext *arena;
    ObjectNodeHeader *next_node;
    s32 random_value;
    s32 x_scale;
    u32 packet_tag;
    u32 linked_tag;
    unsigned long ot_link;
    GameWork *render_state;

    render_state = &g_game_work;
    scratch = WHITE_POINT_SCRATCH;
    scratch->ordering_table = render_state->draw_buffer + 0xB0;
    addr_mask = 0x00FFFFFF;
    tag_mask = 0xFF000000;

    while (1) {
        point_index = 0;
        do {
            arena = render_state->draw_buffer;
            packet = arena->packetCursor;
            arena->packetCursor = packet + 1;
            ((u8 *)&packet->tag)[3] = 2;
            packet->code = 0x68;
            packet->r0 = 0xFF;
            packet->g0 = 0xFF;
            packet->b0 = 0xFF;

            random_value = rand();
            angle = (s16)(random_value % 0x1000);

            x_scale = rsin(angle) >> 4;
            {
                s32 base_radius = object->radius_bias;
                radius_offset = (point_index / 8) % 12 + 0x48;
                scratch->position.vx =
                    coords->x.w.i + ((x_scale * (base_radius + radius_offset)) >> 8);
            }

            scratch->position.vy =
                coords->y.w.i +
                (((rcos(angle) >> 4) *
                  (object->radius_bias + radius_offset)) >> 8);

            scratch->position.vz =
                coords->z.w.i -
                (((rsin((point_index % 16) << 6) >> 4) *
                  (object->unk_66 + 0x10)) >> 8);

            scratch->ot_index = RotTransPers(
                &scratch->position, (s32 *)scratch, &scratch->depth_cue, &scratch->gte_flag);
            packet->x0 = scratch->screen.x;
            packet->y0 = scratch->screen.y;

            ot_link = scratch->ot_index;
            if (ot_link < 0x1E0) {
                packet_tag = packet->tag;
                ot_link = scratch->ordering_table[ot_link];
                ot_link &= addr_mask;
                linked_tag = packet_tag & tag_mask;
                linked_tag |= ot_link;
                packet->tag = linked_tag;
                scratch->ordering_table[scratch->ot_index] =
                    (scratch->ordering_table[scratch->ot_index] & tag_mask) |
                    ((u32)packet & addr_mask);
            }
        } while (++point_index < 0x180);

        next_node = NODE_HEADER(object)->chain_next;
        if (next_node == 0) {
            break;
        }
        object = NODE_BODY(next_node);
        coords = next_node->position;
    }
    return 0;
}
