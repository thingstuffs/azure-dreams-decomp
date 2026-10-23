/* Transforms vectors and mesh quads and queues quads with randomized vertex colors. */
/* inferred-strong G00591: mesh_quad_transform_g00591; joins CL:town/func_800AC7B4,CL:town/func_800AC8E4,CL:town/func_800AC908,CL:town/func_800AC9AC,PD:town/engine:80100D18,PD:town/engine:80100D1C,PD:town/engine:80100D40; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC7B4, CL:town/func_800AC8E4, CL:town/func_800AC908, CL:town/func_800AC9AC, PD:town/engine:80100D18, PD:town/engine:80100D1C, PD:town/engine:80100D40. */
#include "town/event/mesh_quad_transform_g00591.h"

/* Copies three spaced halfwords into contiguous fields. */
void copy_even_halfwords_3(S_800AA044_0 *dst, S_800AA044_1 *src) {
    dst->unk_00 = (u16) src->unk_00;
    dst->unk_02 = (u16) src->unk_04;
    dst->unk_04 = (u16) src->unk_08;
}

/* Apply rotation, scale, and translation to a vector and copy the result back. */
void transform_vector(s32 transform, void *vector, void *transformed) {
    s32 flags;

    TransMatrix(0x1F800054, &D_800D11C0);
    RotMatrix(transform + 8, 0x1F800054);
    ScaleMatrix(0x1F800054, transform + 0x10);
    SetRotMatrix(0x1F800054);
    SetTransMatrix(0x1F800054);
    RotTrans(vector, transformed, &flags);
    copy_even_halfwords_3(vector, transformed);
}

/* Transform and queue mesh quads with randomized vertex colors. */
void transform_and_queue_mesh_quads(S_func_800AC9AC_0 *mesh, void *transform)
{
    S_func_800AC9AC_1 *scratch;
    u8 *initial_state;
    u8 *vertices;
    u32 *color_masks;
    s16 *quad_indices;
    u8 *vertex_0;
    u8 *vertex_1;
    u8 *vertex_2;
    u8 *vertex_3;
    u8 *vertex_work;
    S_func_800AC9AC_2 *render_state;
    u8 **render_state_ptr;
    S_func_800AC9AC_3 *quad;
    u32 *draw_mode;
    s32 random_factor;
    u32 address_mask;
    u32 length_mask;

    quad_indices = mesh->unk_04;
    vertices = mesh->unk_00;
    render_state_ptr = ((u8 * *)(&g_game_work));
    initial_state = *render_state_ptr;
    color_masks = mesh->unk_20;
    scratch = (S_func_800AC9AC_1 *)0x1F800000;
    scratch->unk_24 = (u32 *)(initial_state + 0xB0);

    if (*quad_indices != -1) {
        vertex_0 = (u8 *)scratch + 0x74;
        vertex_1 = (u8 *)scratch + 0x7C;
        vertex_2 = (u8 *)scratch + 0x84;
        vertex_3 = (u8 *)scratch + 0x8C;
        vertex_work = (u8 *)scratch + 0x44;
        address_mask = 0x00FFFFFF;

        do {
            render_state = (S_func_800AC9AC_2 *)*render_state_ptr;
            quad = render_state->unk_8D0;
            render_state->unk_8D0 = (u8 *)quad + 0x28;

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

            copy_menu_vector_halfwords(vertex_0, vertices + (quad_indices[0] * 8));
            copy_menu_vector_halfwords(vertex_1, vertices + (quad_indices[1] * 8));
            copy_menu_vector_halfwords(vertex_2, vertices + (quad_indices[2] * 8));
            copy_menu_vector_halfwords(vertex_3, vertices + (quad_indices[3] * 8));

            PushMatrix();
            transform_vector((s32)mesh, vertex_0, vertex_work);
            transform_vector((s32)mesh, vertex_1, vertex_work);
            transform_vector((s32)mesh, vertex_2, vertex_work);
            transform_vector((s32)mesh, vertex_3, vertex_work);
            PopMatrix();

            add_entity_position_to_menu_vector(vertex_0, transform);
            add_entity_position_to_menu_vector(vertex_1, transform);
            add_entity_position_to_menu_vector(vertex_2, transform);
            add_entity_position_to_menu_vector(vertex_3, transform);

            scratch->unk_C4 = RotTransPers4(
                vertex_0, vertex_1, vertex_2, vertex_3,
                &scratch->unk_E8, &scratch->unk_EC,
                &scratch->unk_F0, &scratch->unk_F4,
                (u8 *)scratch + 0x94, (u8 *)scratch + 0x98) - 0x30;

            quad->unk_08 = scratch->unk_E8;
            quad->unk_0A = scratch->unk_EA;
            quad->unk_10 = scratch->unk_EC;
            quad->unk_12 = scratch->unk_EE;
            quad->unk_18 = scratch->unk_F0;
            quad->unk_1A = scratch->unk_F2;
            quad->unk_20 = scratch->unk_F4;
            quad->unk_22 = scratch->unk_F6;

            if (scratch->unk_C4 >= 0x1E0)
                scratch->unk_C4 = 0x1DF;
            if (scratch->unk_C4 < 0)
                scratch->unk_C4 = 0;

            render_state = (S_func_800AC9AC_2 *)*render_state_ptr;
            draw_mode = render_state->unk_8D0;
            render_state->unk_8D0 = (u8 *)draw_mode + 0xC;
            SetDrawMode(draw_mode, 1, 0,
                          (u16)GetTPage(0, 0, 0x140, 0), 0);

            length_mask = 0xFF000000;
            draw_mode[0] = (draw_mode[0] & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)draw_mode & address_mask);
            quad->unk_00 = (quad->unk_00 & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)quad & address_mask);

            render_state = (S_func_800AC9AC_2 *)*render_state_ptr;
            draw_mode = render_state->unk_8D0;
            render_state->unk_8D0 = (u8 *)draw_mode + 0xC;
            SetDrawMode(draw_mode, 1, 0,
                          (u16)GetTPage(0, 1, 0x140, 0), 0);

            length_mask = 0xFF000000;
            quad_indices += 4;
            draw_mode[0] = (draw_mode[0] & length_mask) | (OTSLOT() & address_mask);
            OTSLOT() = (OTSLOT() & length_mask) | ((u32)draw_mode & address_mask);
        } while (*quad_indices != -1);
    }
}
