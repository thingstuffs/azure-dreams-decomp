#include "common.h"

#define U8(b, o)  (*(u8  *)((u8 *)(b) + (o)))
#define S16(b, o) (*(s16 *)((u8 *)(b) + (o)))
#define U16(b, o) (*(u16 *)((u8 *)(b) + (o)))
#define S32(b, o) (*(s32 *)((u8 *)(b) + (o)))
#define PTR(b, o) (*(u8 **)((u8 *)(b) + (o)))

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
s32 func_80026864(void *objects, void *view_position, void *render_params)
{
    s16 saved_rotation[4];
    s16 saved_position[4];
    u8 *materials;
    s32 col;
    s32 row;
    s32 cell_index;
    u8 *geometry;
    Vert *vertices;
    u8 *render_state;
    u8 *cells;
    u8 *scratch;
    u8 *draw_buffer;
    u8 *active_buffer;
    u8 *prim;
    Face *face;
    u8 *sprite_data;
    u8 *main_object;
    u8 *object_slot;
    u8 *main_entry;
    u8 *extra_entry;
    u8 *extra_object;
    u8 *sprite;
    u32 xy0;
    u32 xy1;
    u32 xy2;
    u32 xy3;
    u32 vert0_ref;
    u32 index1;
    u32 index2;
    u32 index3;
    s32 height0;
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

    geometry = (u8 *)&D_8008333C[0];
    vertices = (Vert *)PTR(geometry, 8);
    materials = PTR(geometry, 12);
    func_800649A0();
    cell_y = -0x60;
    scratch = (u8 *)0x1F800000;
    S32(scratch, 0x30) = U16(render_params, 0x1C);
    S32(scratch, 0x34) = U16(render_params, 0x1E);
    S32(scratch, 0x38) = (s32) (U16(render_params, 0x1C) + U16(render_params, 0x1E)) >> 1;
    render_state = (u8 *)&D_80083160[0];
    cells = (u8 *)&D_80027120[0];
    S32(scratch, 0x40) = S16(view_position, 2);
    S32(scratch, 0x44) = S16(view_position, 6);
    S32(scratch, 0x48) = S16(view_position, 0xA);
    func_80064B90(scratch + 0x50, scratch + 0x40);
    func_80065820((u8 *)render_params + 0x16, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064CF0(scratch + 0x50);
    func_80064D80(scratch + 0x50);
    draw_buffer = *(u8 **)render_state;
    S32(scratch, 0x20) = (s32) (draw_buffer + 0xB0);
    prim = PTR(draw_buffer, 0x8D0);
    S32(scratch, 0x70) = 0;
    S16(scratch, 0x74) = 0;
    S32(scratch, 0xC4) = func_80065420(scratch + 0x70, scratch + 0xF0, scratch + 0x90, scratch + 0x94) - 0x27;
    row = 0;
    cell_index = 0;
    do {
        cell_x = -0x60;
        col = 0;
        do {
            mesh_index = ((Cell *)((u8 *)&D_80027120[0] + cell_index * 6))->idx;
            if (mesh_index != 0) {
                face = ((Face **) PTR(geometry, 4))[mesh_index];
                for (;;) {
                    ASM_SET(vert2_y);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    vert0_addr = face->i0 * 8 + (u32)vertices;
                    xy0 = ((Vert *)vert0_addr)->x;
                    xy0 = xy0 + cell_x;
                    xy0 = xy0 & 0xFFFF;
                    vert0_y = ((Vert *)vert0_addr)->y;
                    y0_high = (cell_y + vert0_y) << 0x10;
                    xy0 = xy0 | y0_high;
                    S32(scratch, 0x70) = xy0;
                    vert2_ref = U16((u8 *)face, 4);
                    vert3_ref_y = U16((u8 *)face, 6);
                    vert0_ref = U16((u8 *)face, 0);
                    index1_xy = face->i1;
                    vert1_ref_y = index1_xy * 8 + (u32)vertices;
                    xy1 = U16((u8 *)vert1_ref_y, 0);
                    vert1_ref_y = S16((u8 *)vert1_ref_y, 2);
                    vert2_ref = vert2_ref << 3;
                    vert2_ref = vert2_ref + (u32)vertices;
                    vert3_ref_y = vert3_ref_y << 3;
                    vert3_ref_y = vert3_ref_y + (u32)vertices;
                    ASM_USE2_NV(vert3_ref_y, vert3_ref_y);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    ASM_USE_NV(vert3_ref_y);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    vert0_ref = vert0_ref << 3;
                    vert0_ref = vert0_ref + (u32)vertices;
                    xy1 = xy1 + cell_x;
                    xy1 = xy1 & 0xFFFF;
                    ASM_USE2_NV(xy1, xy1);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    ASM_USE2_NV(xy1, xy1);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    y1_high = (cell_y + vert1_ref_y) << 0x10;
                    xy1 = xy1 | y1_high;
                    xy2 = U16((u8 *)vert2_ref, 0);
                    vert2_y = S16((u8 *)vert2_ref, 2);
                    xy3 = U16((u8 *)vert3_ref_y, 0);
                    ASM_KEEP_NV(vert0_ref);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    height0 = U16((u8 *)vert0_ref, 4);
                    height_bias = ((Cell *)((u8 *)&D_80027120[0] + cell_index * 6))->bias;
                    height0 = height0 - height_bias;
                    ASM_USE2_NV(height0, height0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    ASM_USE2_NV(height0, height0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    vert3_ref_y = S16((u8 *)vert3_ref_y, 2);
                    xy2 = xy2 + cell_x;
                    xy2 = xy2 & 0xFFFF;
                    y2_high = cell_y + vert2_y;
                    y2_high = y2_high << 0x10;
                    xy2 = xy2 | y2_high;
                    xy3 = xy3 + cell_x;
                    xy3 = xy3 & 0xFFFF;
                    ASM_USE_NV(y2_high);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    S16(scratch, 0x74) = height0;
                    index1 = U16((u8 *)face, 2);
                    vert1_addr = index1 * 8 + (u32)vertices;
                    ASM_KEEP_DEP_NV(vert1_addr, y1_high);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                    y3_high = (cell_y + vert3_ref_y) << 0x10;
                    height1 = U16((u8 *)vert1_addr, 4);
                    S32(scratch, 0x78) = xy1;
                    height1 = height1 - ((Cell *)((u8 *)&D_80027120[0] + cell_index * 6))->bias;
                    S16(scratch, 0x7C) = height1;
                    index2 = U16((u8 *)face, 4);
                    vert2_addr = index2 * 8 + (u32)vertices;
                    height2 = U16((u8 *)vert2_addr, 4);
                    S32(scratch, 0x80) = xy2;
                    height2 = height2 - ((Cell *)((u8 *)&D_80027120[0] + cell_index * 6))->bias;
                    S16(scratch, 0x84) = height2;
                    index3 = U16((u8 *)face, 6);
                    vert3_addr = index3 * 8 + (u32)vertices;
                    xy3 = xy3 | y3_high;
                    S32(scratch, 0x88) = xy3;
                    height3 = U16((u8 *)vert3_addr, 4);
                    height3 = height3 - ((Cell *)((u8 *)&D_80027120[0] + cell_index * 6))->bias;
                    S16(scratch, 0x8C) = height3;
                    facing = func_800656C0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88,
                                      prim + 8, prim + 0x10, prim + 0x18, prim + 0x20,
                                      scratch + 0x90, scratch + 0xC0, scratch + 0x94);
                    S32(scratch, 0x114) = facing;
                    if (facing > 0) {
                        depth = S32(scratch, 0xC0) - S32(scratch, 0xC4);
                        S32(scratch, 0xC0) = depth;
                        if ((u32) (depth - 1) < 0x1DF) {
                            func_80065034(materials + face->tex * 8, render_state + 0xA8, prim + 4);
                            S32(prim, 0xC) = face->a;
                            S32(prim, 0x14) = face->b;
                            U16(prim, 0x1C) = face->u2;
                            U16(prim, 0x24) = face->u3;
                            if (U8(render_params, 0xC) != 0x80) {
                                U8(prim, 4) = (U8(prim, 4) * U8(render_params, 0xC)) >> 7;
                                U8(prim, 5) = (U8(prim, 5) * U8(render_params, 0xD)) >> 7;
                                U8(prim, 6) = (U8(prim, 6) * U8(render_params, 0xE)) >> 7;
                            }
                            U8(prim, 3) = 9;
                            func_8006658C(S32(scratch, 0x20) + S32(scratch, 0xC0) * 4, prim);
                            prim += 0x28;
                        }
                    }
                    if ((face->flags & 0x80FF) == 0x8001) {
                        break;
                    }
                    face += 1;
                }
            }
            ((Cell *)((u8 *)cells + cell_index * 6))->bias = 0;
            cell_x += 0x40;
            col += 1;
            cell_index += 1;
        } while (col < 3);
        cell_y += 0x40;
        row += 1;
    } while (row < 3);

    active_buffer = *(u8 **)render_state;
    PTR(active_buffer, 0x8D0) = prim;
    saved_rotation[0] = U16(render_state, 0xC4);
    saved_rotation[1] = U16(render_state, 0xC6);
    saved_rotation[2] = U16(render_state, 0xC8);
    saved_position[0] = U16(render_state, 0xB4);
    saved_position[1] = U16(render_state, 0xB6);
    saved_position[2] = U16(render_state, 0xB8);
    U16(render_state, 0xB4) = 0;
    U16(render_state, 0xB6) = 0;
    U16(render_state, 0xB8) = 0;
    U16(render_state, 0xC4) = U16(render_params, 0x16);
    U16(render_state, 0xC6) = U16(render_params, 0x18);
    U16(render_state, 0xC8) = U16(render_params, 0x1A);

    if (PTR(objects, 8) != 0) {
        S32(scratch, 0x13C) = 0;
        main_object = PTR(objects, 8);
        func_800453E0(main_object + 0x20, S32(main_object, 8), S32(main_object, 0xC), (s16) U16(scratch, 0xC4));
        main_entry = PTR(objects, 8);
        D_8002713A[0] = -2;
        func_80026F1C(S32(main_entry, 8), S32(main_entry, 0xC), -2, S32(scratch, 0xC4));
    }
    object_index = 0;
    object_slot = objects;
    ASM_USE_NV(vertices);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    do {
        ASM_KEEP_NV(object_slot);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        if (PTR(object_slot, 0xC) != 0) {
            S32(scratch, 0x13C) = 0;
            extra_object = PTR(object_slot, 0xC);
            func_800453E0(extra_object + 0x20, S32(extra_object, 8), S32(extra_object, 0xC), (s16) U16(scratch, 0xC4));
            extra_entry = PTR(object_slot, 0xC);
            func_80026F1C(S32(extra_entry, 8), S32(extra_entry, 0xC), 0, S32(scratch, 0xC4));
        }
        object_index += 1;
        object_slot += 4;
    } while (object_index < 2);

    sprite = PTR(objects, 0x14);
    if (sprite != 0) {
        sprite_data = PTR(sprite, 0xC);
        if (!(U16(sprite_data, 0x14) & 0x80)) {
            func_80045CC4(sprite + 0x20, S32(sprite, 8), sprite_data, (s16) U16(scratch, 0xC4));
        }
    }
    U16(render_state, 0xB4) = saved_position[0];
    U16(render_state, 0xB6) = saved_position[1];
    U16(render_state, 0xB8) = saved_position[2];
    U16(render_state, 0xC4) = saved_rotation[0];
    U16(render_state, 0xC6) = saved_rotation[1];
    U16(render_state, 0xC8) = saved_rotation[2];
    func_80064A40();
    return 0;
}


