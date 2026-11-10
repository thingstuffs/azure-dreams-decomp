#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "town/map.h"

typedef struct S_800BB218_0 {
    u16 unk_00;
    u16 unk_02;
    u32 unk_04;
    u8 pad_08[0x8];
    u8 * unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
} S_800BB218_0;   /* scratch in draw_randomized_white_points */

   /* arena in draw_randomized_white_points */

typedef struct S_800BB218_4 {
    u32 unk_00;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
} S_800BB218_4;   /* packet in draw_randomized_white_points */

typedef struct S_800BB218_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_800BB218_5;   /* next in draw_randomized_white_points */

/* Draws randomized white points around each object in the linked chain. */
s32 draw_randomized_white_points(void *first_object, void *first_coords)
{
    s16 angle;
    s32 radius_offset;
    u8 *packet;
    s32 point_index;
    S_800BB218_0 *scratch;
    u8 *object;
    MovingPosition *coords;
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

    object = first_object;
    coords = first_coords;
    render_state = &g_game_work;
    scratch = (S_800BB218_0 *)0x1F800000;
    scratch->unk_10 = render_state->draw_buffer + 0xB0;
    addr_mask = 0x00FFFFFF;
    tag_mask = 0xFF000000;

    while (1) {
        point_index = 0;
        do {
            arena = render_state->draw_buffer;
            packet = arena->packetCursor;
            arena->packetCursor = packet + 0xC;
            packet[3] = 2;
            packet[7] = 0x68;
            packet[4] = 0xFF;
            packet[5] = 0xFF;
            packet[6] = 0xFF;

            random_value = rand();
            angle = (s16)(random_value % 0x1000);

            x_scale = rsin(angle) >> 4;
            {
                s32 base_radius = ((TownObjectRecord *)object)->unk_97;
                radius_offset = (point_index / 8) % 12 + 0x48;
                scratch->unk_14 =
                    coords->x + ((x_scale * (base_radius + radius_offset)) >> 8);
            }

            scratch->unk_16 =
                coords->y +
                (((rcos(angle) >> 4) *
                  (((TownObjectRecord *)object)->unk_97 + radius_offset)) >> 8);

            scratch->unk_18 =
                coords->z -
                (((rsin((point_index % 16) << 6) >> 4) *
                  (((TownObjectRecord *)object)->unk_66 + 0x10)) >> 8);

            scratch->unk_04 = RotTransPers(
                &scratch->unk_14, (s32 *)scratch, (u8 *)scratch + 8, (u8 *)scratch + 0xC);
            ((S_800BB218_4 *)packet)->unk_08 = scratch->unk_00;
            ((S_800BB218_4 *)packet)->unk_0A = scratch->unk_02;

            ot_link = scratch->unk_04;
            if (ot_link < 0x1E0) {
                ot_link <<= 2;
                ot_link += (unsigned long)scratch->unk_10;
                packet_tag = ((S_800BB218_4 *)packet)->unk_00;
                ot_link = *(u32 *)ot_link;
                ot_link &= addr_mask;
                linked_tag = packet_tag & tag_mask;
                linked_tag |= ot_link;
                ((S_800BB218_4 *)packet)->unk_00 = linked_tag;
                *(u32 *)(scratch->unk_10 +
                         scratch->unk_04 * 4) =
                    (*(u32 *)(scratch->unk_10 +
                              scratch->unk_04 * 4) & tag_mask) |
                    ((u32)packet & addr_mask);
            }
        } while (++point_index < 0x180);

        next_node = NODE_HEADER(object)->chain_next;
        if (next_node == 0) {
            break;
        }
        object = NODE_BODY(next_node);
        coords = ((S_800BB218_5 *)next_node)->unk_08;
    }
    return 0;
}
