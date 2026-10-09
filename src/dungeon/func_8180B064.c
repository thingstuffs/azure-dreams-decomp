#include "common.h"

#define S16(b, o) (*(s16 *)((u8 *)(b) + (o)))
#define U16(b, o) (*(u16 *)((u8 *)(b) + (o)))
#define S32(b, o) (*(s32 *)((u8 *)(b) + (o)))

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad1;
    s16 y;
    s16 pad2;
    s16 z;
} ViewPosition;

typedef struct {
    u8 pad0[0xC];
    u8 color[3];
    u8 pad1[7];
    u16 rotation[3];
    u16 width;
    u16 height;
} RenderParams;

typedef struct {
    u8 pad0[3];
    u8 code;
    u8 rgb[3];
    u8 pad1;
    s32 xy0;
    s32 a;
    s32 xy1;
    s32 b;
    s32 xy2;
    u16 u2;
    u16 pad2;
    s32 xy3;
    u16 u3;
    u16 pad3;
} Prim;

typedef struct {
    u8 pad0[0xB0];
    u8 ot[0x820];
    Prim *prim;
} DrawBuffer;

typedef struct {
    DrawBuffer *draw_buffer;
    u8 pad0[0xA4];
    u8 blend[0xC];
    u16 position[3];
    u8 pad1[0xA];
    u16 rotation[3];
} RenderState;

typedef struct {
    u16 i0;
    u16 i1;
    u16 i2;
    u16 i3;
    s32 a;
    s32 b;
    u16 tex;
    u16 u2;
    u16 u3;
    u16 flags;
} Face;

typedef struct {
    u16 x;
    s16 y;
    u16 w;
    u16 pad;
} Vert;

typedef struct {
    u16 idx;
    u16 bias;
    u16 pad;
} Cell;

typedef struct {
    u8 pad0[4];
    Face **faces;
    Vert *vertices;
    u8 *materials;
} Geometry;

typedef struct {
    u8 pad0[8];
    s32 lo;
    s32 hi;
    u8 pad1[0x10];
    u8 transform[1];
} Object;

typedef struct {
    u8 pad0[0x14];
    u16 flags;
} SpriteData;

typedef struct {
    u8 pad0[8];
    s32 lo;
    SpriteData *data;
    u8 pad1[0x10];
    u8 transform[1];
} Sprite;

typedef struct {
    u8 pad0[8];
    Object *main;
    Object *extra[2];
    Sprite *sprite;
} Objects;

typedef struct {
    u8 pad0[0x20];
    s32 ot;
    u8 pad1[0xC];
    s32 view_w;
    s32 view_h;
    s32 view_mid;
    u8 pad2[4];
    s32 eye[3];
    u8 pad3[4];
    u8 matrix[0x20];
    s32 xy0;
    s16 h0;
    s16 pad4;
    s32 xy1;
    s16 h1;
    s16 pad5;
    s32 xy2;
    s16 h2;
    s16 pad6;
    s32 xy3;
    s16 h3;
    s16 pad7;
    s32 out0;
    s32 out1;
    u8 pad8[0x28];
    s32 depth;
    s32 depth_base;
    u8 pad9[0x28];
    u8 buf[0x24];
    s32 facing;
    u8 pad10[0x24];
    s32 clear;
} Scratch;

extern Cell D_80027120[];
extern s16 D_8002713A[];
extern s8 D_80083160[];
extern s8 D_8008333C[];

extern void func_800649A0();
extern void func_80064B90();
extern void func_80065820();
extern void func_80064BC0();
extern void func_80064CF0();
extern void func_80064D80();
extern s32 func_80065420();
extern s32 func_800656C0();
extern void func_80065034();
extern void func_8006658C();
extern void func_800453E0();
extern void func_80045CC4();
extern void func_80026F1C();
extern void func_80064A40();

