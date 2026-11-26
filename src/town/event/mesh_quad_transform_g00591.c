#include "engine/graphics/sprite_scratch.h"
/* Transforms vectors and mesh quads and queues quads with randomized vertex colors. */
/* inferred-strong mesh_quad_transform_g00591; joins CL:town/func_800AC7B4,CL:town/func_800AC8E4,CL:town/func_800AC908,CL:town/func_800AC9AC,PD:town/engine:80100D18,PD:town/engine:80100D1C,PD:town/engine:80100D40; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC7B4, CL:town/func_800AC8E4, CL:town/func_800AC908, CL:town/func_800AC9AC, PD:town/engine:80100D18, PD:town/engine:80100D1C, PD:town/engine:80100D40. */
#include "town/event/mesh_quad_transform_g00591.h"
#include "shared/gpu_packets.h"
#include "town/event.h"

/* Copies three spaced halfwords into contiguous fields. */
void narrow_vector_to_svector(SVECTOR *dst, VECTOR *src) {
    dst->vx = src->vx;
    dst->vy = src->vy;
    dst->vz = src->vz;
}

/* Apply rotation, scale, and translation to a vector and copy the result back. */
void transform_vector(s32 transform, SVECTOR *vector, VECTOR *transformed) {
    s32 flags;

    TransMatrix(0x1F800054, &D_800D11C0);
    RotMatrix(transform + 8, 0x1F800054);
    ScaleMatrix(0x1F800054, transform + 0x10);
    SetRotMatrix(0x1F800054);
    SetTransMatrix(0x1F800054);
    RotTrans(vector, transformed, &flags);
    narrow_vector_to_svector(vector, transformed);
}

/* Transform and queue mesh quads with randomized vertex colors. */
void transform_and_queue_mesh_quads(S_func_800AC9AC_0 *mesh, Fixed1616 origin[3])
{
    SpriteLinkedScratch *scratch;
    GpuContext *initial_state;
    SVECTOR *vertices;
    u32 *color_masks;
    s16 *quad_indices;
    SVECTOR *vertex_0;
    SVECTOR *vertex_1;
    SVECTOR *vertex_2;
    SVECTOR *vertex_3;
    VECTOR *vertex_work;
    GpuContext *render_state;
    GameWork *render_state_ptr;
    S_func_800AC9AC_3 *quad;
    u32 *draw_mode;
    s32 random_factor;
    u32 address_mask;
    u32 length_mask;

    quad_indices = mesh->unk_04;
    vertices = mesh->vertices;
    render_state_ptr = &g_game_work;
    initial_state = render_state_ptr->draw_buffer;
    color_masks = mesh->unk_20;
    scratch = LINKED_SPRITE_SCRATCH;
    scratch->ordering_table = &initial_state->orderTag[GPU_ORDER_DEPTH_BASE];

    if (*quad_indices != -1) {
        vertex_0 = &scratch->vertices[0];
        vertex_1 = &scratch->vertices[1];
        vertex_2 = &scratch->vertices[2];
        vertex_3 = &scratch->vertices[3];
        vertex_work = &scratch->translation;
        address_mask = 0x00FFFFFF;

        do {
            render_state = render_state_ptr->draw_buffer;
            quad = render_state->packetCursor;
            render_state->packetCursor = (u8 *)quad + 0x28;

            random_factor = rand();
            quad->unk_04 = (random_factor * rand()) & color_masks[0];
            random_factor = rand();
            quad->unk_0C = (random_factor * rand()) & color_masks[1];
            random_factor = rand();
            quad->unk_14 = (random_factor * rand()) & color_masks[2];
            random_factor = rand();
            quad->unk_1C = (random_factor * rand()) & color_masks[3];

            SetLineG4(quad);
            SetSemiTrans(quad, 1);

            copy_menu_point(vertex_0, &vertices[quad_indices[0]]);
            copy_menu_point(vertex_1, &vertices[quad_indices[1]]);
            copy_menu_point(vertex_2, &vertices[quad_indices[2]]);
            copy_menu_point(vertex_3, &vertices[quad_indices[3]]);

            PushMatrix();
            transform_vector((s32)mesh, vertex_0, vertex_work);
            transform_vector((s32)mesh, vertex_1, vertex_work);
            transform_vector((s32)mesh, vertex_2, vertex_work);
            transform_vector((s32)mesh, vertex_3, vertex_work);
            PopMatrix();

            add_entity_position_to_menu_vector(vertex_0, origin);
            add_entity_position_to_menu_vector(vertex_1, origin);
            add_entity_position_to_menu_vector(vertex_2, origin);
            add_entity_position_to_menu_vector(vertex_3, origin);

            scratch->ordering_depth = RotTransPers4(
                vertex_0, vertex_1, vertex_2, vertex_3,
                (s32 *)&scratch->screen[0], (s32 *)&scratch->screen[1],
                (s32 *)&scratch->screen[2], (s32 *)&scratch->screen[3],
                &scratch->depth_cue, &scratch->gte_flag) - 0x30;

            quad->unk_08 = scratch->screen[0].x;
            quad->unk_0A = scratch->screen[0].y;
            quad->unk_10 = scratch->screen[1].x;
            quad->unk_12 = scratch->screen[1].y;
            quad->unk_18 = scratch->screen[2].x;
            quad->unk_1A = scratch->screen[2].y;
            quad->unk_20 = scratch->screen[3].x;
            quad->unk_22 = scratch->screen[3].y;

            if (scratch->ordering_depth >= 0x1E0)
                scratch->ordering_depth = 0x1DF;
            if (scratch->ordering_depth < 0)
                scratch->ordering_depth = 0;

            render_state = render_state_ptr->draw_buffer;
            draw_mode = render_state->packetCursor;
            render_state->packetCursor = (u8 *)draw_mode + 0xC;
            SetDrawMode(draw_mode, 1, 0,
                          (u16)GetTPage(0, 0, 0x140, 0), 0);

            length_mask = 0xFF000000;
            draw_mode[0] = (draw_mode[0] & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)draw_mode & address_mask);
            quad->unk_00 = (quad->unk_00 & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)quad & address_mask);

            render_state = render_state_ptr->draw_buffer;
            draw_mode = render_state->packetCursor;
            render_state->packetCursor = (u8 *)draw_mode + 0xC;
            SetDrawMode(draw_mode, 1, 0,
                          (u16)GetTPage(0, 1, 0x140, 0), 0);

            length_mask = 0xFF000000;
            quad_indices += 4;
            draw_mode[0] = (draw_mode[0] & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)draw_mode & address_mask);
        } while (*quad_indices != -1);
    }
}
