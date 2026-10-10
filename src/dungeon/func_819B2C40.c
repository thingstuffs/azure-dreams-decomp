#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_node.h"

/* A sprite effect record (the object header precedes it): world position of the centre, the size and the
 * texture window of the quad it draws.  The coordinates sit in 4-byte slots with only the second halfword used. */
typedef struct SpriteEffect {
    u8 pad_00[0x1E];
    u16 x;              /* 0x1E */
    u8 pad_20[2];
    u16 y;              /* 0x22 */
    u8 pad_24[2];
    u16 z;              /* 0x26 */
    u8 pad_28[0x18];
    u8 tex_u;           /* 0x40 */
    u8 pad_41;
    u8 tex_v;           /* 0x42 */
    u8 pad_43;
    u8 tex_width;       /* 0x44 */
    u8 pad_45;
    u8 tex_height;      /* 0x46 */
    u8 pad_47[7];
    u16 size;           /* 0x4E: world-space width */
    u16 tpage;          /* 0x50 */
    u16 clut;           /* 0x52 */
} SpriteEffect;

/* The two projected points (centre and one edge): x/y in 4-byte slots. */
typedef struct ScreenPoints {
    u16 x0;
    s16 y0;
    u16 x1;
    s16 y1;
} ScreenPoints;

/* Textured quad, four vertices with separate halfword coordinates (cf. PolyFT4). */
typedef struct SpriteQuad {
    u32 tag;
    s32 color;
    u16 x0;
    u16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    u16 x1;
    u16 y1;
    u8 u1;
    u8 v1;
    u16 tpage;
    u16 x2;
    u16 y2;
    u8 u2;
    u8 v2;
    u8 pad_1E[2];
    u16 x3;
    u16 y3;
    u8 u3;
    u8 v3;
} SpriteQuad;

extern s32 func_80065420();
extern void func_80066640();
extern void func_800666F4();

/* Retail 819B2C40 (func_80024440): projects each linked sprite effect and queues a textured quad centred on
 * its screen position into the ordering table.  The chain runs through the previous header's unk_18 link. */
s32 func_80024440(SpriteEffect *first_item) {
    u16 world_pos[4];
    ScreenPoints screen_points;
    s32 projection_scratch;
    SpriteEffect *node = first_item;
    GameWork *render_state = &gameWork;
    void *screen_base = &screen_points;
    ObjectNodeHeader *next_node;

    for (;;) {
        SpriteEffect *item = node;
        void *screen_point;
        s32 point_index;
        u32 depth_index;
        s32 half_width;
        u16 center_z;

        world_pos[0] = item->x;
        world_pos[1] = item->y;
        center_z = item->z;
        world_pos[2] = center_z;
        world_pos[2] = center_z - ((s32)(item->size << 16) >> 17);

        point_index = 0;
        screen_point = screen_base;
        do {
            depth_index = func_80065420(world_pos, screen_point, &projection_scratch, &projection_scratch) - 8;
            screen_point = (u8 *)screen_point + 4;
            point_index++;
            world_pos[2] += item->size;
        } while (point_index < 2);

        half_width = (screen_points.y0 - screen_points.y1) >> 1;
        if (depth_index < 0x1E0U) {
            GpuContext *packet_pool;
            SpriteQuad *packet;
            u8 tex_v;
            u8 tex_u;
            u8 tex_width;
            u16 screen_coord;
            u32 ot_slot;
            u32 depth_offset;
            u32 addr_mask = 0;
            u32 color_or_tag_mask = 0;

            packet_pool = render_state->unk_000;
            packet = (SpriteQuad *)packet_pool->packetCursor;
            packet_pool->packetCursor = (u8 *)packet + 0x34;
            packet->color = 0xA0A0A0;
            func_800666F4(packet);
            func_80066640(packet, 1);

            packet->tpage = item->tpage;
            packet->clut = item->clut;
            screen_coord = screen_points.x0 + half_width;
            packet->x1 = screen_coord;
            packet->x0 = screen_coord;
            screen_coord = screen_points.x0 - half_width;
            packet->x3 = screen_coord;
            packet->x2 = screen_coord;
            screen_coord = screen_points.y0;
            packet->y2 = screen_coord;
            packet->y0 = screen_coord;
            screen_coord = screen_points.y1;
            packet->y3 = screen_coord;
            packet->y1 = screen_coord;

            tex_u = item->tex_u;
            addr_mask = 0xFFFFFF;
            packet->u1 = tex_u;
            packet->u0 = tex_u;
            tex_width = item->tex_width;
            tex_u += tex_width;
            packet->u3 = tex_u;
            packet->u2 = tex_u;
            tex_v = item->tex_v;
            depth_offset = depth_index << 2;
            packet->v2 = tex_v;
            packet->v0 = tex_v;
            tex_v += item->tex_height;
            color_or_tag_mask = 0xFF000000;
            packet->v3 = tex_v;
            packet->v1 = tex_v;

            packet->tag =
                (packet->tag & color_or_tag_mask) |
                (*(u32 *)((u8 *)(depth_offset + (u32)render_state->unk_000) + 0xB0) & addr_mask);
            ot_slot = depth_offset + (u32)render_state->unk_000;
            *(u32 *)((u8 *)ot_slot + 0xB0) =
                (*(u32 *)((u8 *)ot_slot + 0xB0) & color_or_tag_mask) |
                ((u32)packet & addr_mask);
        }

        next_node = (ObjectNodeHeader *)((ObjectNodeHeader *)node - 1)->unk_18;
        if (next_node == 0) {
            break;
        }
        node = (SpriteEffect *)(next_node + 1);
    }

    return 0;
}