/* Render a 3x3 grid of terrain faces and its associated objects. */
s32 func_80026864(Objects *objects, ViewPosition *view_position, RenderParams *render_params)
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
    u32 packed0;
    u32 x1;
    u32 x1_shifted;
    s32 x1_masked;
    u32 packed1;
    u32 packed2;
    u32 x3;
    u32 x3_shifted;
    u32 x3_masked;
    u32 packed3;
    u32 vert0_ref;
    u32 index1;
    u32 index2;
    u32 index3;
    s16 height0;
    s32 height1;
    s32 height2;
    s32 height3;
    s32 cell_x;
    s32 cell_y;
    s32 facing;
    s32 object_index;
    s32 depth;
    u32 mesh_index;
    u32 index1_xy;
    u32 vert2_ref;
    u32 vert3_ref_y;
    u32 vert0_addr;
    u32 vert1_ref_y;
    u32 vert2_y;
    s32 vert0_y;
    u32 y0_high;
    u32 y1_high;
    u32 y3_high;
    u32 vert1_addr;
    u32 vert2_addr;
    u32 vert3_addr;
    u32 y2_high;
    u32 height_bias;
    s32 vert3_y;

    geometry = (Geometry *)&D_8008333C[0];
    vertices = geometry->vertices;
    materials = geometry->materials;
    func_800649A0();
    cell_y = -0x60;
    scratch = (Scratch *)0x1F800000;
    scratch->view_w = render_params->width;
    scratch->view_h = render_params->height;
    scratch->view_mid = (s32) (render_params->width + render_params->height) >> 1;
    render_state = (RenderState *)&D_80083160[0];
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
        cell_x = -0x60;
        col = 0;
        do {
            mesh_index = D_80027120[cell_index].idx;
            if (mesh_index != 0) {
                face = geometry->faces[mesh_index];
                for (;;) {
                    vert0_addr = face->i0 * 8 + (u32)vertices;
                    packed0 = ((Vert *)vert0_addr)->x;
                    packed0 = packed0 + cell_x;
                    packed0 = packed0 & 0xFFFF;
                    vert0_y = ((Vert *)vert0_addr)->y;
                    y0_high = (cell_y + vert0_y) << 0x10;
                    packed0 = packed0 | y0_high;
                    S32(scratch, 0x70) = packed0;
                    vert2_ref = U16((u8 *)face, 4);
                    vert3_ref_y = U16((u8 *)face, 6);
                    vert0_ref = U16((u8 *)face, 0);
                    index1_xy = face->i1;
                    vert1_ref_y = index1_xy * 8 + (u32)vertices;
                    x1 = U16((u8 *)vert1_ref_y, 0);
                    vert1_ref_y = ((Vert *)vert1_ref_y)->y;
                    vert2_ref = vert2_ref << 3;
                    vert2_ref = vert2_ref + (u32)vertices;
                    vert3_ref_y = vert3_ref_y << 3;
                    vert3_ref_y = vert3_ref_y + (u32)vertices;
                    vert0_ref = vert0_ref * 8;
                    vert0_ref = vert0_ref + (u32)vertices;
                    x1_shifted = x1 + cell_x;
                    x1_shifted &= 0xFFFF;
                    x1_masked = (u16)x1_shifted;
                    y1_high = (cell_y + vert1_ref_y) << 0x10;
                    packed1 = x1_masked | y1_high;
                    packed2 = ((Vert *)vert2_ref)->x;
                    vert2_y = ((Vert *)vert2_ref)->y;
                    x3 = ((Vert *)vert3_ref_y)->x;
                    height0 = ((Vert *)vert0_ref)->w;
                    height_bias = D_80027120[cell_index].bias;
                    height0 = height0 - height_bias;
                    vert3_ref_y += 2;
                    vert3_y = S16((u8 *)vert3_ref_y, 0);
                    packed2 = packed2 + cell_x;
                    packed2 = packed2 & 0xFFFF;
                    y2_high = (cell_y + vert2_y) << 0x10;
                    packed2 = packed2 | y2_high;
                    x3_shifted = x3 + cell_x;
                    x3_masked = x3_shifted & 0xFFFF;
                    scratch->h0 = height0;
                    index1 = face->i1;
                    vert1_addr = index1 * 8 + (u32)vertices;
                    y3_high = (cell_y + vert3_y) << 0x10;
                    height1 = U16((u8 *)vert1_addr, 4);
                    S32(scratch, 0x78) = packed1;
                    height1 = height1 - D_80027120[cell_index].bias;
                    scratch->h1 = height1;
                    index2 = U16((u8 *)face, 4);
                    vert2_addr = index2 * 8 + (u32)vertices;
                    height2 = ((Vert *)vert2_addr)->w;
                    S32(scratch, 0x80) = packed2;
                    height2 = height2 - D_80027120[cell_index].bias;
                    scratch->h2 = height2;
                    index3 = face->i3;
                    vert3_addr = index3 * 8 + (u32)vertices;
                    packed3 = x3_masked | y3_high;
                    scratch->xy3 = packed3;
                    height3 = ((Vert *)vert3_addr)->w;
                    height3 = height3 - D_80027120[cell_index].bias;
                    scratch->h3 = height3;
                    facing = func_800656C0(&scratch->xy0, &scratch->xy1, &scratch->xy2, &scratch->xy3,
                                      &prim->xy0, &prim->xy1, &prim->xy2, &prim->xy3,
                                      &scratch->out0, &scratch->depth, &scratch->out1);
                    scratch->facing = facing;
                    if (facing > 0) {
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
        cell_y += 0x40;
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
        func_80026F1C(main_entry->lo, main_entry->hi, -2, scratch->depth_base);
    }
    object_index = 0;
    ASM_USE_NV(vertices);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    do {
        if (objects->extra[object_index] != 0) {
            scratch->clear = 0;
            extra_object = objects->extra[object_index];
            func_800453E0(extra_object->transform, extra_object->lo, extra_object->hi, (s16) scratch->depth_base);
            extra_entry = objects->extra[object_index];
            func_80026F1C(extra_entry->lo, extra_entry->hi, 0, scratch->depth_base);
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

