#include "shared/gpu_packets.h"
#include "town/menu/line_effects.h"
#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_D_80100B70.h"
#include "shared/object_payload.h"

#define SCALE255(value) ((u32)(value) / 255)

extern s32 rand(void);
extern void SetLineG4(void *);
extern void SetSemiTrans(void *, s32);
extern void copy_odd_halfwords_3(void *, void *);
extern void copy_menu_vector_halfwords(void *, void *);
extern s32 RotTransPers4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void AddPrim(void *, void *);
extern u16 GetTPage(s32, s32, s32, s32);
extern void SetDrawMode(void *, s32, s32, u16, s32);



   /* ctx in draw_random_tinted_quad_pair */


typedef struct S_800A1354_4 {
    u8 pad_00[0x54];
    u8 * unk_54;
    u8 * unk_58;
    u8 * unk_5C;
} S_800A1354_4;   /* obj in draw_random_tinted_quad_pair */

   /* Draw two translucent quads with random vertex colors scaled by the effect intensity. */
void draw_random_tinted_quad_pair(u8 *effect)
{
    GpuContext **render_ctx_addr = (GpuContext **)&g_game_work.draw_buffer;
    s32 vertex_index = 0;
    u32 rgb_mask = 0xFFFFFF;
    MenuLineScratch *scratch = (MenuLineScratch *)0x1F800000;
    u8 *vertex_group;
    s32 intensity;
    MenuLineG4 *quad;
    s32 random_value;
    s32 random_color;

    intensity = ((Rec_D_80100B70 *)effect)->unk_10;
    scratch->order_table.bytes = &(*render_ctx_addr)->orderTag;
    do {
        GpuContext *render_ctx = *render_ctx_addr;
        u8 *draw_mode;
        vertex_group = effect + (vertex_index * 4);

        quad = render_ctx->packetCursor;
        render_ctx->packetCursor = (u8 *)(quad + 1);
        random_value = rand();
        quad->vertices[0].color.word = (random_value * rand()) & rgb_mask;
        random_value = rand();
        quad->vertices[1].color.word = (random_value * rand()) & rgb_mask;
        random_value = rand();
        quad->vertices[2].color.word = (random_value * rand()) & rgb_mask;
        random_value = rand();
        random_color = random_value * rand();
        quad->vertices[3].color.word = random_color & rgb_mask;

        quad->vertices[0].color.c.r = SCALE255(quad->vertices[0].color.c.r * intensity);
        quad->vertices[0].color.c.g = SCALE255(quad->vertices[0].color.c.g * intensity);
        quad->vertices[0].color.c.b = SCALE255(quad->vertices[0].color.c.b * intensity);
        quad->vertices[1].color.c.r = SCALE255(quad->vertices[1].color.c.r * intensity);
        quad->vertices[1].color.c.g = SCALE255(quad->vertices[1].color.c.g * intensity);
        quad->vertices[1].color.c.b = SCALE255(quad->vertices[1].color.c.b * intensity);
        quad->vertices[2].color.c.r = SCALE255(quad->vertices[2].color.c.r * intensity);
        quad->vertices[2].color.c.g = SCALE255(quad->vertices[2].color.c.g * intensity);
        quad->vertices[2].color.c.b = SCALE255(quad->vertices[2].color.c.b * intensity);
        quad->vertices[3].color.c.r = quad->vertices[0].color.c.r;
        quad->vertices[3].color.c.g = quad->vertices[0].color.c.g;
        quad->vertices[3].color.c.b = quad->vertices[0].color.c.b;
        SetLineG4(quad);
        SetSemiTrans(quad, 1);

        copy_odd_halfwords_3(scratch->vertices[0], ((ObjectPayloadView *)(((S_800A1354_4 *)vertex_group)->unk_54))->unk_08);
        copy_odd_halfwords_3(scratch->vertices[1], ((ObjectPayloadView *)(((S_800A1354_4 *)vertex_group)->unk_58))->unk_08);
        copy_odd_halfwords_3(scratch->vertices[2], ((ObjectPayloadView *)(((S_800A1354_4 *)vertex_group)->unk_5C))->unk_08);
        copy_menu_vector_halfwords(scratch->vertices[3], scratch->vertices[0]);
        scratch->depth = RotTransPers4(
            scratch->vertices[0], scratch->vertices[1], scratch->vertices[2], scratch->vertices[3], scratch->screen[0], scratch->screen[1],
            scratch->screen[2], scratch->screen[3], &scratch->interp, &scratch->flag) - 0x30;

        quad->vertices[0].x = scratch->screen[0][0];
        quad->vertices[0].y = scratch->screen[0][1];
        quad->vertices[1].x = scratch->screen[1][0];
        quad->vertices[1].y = scratch->screen[1][1];
        quad->vertices[2].x = scratch->screen[2][0];
        quad->vertices[2].y = scratch->screen[2][1];
        quad->vertices[3].x = scratch->screen[3][0];
        quad->vertices[3].y = scratch->screen[3][1];
        if (scratch->depth >= 0x1E0)
            scratch->depth = 0x1DF;
        if (scratch->depth < 0)
            scratch->depth = 0;
        AddPrim(scratch->order_table.bytes + scratch->depth * 4, quad);
        vertex_index += 3;
        render_ctx = *render_ctx_addr;
        draw_mode = render_ctx->packetCursor;
        render_ctx->packetCursor = draw_mode + 0xC;
        SetDrawMode(draw_mode, 1, 0, GetTPage(0, 1, 0x140, 0), 0);
        AddPrim(scratch->order_table.bytes + scratch->depth * 4, draw_mode);
    } while (vertex_index < 6);
}
