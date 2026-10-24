#include "dungeon/effect.h"
#include "dungeon/effect/motion.h"
#include "shared/dungeon_effect_views.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_node.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"

typedef struct BallPointPacket {
    GpuLinkTag tag;
    union {
        u32 color;
        struct { u8 r, g, b, code; } channels;
    } rgb;
    s32 xy;
} BallPointPacket;

typedef struct BallPointScratch {
    u16 x, y, z;
    u8 pad_06[0x12];
    BallPointPacket *cursor;
    u8 pad_1C[4];
    GpuLinkTag *ot;
    u8 pad_24[0x6C];
    s32 xy;
    s32 depth;
    u8 pad_98[0x28];
    u32 index;
} BallPointScratch;

/* Mark the ball effect active and queue its brightness-scaled point tiles. */
s32 draw_ball_effect_points(PointRecord *first_point, ObjectPosition *first_position)
{
    particle_effect_active = 1;
    {
        PointRecord *point = first_point;
        ObjectPosition *position = first_position;
        GameWork *render_state = &g_game_work;
        GpuContext *render_ctx;
        void *packet_start;
        BallPointScratch *scratch = (BallPointScratch *)0x1F800000;
        BallPointPacket *tile;
        BallPointPacket *draw_mode;
        GpuContext *final_render_ctx;
        s32 color_value;
        u16 draw_page;
        ObjectNodeHeader *next_node;
        void *table;
        void *next_data;

        render_ctx = g_game_work.draw_buffer;
        packet_start = render_ctx->packetCursor;
        table = &render_ctx->orderTag;
        scratch->ot = table;
        scratch->cursor = packet_start;

        for (;;) {
            tile = scratch->cursor;
            scratch->x = position->x.w.i;
            scratch->y = position->y.w.i;
            scratch->z = position->z.w.i;
            scratch->cursor = tile + 1;
            scratch->index = RotTransPers(scratch, &tile->xy, &scratch->xy, &scratch->depth);
            if (scratch->index < 480U) {
                tile->rgb.color = point->color;
                color_value = tile->rgb.channels.r * point->brightness;
                if (color_value < 0) { color_value += 255; }
                tile->rgb.channels.r = color_value >> 8;
                color_value = tile->rgb.channels.g * point->brightness;
                if (color_value < 0) { color_value += 255; }
                tile->rgb.channels.g = color_value >> 8;
                color_value = tile->rgb.channels.b * point->brightness;
                if (color_value < 0) { color_value += 255; }
                tile->rgb.channels.b = color_value >> 8;
                tile->tag.len = 2;
                tile->rgb.channels.code = 0x6A;
                tile->tag.addr = scratch->ot[scratch->index].addr;
                scratch->ot[scratch->index].addr = (u32)tile;
                draw_mode = scratch->cursor;
                scratch->cursor = draw_mode + 1;
                draw_page = GetTPage(0, 1, 0, 0);
                SetDrawMode(draw_mode, 0, 0, draw_page, 0);
                draw_mode->tag.addr = scratch->ot[scratch->index].addr;
                scratch->ot[scratch->index].addr = (u32)draw_mode;
            }
            next_node = ((ObjectNodeHeader *)point - 1)->chain_next;
            if (next_node != 0) {
                next_data = next_node + 1;
                point = next_data;
                position = next_node->position;
                continue;
            }
            break;
        }
        final_render_ctx = render_state->draw_buffer;
        final_render_ctx->packetCursor = (void *)scratch->cursor;
        return 0;
    }
}
