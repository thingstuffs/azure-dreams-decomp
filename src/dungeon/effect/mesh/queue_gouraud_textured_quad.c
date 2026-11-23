/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "dungeon/effect/mesh.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "dungeon/effect/travel/cycle_seven_color_fade.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} Tag;

typedef struct {
    u8 *ordering_table;
} Scratch;

typedef union {
    u8 bytes[0x40];
    u16 halfwords[0x20];
    u32 words[0x10];
} Poly;

typedef struct {
    u8 pad[0x8D0];
    Poly *poly;
} Context;



/*
 * Builds a four-color textured quad with CLUT 0x7DCF and texture page (0x300, 0x100), translating
 * the scratch vertices by effect_position_source before projection. Links it into the ordering
 * table only for depths below 0x1E0 and returns zero.
 */
s32 queue_gouraud_textured_quad(s32 color0, s32 color1, s32 color2, s32 color3) {
    Poly *quad;
    Context *u_right;
    s16 texture_page;
    Scratch *scratch;
    RadialBandQuadScratch *band;
    MeshEffectOrigin *offsets;
    u16 *screen0;
    u16 *screen1;
    u16 *screen2;
    u16 *screen3;
    void *depth_cue;
    void *transform_flags;
    void *vertex0;
    void *vertex1;
    void *vertex2;
    void *vertex3;

    vertex0 = 0;
    vertex1 = (void *)3;
    u_right = g_game_work.draw_buffer;
    vertex2 = (void *)0x300;
    scratch = (Scratch *)0x1F800000;
    band = RADIAL_BAND_SCRATCH;
    scratch->ordering_table = (u8 *)u_right + 0xB0;
    quad = u_right->poly;
    u_right->poly = (Poly *)((u8 *)quad + 0x34);
    quad->bytes[3] = 0xC;
    quad->bytes[7] = 0x3E;
    vertex3 = (void *)0x100;
    texture_page = GetTPage(vertex0, vertex1, vertex2, vertex3);
    screen0 = &band->screen[0].x;
    screen1 = &band->screen[1].x;
    screen2 = &band->screen[2].x;
    screen3 = &band->screen[3].x;
    quad->halfwords[0x1A / 2] = texture_page;
    quad->halfwords[0xE / 2] = 0x7DCF;
    quad->bytes[0xC] = 0xC0;
    quad->bytes[0xD] = 0x40;
    quad->bytes[0x18] = 0xFF;
    quad->bytes[0x19] = 0x40;
    quad->bytes[0x24] = 0xC0;
    quad->bytes[0x25] = 0x7F;
    quad->bytes[0x30] = 0xFF;
    quad->bytes[0x31] = 0x7F;
    quad->bytes[4] = (u8)(color0 >> 0x10);
    quad->bytes[5] = (u8)(color0 >> 8);
    quad->bytes[0x10] = (u8)(color1 >> 0x10);
    quad->bytes[0x11] = (u8)(color1 >> 8);
    quad->bytes[0x1C] = (u8)(color2 >> 0x10);
    quad->bytes[0x1D] = (u8)(color2 >> 8);
    quad->bytes[0x28] = (u8)(color3 >> 0x10);
    quad->bytes[0x29] = (u8)(color3 >> 8);
    quad->bytes[6] = (u8)color0;
    quad->bytes[0x12] = (u8)color1;
    quad->bytes[0x1E] = (u8)color2;
    quad->bytes[0x2A] = (u8)color3;
    offsets = effect_position_source;
    band->vertices[0].vx = (s16)((band->positions[0].vx + offsets->x.v) >> 0x10);
    band->vertices[1].vx = (s16)((band->positions[1].vx + offsets->x.v) >> 0x10);
    depth_cue = &band->depth_cue;
    band->vertices[2].vx = (s16)((band->positions[2].vx + offsets->x.v) >> 0x10);
    band->vertices[3].vx = (s16)((band->positions[3].vx + offsets->x.v) >> 0x10);
    transform_flags = &band->gte_flag;
    band->vertices[0].vy = (s16)((band->positions[0].vy + offsets->y.v) >> 0x10);
    band->vertices[1].vy = (s16)((band->positions[1].vy + offsets->y.v) >> 0x10);
    vertex0 = &band->vertices[0];
    band->vertices[2].vy = (s16)((band->positions[2].vy + offsets->y.v) >> 0x10);
    band->vertices[3].vy = (s16)((band->positions[3].vy + offsets->y.v) >> 0x10);
    vertex1 = &band->vertices[1];
    band->vertices[0].vz = (s16)((band->positions[0].vz + offsets->z.v) >> 0x10);
    band->vertices[1].vz = (s16)((band->positions[1].vz + offsets->z.v) >> 0x10);
    vertex2 = &band->vertices[2];
    band->vertices[2].vz = (s16)((band->positions[2].vz + offsets->z.v) >> 0x10);
    band->vertices[3].vz = (s16)((band->positions[3].vz + offsets->z.v) >> 0x10);
    vertex3 = &band->vertices[3];
    band->ot_index = RotAverage4(vertex0, vertex1, vertex2, vertex3, screen0, screen1, screen2, screen3,
        depth_cue, transform_flags);
    quad->halfwords[8 / 2] = band->screen[0].x;
    quad->halfwords[0xA / 2] = band->screen[0].y;
    quad->halfwords[0x14 / 2] = band->screen[1].x;
    quad->halfwords[0x16 / 2] = band->screen[1].y;
    quad->halfwords[0x20 / 2] = band->screen[2].x;
    quad->halfwords[0x22 / 2] = band->screen[2].y;
    quad->halfwords[0x2C / 2] = band->screen[3].x;
    quad->halfwords[0x2E / 2] = band->screen[3].y;
    if (band->ot_index < 0x1E0U) {
        ((Tag *)quad)->addr = ((Tag *)((u32 *)scratch->ordering_table + band->ot_index))->addr;
        ((Tag *)((u32 *)scratch->ordering_table + band->ot_index))->addr = (u32)quad;
    }
    return 0;
}
