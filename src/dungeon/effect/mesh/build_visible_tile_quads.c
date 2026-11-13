#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect/mesh.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"

typedef struct S_800D1824_4 {
    u8 pad_00[0x8];
    u32 unk_08;
    u32 unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
} S_800D1824_4;   /* style in build_visible_tile_quads */

typedef struct S_800D1824_5 {
    u8 pad_00[0x10];
    u8 * unk_10;
} S_800D1824_5;   /* ((S_800D1824_1 *)globals)->unk_1E0 in build_visible_tile_quads */

   /* ((S_800D1824_1 *)globals)->unk_00 in build_visible_tile_quads */

/* Transform grid tiles into quads and add visible ones to the ordering table. */
void build_visible_tile_quads(MeshEffectObjectBody *tiles)
{
    SpriteQuadScratch *scratch = (SpriteQuadScratch *)0x1F800000;
    GameWork *globals = &g_game_work;
    S_800D1824_4 *style;
    POLY_FT4 *prim;
    GpuContext *render_state;
    s32 x;
    s32 y;
    s32 depth;
    s32 tri_depth;
    u16 z;

    /* BYTES: retail clears the normal's vx and vy with one sw of zero; member stores compile to two sh */
    *(s32 *)&scratch->rotation.vx = 0;
    render_state = globals->draw_buffer;
    style = (S_800D1824_4 *)((S_800D1824_5 *)globals->map.cell_faces)->unk_10;
    prim = render_state->packetCursor;
    scratch->rotation.vz = -0x1000;
    scratch->ordering_table = (u32 *)&render_state->orderTag;

    while (tiles->x != 0) {
        if (tiles->height != 0x8000) {
            x = (s32)tiles->x << 6;
            scratch->vertices[2].vx = x;
            scratch->vertices[0].vx = x;
            x += 0x40;
            scratch->vertices[3].vx = x;
            scratch->vertices[1].vx = x;

            y = (s32)tiles->y << 6;
            scratch->vertices[1].vy = y;
            scratch->vertices[0].vy = y;
            y += 0x40;
            scratch->vertices[3].vy = y;
            scratch->vertices[2].vy = y;

            z = tiles->height;
            scratch->vertices[2].vz = z;
            scratch->vertices[1].vz = z;
            scratch->vertices[0].vz = z;

            gte_ldv3(&scratch->vertices[0], &scratch->vertices[1], &scratch->vertices[2]);
            scratch->vertices[3].vz = tiles->height;
            gte_rtpt_nn();
            gte_nclip();
            gte_stopz(&scratch->winding);

            if (scratch->winding > 0) {
                gte_stsxy3_g3(prim);
                gte_avsz3();
                gte_stotz(&scratch->sort_depth);
                gte_ldv0(&scratch->vertices[3]);
                tri_depth = scratch->sort_depth;
                tri_depth = tri_depth * 3;
                scratch->sort_depth = tri_depth;

                gte_rtps_nn();
                gte_stszotz(&scratch->depth_offset);
                depth = ((s32)scratch->sort_depth +
                         scratch->depth_offset) >> 2;
                scratch->sort_depth = depth;

                if ((u32)depth < 0x1E0) {
                    gte_stsxy(&prim->x3);
                    NormalColorCol(&scratch->rotation, (CVECTOR *)&globals->view.tint, (CVECTOR *)&prim->r0);
                    /* BYTES: retail stores u0, v0 and the CLUT with one sw of the style word; member stores compile to sb, sb, sh */
                    *(u32 *)&prim->u0 = style->unk_08;
                    /* BYTES: retail stores u1, v1 and the texture page with one sw of the style word; member stores compile to sb, sb, sh */
                    *(u32 *)&prim->u1 = style->unk_0C;
                    /* BYTES: retail writes the packet u/v byte pair with one sh of the style halfword; storing u and v separately compiles to two sb */
                    *(u16 *)&prim->u2 = style->unk_12;
                    /* BYTES: retail writes the packet u/v byte pair with one sh of the style halfword; storing u and v separately compiles to two sb */
                    *(u16 *)&prim->u3 = style->unk_14;
                    ((GpuLinkTag *)&prim->tag)->len = 9;
                    AddPrim(scratch->ordering_table + scratch->sort_depth, prim);
                    prim++;
                }
            }
        }
        tiles++;
    }

    ((GpuContext *)globals->draw_buffer)->packetCursor = prim;
}
