#include "engine/graphics/lit_mesh.h"
#include "shared/gpu_packets.h"
#include "shared/entity.h"
#include "shared/vector.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/game_work.h"

#include "common.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"

typedef struct {
    u8 pad0[8];
    s32 meshIndex;
    u8 padC[4];
    u16 colour;
    u16 texture;
    u16 flags;
    s16 rotation[3];
    u16 scale[3];
} RenderObject;

extern void NormalColorCol(void *a0, void *a1, void *a2);

/* Transform, light, and queue visible textured mesh quads for rendering. */
void draw_lit_mesh(void *unused, u8 *position_arg, RenderObject *object, s16 depth_bias)
{
    Fixed1616 *position = position_arg;
    GteMatrix view_matrix;
    GameWork *render_globals;
    Vertex *vertex_table;
    u8 *normal_table;
    GpuContext *render_state;
    LitMeshFace *face;
    LitMeshQuadPacket *prim;
    RenderScratch *scratch;
    u32 vertex_word;
    u16 index_b;
    u16 index_c;
    u16 vertex_index;
    unsigned long vertex_data;
    void *vertex_0;
    void *vertex_1;
    s32 clip_xy_0;
    s32 clip_xy_1;
    s32 clip_xy_2;
    s32 flip_flags;
    s32 depth_offset;
    u16 flags;
    u16 colour;
    u32 depth;

    render_globals = &g_game_work;
    vertex_table = render_globals->map.vertices;
    normal_table = render_globals->map.surface_planes;

    PushMatrix();

    vertex_word = *&object->scale[0];
    scratch = (RenderScratch *)0x1F800000;

    scratch->scale[0] = vertex_word;
    scratch->scale[1] = object->scale[1];
    scratch->scale[2] = object->scale[2];
    scratch->translation[0] = position[0].w.i;
    scratch->translation[1] = position[1].w.i;
    scratch->translation[2] = position[2].w.i;

    ReadRotMatrix(&view_matrix);
    vertex_0 = scratch;
    vertex_0 = (void *)((unsigned long)vertex_0 | 0x50);
    vertex_1 = scratch;
    vertex_1 = (void *)((unsigned long)vertex_1 | 0x40);
    TransMatrix(vertex_0, vertex_1);
    vertex_0 = &object->rotation[0];
    vertex_1 = scratch;
    vertex_1 = (void *)((unsigned long)vertex_1 | 0x50);
    RotMatrix(vertex_0, vertex_1);

    if (object->flags & 1) {
        scratch->scale[0] = -scratch->scale[0];
    }
    if (object->flags & 2) {
        scratch->scale[1] = -scratch->scale[1];
    }

    ScaleMatrix((void *)0x1F800050, (void *)0x1F800030);
    CompMatrix(&view_matrix, (void *)0x1F800050, (void *)0x1F8000D0);
    SetTransMatrix((void *)0x1F8000D0);
    SetRotMatrix((void *)0x1F8000D0);

    depth_offset = depth_bias;
    render_state = g_game_work.draw_buffer;
    scratch->ordering_table = &render_state->orderTag;
    prim = render_state->packetCursor;
    object->flags |= 0x8000;

    face = *(LitMeshFace **)(*(u8 **)&render_globals->map.cell_faces + object->meshIndex * 4);

    for (;;) {
        vertex_data = vertex_table[face->vertex_indices[0]].value;
        index_b = face->vertex_indices[1];
        scratch->vertices[0].xy = vertex_data;
        vertex_data = vertex_table[index_b].value;
        index_c = face->vertex_indices[2];
        scratch->vertices[1].xy = vertex_data;
        vertex_data = face->vertex_indices[3];
        vertex_data = (vertex_data << 3) + (unsigned long)vertex_table;
        scratch->vertices[2].xy = vertex_table[index_c].value;
        vertex_data = ((Vertex *)vertex_data)->value;
        scratch->vertices[0].z = vertex_table[face->vertex_indices[0]].depth;
        scratch->vertices[1].z = vertex_table[face->vertex_indices[1]].depth;
        scratch->vertices[2].z = vertex_table[face->vertex_indices[2]].depth;
        vertex_index = face->vertex_indices[3];
        scratch->vertices[3].xy = vertex_data;
        vertex_data = vertex_table[vertex_index].depth;
        scratch->vertices[3].z = vertex_data;

        scratch->depth = RotAverage4(
            &scratch->vertices[0],
            &scratch->vertices[1],
            &scratch->vertices[2],
            &scratch->vertices[3],
            &prim->xy0,
            &prim->xy1,
            &prim->xy2,
            &prim->xy3,
            (u8 *)scratch + 0x90,
            (u8 *)scratch + 0x94);

        flip_flags = object->flags & 3;
        switch (flip_flags) {
        case 0:
            clip_xy_0 = prim->xy0;
            clip_xy_1 = prim->xy1;
            clip_xy_2 = prim->xy2;
            scratch->clip = NormalClip(clip_xy_0, clip_xy_1, clip_xy_2);
            break;
        case 1:
            clip_xy_0 = prim->xy1;
            clip_xy_1 = prim->xy0;
            clip_xy_2 = prim->xy3;
            scratch->clip = NormalClip(clip_xy_0, clip_xy_1, clip_xy_2);
            break;
        case 2:
            clip_xy_0 = prim->xy3;
            clip_xy_1 = prim->xy2;
            clip_xy_2 = prim->xy1;
            scratch->clip = NormalClip(clip_xy_0, clip_xy_1, clip_xy_2);
            break;
        default:
            clip_xy_0 = prim->xy2;
            clip_xy_1 = prim->xy3;
            clip_xy_2 = prim->xy0;
            scratch->clip = NormalClip(clip_xy_0, clip_xy_1, clip_xy_2);
            break;
        }

        if (scratch->clip > 0) {
            depth = scratch->depth - depth_offset;
            scratch->depth = depth;
            if (depth < 0x1E0U) {
                NormalColorCol(
                    normal_table + face->normal_index * 8,
                    (u8 *)object + 0xC,
                    prim->color);

                prim->uv_clut.word = face->uv_clut;
                prim->uv_clut.halves.clut += object->texture;
                prim->uv_page.word = face->uv_page;

                colour = object->colour;
                if (colour != 0) {
                    prim->uv_page.halves.page = colour + (prim->uv_page.halves.page & 0xFF9F);
                }

                prim->uv2 = face->uv2;
                prim->uv3 = face->uv3;
                SetPolyFT4(prim);

                flags = object->flags;
                if (flags & 8) {
                    if (flags & 4) {
                        prim->command |= 2;
                    }
                }

                AddPrim((u8 *)scratch->ordering_table + scratch->depth * 4, prim);
                prim++;
                object->flags &= 0x7FFF;
            }
        }

        if (face->unk_16 == 1 && face->unk_17 < 0) {
            break;
        }
        face++;
    }

    PopMatrix();
    ((GpuContext *)render_globals->draw_buffer)->packetCursor = prim;
}
