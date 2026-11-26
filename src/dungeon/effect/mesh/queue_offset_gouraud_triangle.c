#include "common.h"
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "shared/game_work.h"
#include "dungeon/effect/mesh.h"
#include "sdk/libgpu.h"

typedef struct Packet81976CB0 {
    u8 link_bytes[3];
    u8 type;
    u8 x0_hi;
    u8 x0_mid;
    u8 x0_lo;
    u8 unk7;
    u16 u8;
    u16 uA;
    u8 color0;
    u8 color1;
    u16 clut;
    u8 x1_hi;
    u8 x1_mid;
    u8 x1_lo;
    u8 pad13;
    u16 u14;
    u16 u16;
    u8 color2;
    u8 color3;
    u16 random;
    u8 x2_hi;
    u8 x2_mid;
    u8 x2_lo;
    u8 pad1F;
    u16 u20;
    u16 u22;
    u8 color4;
    u8 color5;
    u8 pad26[2];
} Packet81976CB0;


extern s32 func_80065530(void *, void *, void *, void *, void *, void *, void *, void *);

/*
 * Allocates a shaded textured triangle packet with CLUT 0x7DCF, translates scratch vertices by
 * effect_position_source, and projects them. Links the packet into the ordering table only for
 * depths below 0x1E0.
 */
s32 queue_offset_gouraud_triangle(s32 vertex_color0, s32 vertex_color1, s32 vertex_color2)
{
    GpuContext *state;
    Packet81976CB0 *packet;
    RadialBandQuadScratch *scratch = RADIAL_BAND_SCRATCH;
    MeshEffectOrigin *vertex_offset;
    void *screen_xy1;
    void *screen_xy2;
    void *depth_cue;
    void *transform_flags;

    state = g_game_work.draw_buffer;
    scratch->ordering_table = &state->orderTag[GPU_ORDER_DEPTH_BASE];
    packet = state->packetCursor;
    state->packetCursor = packet + 1;

    packet->type = 9;
    packet->unk7 = 0x36;
    packet->random = GetTPage(0, 3, 0x300, 0x100);
    screen_xy1 = &scratch->screen[1];
    screen_xy2 = &scratch->screen[2];
    depth_cue = &scratch->depth_cue;
    transform_flags = scratch;
    packet->clut = 0x7DCF;
    packet->color0 = 0xC0;
    packet->color1 = 0x7F;
    packet->color2 = 0xFF;
    packet->color3 = 0x40;
    packet->color4 = 0xFF;
    packet->color5 = 0x7F;
    packet->x0_hi = vertex_color0 >> 16;
    packet->x0_mid = vertex_color0 >> 8;
    packet->x0_lo = vertex_color0;
    packet->x1_hi = vertex_color1 >> 16;
    packet->x1_mid = vertex_color1 >> 8;
    packet->x1_lo = vertex_color1;
    packet->x2_hi = vertex_color2 >> 16;
    packet->x2_mid = vertex_color2 >> 8;
    packet->x2_lo = vertex_color2;

    vertex_offset = effect_position_source;
    scratch->vertices[0].vx = (scratch->positions[0].vx + vertex_offset->x.v) >> 16;
    transform_flags = &scratch->gte_flag;
    scratch->vertices[1].vx = (scratch->positions[1].vx + vertex_offset->x.v) >> 16;
    scratch->vertices[2].vx = (scratch->positions[2].vx + vertex_offset->x.v) >> 16;
    scratch->vertices[0].vy = (scratch->positions[0].vy + vertex_offset->y.v) >> 16;
    scratch->vertices[1].vy = (scratch->positions[1].vy + vertex_offset->y.v) >> 16;
    scratch->vertices[2].vy = (scratch->positions[2].vy + vertex_offset->y.v) >> 16;
    scratch->vertices[0].vz = (scratch->positions[0].vz + vertex_offset->z.v) >> 16;
    scratch->vertices[1].vz = (scratch->positions[1].vz + vertex_offset->z.v) >> 16;
    scratch->vertices[2].vz = (scratch->positions[2].vz + vertex_offset->z.v) >> 16;

    scratch->ot_index = func_80065530(
        &scratch->vertices[0], &scratch->vertices[1],
        &scratch->vertices[2], &scratch->screen[0],
        screen_xy1, screen_xy2, depth_cue, transform_flags);

    packet->u8 = scratch->screen[0].x;
    packet->uA = scratch->screen[0].y;
    packet->u14 = scratch->screen[1].x;
    packet->u16 = scratch->screen[1].y;
    packet->u20 = scratch->screen[2].x;
    packet->u22 = scratch->screen[2].y;

    if (scratch->ot_index < 0x1E0U) {
        u32 ordering_link = scratch->ordering_table[scratch->ot_index];
        *(u32 *)packet = (*(u32 *)packet & 0xFF000000) | (ordering_link & 0x00FFFFFF);
        scratch->ordering_table[scratch->ot_index] =
            (scratch->ordering_table[scratch->ot_index] & 0xFF000000) |
            ((u32)packet & 0x00FFFFFF);
    }

    return 0;
}
