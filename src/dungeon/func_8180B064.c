#include "modules/dungeon_ovl_1829800.h"
#define S16(b, o) (*(s16 *)((u8 *)(b) + (o)))
#define U16(b, o) (*(u16 *)((u8 *)(b) + (o)))
#define S32(b, o) (*(s32 *)((u8 *)(b) + (o)))
s32 dungeonRenderThreeByThreeTerrainGrid(Objects *objects, ViewPosition *view_position, RenderParams *render_params)
{
    s16 saved_rotation[4];
    s16 saved_position[4];
    u8 *materials;
    s32 col;
    s32 row;
    s32 cell_index;
    Geometry *geometry;
    Vert *vertices;
    RenderState *render_state;
    Cell *cells;
    Scratch *scratch;
    DrawBuffer *draw_buffer;
    DrawBuffer *active_buffer;
    Prim *prim;
    Face *face;
    SpriteData *sprite_data;
    Object *main_object;
    Object *main_entry;
    Object *extra_entry;
    Object *extra_object;
    Sprite *sprite;
    u32 x1_shifted;
    s32 x1_masked;
    u32 packed2;
    u32 x3;
    u32 x3_shifted;
    u32 x3_masked;
    u32 packed3;
    u32 vert0_ref;
    s16 height0;
    s32 height1;
    s32 height2;
    s32 height3;
    s32 cell_x;
    s32 object_index;
    s32 depth;
    u32 vert3_ref_y;
    u32 vert1_ref_y;
    u32 vert2_y;
    s32 vert0_y;
    u32 y1_high;
    u32 y3_high;
    u32 y2_high;
    u32 height_bias;
    s32 vert3_y;

    geometry = (Geometry *)&D_8008333C[0];
    vertices = geometry->vertices;
    materials = geometry->materials;
    func_800649A0();
    {
        union { s32 value; } cell_y = {0};
        cell_y.value = -0x60;
        scratch = (Scratch *)0x1F800000;
        scratch->view_w = render_params->width;
        scratch->view_h = render_params->height;
        scratch->view_mid = (s32) (render_params->width + render_params->height) >> 1;
        render_state = (RenderState *)&gameWork;
        cells = &D_80027120[0];
        scratch->eye[0] = view_position->x;
        scratch->eye[1] = view_position->y;
        scratch->eye[2] = view_position->z;
        func_80064B90(scratch->matrix, &scratch->eye[0]);
        func_80065820(render_params->rotation, scratch->matrix);
        func_80064BC0(scratch->matrix, &scratch->view_w);
        func_80064CF0(scratch->matrix);
        func_80064D80(scratch->matrix);
        draw_buffer = render_state->draw_buffer;
        scratch->ot = (s32) draw_buffer->ot;
        prim = draw_buffer->prim;
        scratch->xy0 = 0;
        scratch->h0 = 0;
        scratch->depth_base = func_80065420(&scratch->xy0, scratch->buf, &scratch->out0, &scratch->out1) - 0x27;
        row = 0;
        cell_index = 0;
        do {
            union { u32 value; } mesh_index = {0};
            union { u32 value; } packed0 = {0};
            union { u32 value; } x1 = {0};
            union { u32 value; } packed1 = {0};
            union { u32 value; } vert0_addr = {0};
            union { u32 value; } vert1_addr = {0};
            union { u32 value; } vert2_addr = {0};
            union { u32 value; } vert2_ref = {0};
            union { u32 value; } vert3_addr = {0};
            union { u32 value; } index1 = {0};
            union { u32 value; } index1_xy = {0};
            union { u32 value; } index2 = {0};
            union { u32 value; } index3 = {0};
            union { u32 value; } y0_high = {0};
            union { s32 value; } facing = {0};
            cell_x = -0x60;
            col = 0;
            do {
                mesh_index.value = D_80027120[cell_index].idx;
                if (mesh_index.value != 0) {
                    face = geometry->faces[mesh_index.value];
                    for (;;) {
                        vert0_addr.value = face->i0 * 8 + (u32)vertices;
                        packed0.value = ((Vert *)vert0_addr.value)->x;
                        packed0.value = packed0.value + cell_x;
                        packed0.value = packed0.value & 0xFFFF;
                        vert0_y = ((Vert *)vert0_addr.value)->y;
                        y0_high.value = (cell_y.value + vert0_y) << 0x10;
                        packed0.value = packed0.value | y0_high.value;
                        S32(scratch, 0x70) = packed0.value;
                        vert2_ref.value = U16((u8 *)face, 4);
                        vert3_ref_y = U16((u8 *)face, 6);
                        vert0_ref = U16((u8 *)face, 0);
                        index1_xy.value = face->i1;
                        vert1_ref_y = index1_xy.value * 8 + (u32)vertices;
                        x1.value = U16((u8 *)vert1_ref_y, 0);
                        vert1_ref_y = ((Vert *)vert1_ref_y)->y;
                        vert2_ref.value = vert2_ref.value << 3;
                        vert2_ref.value = vert2_ref.value + (u32)vertices;
                        vert3_ref_y = vert3_ref_y << 3;
                        vert3_ref_y = vert3_ref_y + (u32)vertices;
                        vert0_ref = vert0_ref * 8;
                        vert0_ref = vert0_ref + (u32)vertices;
                        x1_shifted = x1.value + cell_x;
                        x1_shifted &= 0xFFFF;
                        x1_masked = (u16)x1_shifted;
                        y1_high = (cell_y.value + vert1_ref_y) << 0x10;
                        packed1.value = x1_masked | y1_high;
                        packed2 = ((Vert *)vert2_ref.value)->x;
                        vert2_y = ((Vert *)vert2_ref.value)->y;
                        x3 = ((Vert *)vert3_ref_y)->x;
                        height0 = ((Vert *)vert0_ref)->w;
                        height_bias = D_80027120[cell_index].bias;
                        height0 = height0 - height_bias;
                        vert3_ref_y += 2;
                        vert3_y = S16((u8 *)vert3_ref_y, 0);
                        packed2 = packed2 + cell_x;
                        packed2 = packed2 & 0xFFFF;
                        y2_high = (cell_y.value + vert2_y) << 0x10;
                        packed2 = packed2 | y2_high;
                        x3_shifted = x3 + cell_x;
                        x3_masked = x3_shifted & 0xFFFF;
                        scratch->h0 = height0;
                        index1.value = face->i1;
                        vert1_addr.value = index1.value * 8 + (u32)vertices;
                        y3_high = (cell_y.value + vert3_y) << 0x10;
                        height1 = U16((u8 *)vert1_addr.value, 4);
                        S32(scratch, 0x78) = packed1.value;
                        height1 = height1 - D_80027120[cell_index].bias;
                        scratch->h1 = height1;
                        index2.value = U16((u8 *)face, 4);
                        vert2_addr.value = index2.value * 8 + (u32)vertices;
                        height2 = ((Vert *)vert2_addr.value)->w;
                        S32(scratch, 0x80) = packed2;
                        height2 = height2 - D_80027120[cell_index].bias;
                        scratch->h2 = height2;
                        index3.value = face->i3;
                        vert3_addr.value = index3.value * 8 + (u32)vertices;
                        packed3 = x3_masked | y3_high;
                        scratch->xy3 = packed3;
                        height3 = ((Vert *)vert3_addr.value)->w;
                        height3 = height3 - D_80027120[cell_index].bias;
                        scratch->h3 = height3;
                        facing.value = func_800656C0(&scratch->xy0, &scratch->xy1, &scratch->xy2, &scratch->xy3,
                                          &prim->xy0, &prim->xy1, &prim->xy2, &prim->xy3,
                                          &scratch->out0, &scratch->depth, &scratch->out1);
                        scratch->facing = facing.value;
                        if (facing.value > 0) {
                            depth = scratch->depth - scratch->depth_base;
                            scratch->depth = depth;
                            if ((u32) (depth - 1) < 0x1DF) {
                                func_80065034(materials + face->tex * 8, render_state->blend, prim->rgb);
                                prim->a = face->a;
                                prim->b = face->b;
                                prim->u2 = face->u2;
                                prim->u3 = face->u3;
                                if (render_params->color[0] != 0x80) {
                                    prim->rgb[0] = (prim->rgb[0] * render_params->color[0]) >> 7;
                                    prim->rgb[1] = (prim->rgb[1] * render_params->color[1]) >> 7;
                                    prim->rgb[2] = (prim->rgb[2] * render_params->color[2]) >> 7;
                                }
                                prim->code = 9;
                                func_8006658C(scratch->ot + scratch->depth * 4, prim);
                                prim += 1;
                            }
                        }
                        if ((face->flags & 0x80FF) == 0x8001) {
                            break;
                        }
                        face += 1;
                    }
                }
                cells[cell_index].bias = 0;
                cell_x += 0x40;
                col += 1;
                cell_index += 1;
            } while (col < 3);
            cell_y.value += 0x40;
            row += 1;
        } while (row < 3);

        active_buffer = render_state->draw_buffer;
        active_buffer->prim = prim;
        saved_rotation[0] = render_state->rotation[0];
        saved_rotation[1] = render_state->rotation[1];
        saved_rotation[2] = render_state->rotation[2];
        saved_position[0] = render_state->position[0];
        saved_position[1] = render_state->position[1];
        saved_position[2] = render_state->position[2];
        render_state->position[0] = 0;
        render_state->position[1] = 0;
        render_state->position[2] = 0;
        render_state->rotation[0] = render_params->rotation[0];
        render_state->rotation[1] = render_params->rotation[1];
        render_state->rotation[2] = render_params->rotation[2];

        if (objects->main != 0) {
            scratch->clear = 0;
            main_object = objects->main;
            func_800453E0(main_object->transform, main_object->lo, main_object->hi, (s16) scratch->depth_base);
            main_entry = objects->main;
            D_8002713A[0] = -2;
            dungeonSetNegatedCoordinateScratch(main_entry->lo, main_entry->hi, -2, scratch->depth_base);
        }
        object_index = 0;
        do {
            if (objects->extra[object_index] != 0) {
                scratch->clear = 0;
                extra_object = objects->extra[object_index];
                func_800453E0(extra_object->transform, extra_object->lo, extra_object->hi, (s16) scratch->depth_base);
                extra_entry = objects->extra[object_index];
                dungeonSetNegatedCoordinateScratch(extra_entry->lo, extra_entry->hi, 0, scratch->depth_base);
            }
            object_index += 1;
        } while (object_index < 2);

        sprite = objects->sprite;
        if (sprite != 0) {
            sprite_data = sprite->data;
            if (!(sprite_data->flags & 0x80)) {
                func_80045CC4(sprite->transform, sprite->lo, sprite_data, (s16) scratch->depth_base);
            }
        }
        render_state->position[0] = saved_position[0];
        render_state->position[1] = saved_position[1];
        render_state->position[2] = saved_position[2];
        render_state->rotation[0] = saved_rotation[0];
        render_state->rotation[1] = saved_rotation[1];
        render_state->rotation[2] = saved_rotation[2];
        func_80064A40();
        return 0;
    }
}
