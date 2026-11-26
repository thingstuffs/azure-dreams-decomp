#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect/mesh.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"
#include "engine/graphics/lit_mesh.h"

/* The first face in map slot four supplies the tile effect texture coordinates. */
/* Transform grid tiles into quads and add visible ones to the ordering table. */
void build_visible_tile_quads(MeshEffectObjectBody *tiles)
{
    SpriteQuadScratch *scratch = SPRITE_SCRATCH;
    GameWork *globals = &g_game_work;
    LitMeshFace *style;
    POLY_FT4 *prim;
    GpuContext *render_state;
    s32 x;
    s32 y;
    s32 depth;
    s32 tri_depth;
    u16 z;

    /* BYTES: Both normal components are cleared with one word store. Separate members produce two halfword stores. */
    *(s32 *)&scratch->rotation.vx = 0;
    render_state = globals->draw_buffer;
    style = globals->map.cell_faces[4];
    prim = render_state->packetCursor;
    scratch->rotation.vz = -0x1000;
    scratch->ordering_table = &render_state->orderTag[GPU_ORDER_DEPTH_BASE];

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
                    /* BYTES: The first UV pair and palette selector are stored together. Separate members split the style word into three stores. */
                    *(u32 *)&prim->u0 = style->uv_clut;
                    /* BYTES: The second UV pair and texture-page selector are stored together. Separate members split the style word into three stores. */
                    *(u32 *)&prim->u1 = style->uv_page;
                    /* BYTES: The packed style UV pair is stored together. Separate members generate two byte stores. */
                    *(u16 *)&prim->u2 = style->uv2;
                    /* BYTES: The packed style UV pair is stored together. Separate members generate two byte stores. */
                    *(u16 *)&prim->u3 = style->uv3;
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
