#include "common.h"

extern u8 *D_80083160;

typedef struct {} EmptyArg;

s32 func_800644B8(s32);
s32 func_80064584(s32);
void func_80064840(void *, void *, void *);
void func_800649A0(void);
void func_80064A40(void);
void func_80064AE0(void *);
void func_80064BC0(void *, void *);
void func_80064CF0(void *);
void func_80064D80(void *);
s32 func_80065590(void *, void *, void *, void *, void *,
                  void *, void *, void *, void *, void *, EmptyArg);
void func_80065820(void *, void *);
void func_800666F4(void *);

/* Draws a textured spherical mesh and adds its visible quads to the ordering table. */
void func_80024758(void *mesh, void *position, void *material, u16 depth_bias) {
    s32 view_matrix[8];
    u16 saved_depth_bias;
    u8 *texture;
    s32 column;
    s32 row;
    register u8 *scratch ASM_REG("$21") = (u8 *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *page;
    u8 *initial_page;
    u32 page_dependency;
    u8 **page_ptr;
    u8 *quad;
    s32 column_count;
    s32 row_count;
    s32 latitude_span;
    s32 latitude_offset;
    s32 next_latitude_offset;
    s32 longitude_offset;
    s32 ring_radius;
    s32 next_ring_radius;
    s32 longitude;
    s32 next_longitude;
    s32 latitude;
    s32 next_latitude;
    s32 depth_index;
    s32 clut;
    s32 tpage;
    s32 uv_end;
    s32 clut_override;
    s32 tpage_override;
    s32 material_flags;
    s32 screen_y;
    s32 corner_0_visible;
    s32 corner_1_visible;
    s32 corner_2_visible;
    s32 corner_3_visible;
    s32 any_corner_visible;
    s32 last_vertex_z;
    u8 texture_flags;
    u8 draw_flags;

    initial_page = D_80083160;
    ASM_KEEP_MEMDEP(initial_page, page_dependency, D_80083160);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    *(u8 **)(scratch + 0x24) = initial_page + 0xB0;
    *(s32 *)(scratch + 0x88) = *(s16 *)((u8 *)position + 2);
    *(s32 *)(scratch + 0x8C) = *(s16 *)((u8 *)position + 6);
    *(s32 *)(scratch + 0x90) = *(s16 *)((u8 *)position + 0xA);
    *(u16 *)((u8 *)material + 0x14) = *(u16 *)((u8 *)material + 0x14) | 0x8000;
    saved_depth_bias = depth_bias;
    func_800649A0();
    *(s32 *)(scratch + 0x3C) = 0x2000;
    *(s32 *)(scratch + 0x38) = 0x2000;
    *(s32 *)(scratch + 0x34) = 0x2000;
    *(u16 *)(scratch + 0xA4) = *(u16 *)((u8 *)material + 0x16);
    *(u16 *)(scratch + 0xA8) = *(u16 *)((u8 *)material + 0x1A);
    *(u16 *)(scratch + 0xA6) = *(u16 *)((u8 *)material + 0x18);
    func_80065820((u8 *)((u32)scratch | 0xA4), (u8 *)((u32)scratch | 0x74));
    func_80064AE0(&view_matrix[0]);
    func_80064840(&view_matrix[0], (u8 *)((u32)scratch | 0x74), (u8 *)((u32)scratch | 0x54));
    func_80064BC0((u8 *)((u32)scratch | 0x54), (u8 *)((u32)scratch | 0x34));
    func_80064D80((u8 *)((u32)scratch | 0x54));
    func_80064CF0((u8 *)((u32)scratch | 0x54));
    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    texture = *(u8 **)((u8 *)material + 8);
    *(u16 *)(scratch + 0x28) = *(u16 *)((u8 *)material + 0x14);
    for (;;) {
        for (row = 0; row < *(s16 *)((u8 *)mesh + 0xC); row++) {
            page_ptr = &D_80083160;
            for (column = 0; column < *(s16 *)((u8 *)mesh + 0xA); column++) {
                *(s32 *)(scratch + 0x0C) = *(u8 *)(texture + 8);
                *(s32 *)(scratch + 0x10) = *(u8 *)(texture + 9);
                *(s32 *)(scratch + 0x14) = *(u8 *)(texture + 10);
                page = *page_ptr;
                *(s32 *)(scratch + 0x18) = *(u8 *)(texture + 11);
                quad = *(u8 **)(page + 0x8D0);
                *(u8 **)(page + 0x8D0) = quad + 0x28;
                column_count = *(s16 *)((u8 *)mesh + 0xA);
                longitude = (column << 0xC) / column_count;
                latitude_span = -*(s16 *)((u8 *)mesh + 0xE);
                row_count = *(s16 *)((u8 *)mesh + 0xC);
                latitude_offset = (latitude_span * row) / row_count;
                next_latitude_offset = (latitude_span * (row + 1)) / row_count;
                longitude_offset = *(s16 *)((u8 *)mesh + 0x10);
                next_longitude = ((column + 1) << 0xC) / column_count;
                longitude = longitude + longitude_offset;
                latitude = latitude_offset + 0x400;
                next_latitude = next_latitude_offset + 0x400;
                if (longitude >= 0x1001) {
                    longitude -= 0x1000;
                }
                if (longitude < 0) {
                    longitude += 0x1000;
                }
                next_longitude = next_longitude + longitude_offset;
                if (next_longitude >= 0x1001) {
                    next_longitude -= 0x1000;
                }
                if (next_longitude < 0) {
                    next_longitude += 0x1000;
                }
                ring_radius = ((*(s32 *)((u8 *)mesh + 0x68) >> 8) * func_80064584(latitude)) >> 0x14;
                next_ring_radius = ((*(s32 *)((u8 *)mesh + 0x68) >> 8) * func_80064584(next_latitude)) >> 0x14;
                *(s16 *)(scratch + 0xB0) = (ring_radius * func_800644B8(longitude)) >> 0xC;
                *(s16 *)(scratch + 0xB2) = (ring_radius * func_80064584(longitude)) >> 0xC;
                *(s16 *)(scratch + 0xB4) = -(((*(s32 *)((u8 *)mesh + 0x68) >> 8) * func_800644B8(latitude)) >> 0x14);
                *(s16 *)(scratch + 0xB8) = (ring_radius * func_800644B8(next_longitude)) >> 0xC;
                *(s16 *)(scratch + 0xBA) = (ring_radius * func_80064584(next_longitude)) >> 0xC;
                *(s16 *)(scratch + 0xBC) = -(((*(s32 *)((u8 *)mesh + 0x68) >> 8) * func_800644B8(latitude)) >> 0x14);
                *(s16 *)(scratch + 0xC0) = (next_ring_radius * func_800644B8(longitude)) >> 0xC;
                *(s16 *)(scratch + 0xC2) = (next_ring_radius * func_80064584(longitude)) >> 0xC;
                *(s16 *)(scratch + 0xC4) = -(((*(s32 *)((u8 *)mesh + 0x68) >> 8) * func_800644B8(next_latitude)) >> 0x14);
                *(s16 *)(scratch + 0xC8) = (next_ring_radius * func_800644B8(next_longitude)) >> 0xC;
                *(s16 *)(scratch + 0xCA) = (next_ring_radius * func_80064584(next_longitude)) >> 0xC;
                last_vertex_z = -(((*(s32 *)((u8 *)mesh + 0x68) >> 8) * func_800644B8(next_latitude)) >> 0x14);
                depth_index = (func_80065590(scratch + 0xB0, scratch + 0xB8, scratch + 0xC0, scratch + 0xC8, quad + 8, quad + 0x10, quad + 0x18, quad + 0x20, scratch + 0xD0, (void *)(scratch + 0xD4),
                       ({
                           EmptyArg empty;
                           *(s16 *)(scratch + 0xCC) = last_vertex_z;
                           empty;
                       })) - (s16)saved_depth_bias) - 6;
                *(s32 *)(scratch + 0x100) = depth_index;
                if ((u32)depth_index < 0x1E0U) {
                    corner_0_visible = 0;
                    if ((u32)((*(u16 *)(quad + 8) + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = *(u16 *)(quad + 0xA) + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_0_visible = (u32)screen_y < 0x121U;
                    }
                    corner_1_visible = 0;
                    if ((u32)((*(u16 *)(quad + 0x10) + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = *(u16 *)(quad + 0x12) + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_1_visible = (u32)screen_y < 0x121U;
                    }
                    corner_2_visible = 0;
                    corner_0_visible = corner_0_visible | corner_1_visible;
                    if ((u32)((*(u16 *)(quad + 0x18) + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = *(u16 *)(quad + 0x1A) + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_2_visible = (u32)screen_y < 0x121U;
                    }
                    corner_3_visible = 0;
                    any_corner_visible = corner_0_visible | corner_2_visible;
                    if ((u32)((*(u16 *)(quad + 0x20) + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = *(u16 *)(quad + 0x22) + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_3_visible = (u32)screen_y < 0x121U;
                    }
                    if ((any_corner_visible | corner_3_visible) != 0) {
                        *(u16 *)((u8 *)material + 0x14) = *(u16 *)((u8 *)material + 0x14) & 0x7FFF;
                        func_800666F4(quad);
                        uv_end = *(s32 *)(scratch + 0x14) + *(s32 *)(scratch + 0x0C);
                        *(s32 *)(scratch + 0x14) = uv_end;
                        if (uv_end & 0x100) {
                            *(s32 *)(scratch + 0x14) = uv_end - 1;
                        }
                        uv_end = *(s32 *)(scratch + 0x18) + *(s32 *)(scratch + 0x10);
                        *(s32 *)(scratch + 0x18) = uv_end;
                        if (uv_end & 0x100) {
                            *(s32 *)(scratch + 0x18) = uv_end - 1;
                        }
                        *(s32 *)(scratch + 0x10) = *(s32 *)(scratch + 0x10) << 8;
                        *(s32 *)(scratch + 0x18) = *(s32 *)(scratch + 0x18) << 8;
                        clut_override = *(u16 *)((u8 *)material + 0x12);
                        if (clut_override != 0) {
                            if (*(u16 *)(scratch + 0x28) & 0x100) {
                                *(u16 *)(quad + 0xE) = clut_override;
                                goto set_uvs;
                            }
                            clut = clut_override + *(u16 *)(texture + 6);
                            goto store_clut;
                        }
                        clut = *(u16 *)(texture + 6);
                    store_clut:
                        *(u16 *)(quad + 0xE) = clut;
                    set_uvs:
                        *(s16 *)(quad + 0xC) = *(u16 *)(scratch + 0x10) + *(u16 *)(scratch + 0x0C);
                        *(s16 *)(quad + 0x14) = *(u16 *)(scratch + 0x10) + *(u16 *)(scratch + 0x14);
                        tpage_override = *(u16 *)((u8 *)material + 0x10);
                        if (tpage_override != 0) {
                            tpage = tpage_override + (*(u16 *)(texture + 4) & 0xFF9F);
                            goto store_tpage;
                        }
                        tpage = *(u16 *)(texture + 4);
                    store_tpage:
                        *(u16 *)(quad + 0x16) = tpage;
                        *(s16 *)(quad + 0x1C) = *(u16 *)(scratch + 0x18) + *(u16 *)(scratch + 0x0C);
                        *(s16 *)(quad + 0x24) = *(u16 *)(scratch + 0x18) + *(u16 *)(scratch + 0x14);
                        if (*(s16 *)(quad + 8) > *(s16 *)(quad + 0x20)) {
                            *(u8 *)(quad + 0x14) = *(u8 *)(quad + 0x14) - 1;
                            *(u8 *)(quad + 0x24) = *(u8 *)(quad + 0x24) - 1;
                        }
                        if (*(s16 *)(quad + 0xA) > *(s16 *)(quad + 0x22)) {
                            *(u8 *)(quad + 0x1D) = *(u8 *)(quad + 0x1D) - 1;
                            *(u8 *)(quad + 0x25) = *(u8 *)(quad + 0x25) - 1;
                        }
                        texture_flags = *(u8 *)(texture + 1);
                        *(u8 *)((u8 *)material + 0xF) = texture_flags;
                        material_flags = *(u16 *)(scratch + 0x28);
                        if (material_flags & 8) {
                            if (material_flags & 4) {
                                draw_flags = texture_flags | 2;
                                *(u8 *)((u8 *)material + 0xF) = draw_flags;
                            } else {
                                draw_flags = texture_flags & 0xFD;
                                *(u8 *)((u8 *)material + 0xF) = draw_flags;
                            }
                        }
                        {
                            register u32 address_mask ASM_REG("$4") = 0x00FFFFFF;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                            register u32 tag_mask ASM_REG("$5") = 0xFF000000;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                            s32 *ordering_slot;
                            *(s32 *)(quad + 4) = *(s32 *)((u8 *)material + 0xC);
                            *(s32 *)quad = (*(s32 *)quad & tag_mask)
                                | (*(s32 *)((*(s32 *)(scratch + 0x100) * 4) + *(s32 *)(scratch + 0x24)) & address_mask);
                            ordering_slot = (s32 *)((*(s32 *)(scratch + 0x100) * 4) + *(s32 *)(scratch + 0x24));
                            *ordering_slot = (*ordering_slot & tag_mask) | ((s32)quad & address_mask);
                        }
                    }
                }
            }
        }
        if (*(s8 *)texture < 0) {
            break;
        }
        texture += 12;
    }
    func_80064A40();
}
