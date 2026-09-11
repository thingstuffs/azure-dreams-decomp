#include "common.h"

extern void func_80064840();
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0();
extern void func_80064CF0();
extern void func_80064D80();
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800654B0();
extern void func_80065820();
extern void func_8006658C();
extern void func_800666F4();

extern u8 D_8006CD30[];
extern u8 D_80083160[];
typedef struct { u8 b0, b1, b2, b3; } Ent4;
typedef struct { u8 b0, b1; u16 h2, h4; u8 *p8; } Ent12;
extern Ent4 D_800E3548[];
extern Ent12 D_800E36C8[];

#define U8(p, o)  (*(u8  *)((u8 *)(p) + (o)))
#define S8(p, o)  (*(s8  *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

typedef struct {
    s32 vx, vy, vz, pad;
} Vec4;

/* Draw visible entity sprite quads and their translucent shadows. */
s32 func_800A7CC4(s32 unused0, s32 unused1, void *render_params) {
    s32 entity_index;
    u8 *scratch;
    u8 *render_state;
    u8 *render_ctx;
    u8 *entity;
    u8 *prim;
    u8 *prim_code;
    u8 *sprite;
    register u8 *tex_info ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 world_z, depth, angle_y_offset, sort_depth;
    s32 tex_u, tex_width, tex_v, tex_height;
    register s32 tex_left ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 tex_right;
    s32 tex_top;
    s32 tex_bottom;
    s32 quad_right, quad_bottom, packed_uv, quad_left, quad_top;
    u8 offset_x_byte, offset_y_byte;
    s32 visible, visible1, visible2, visible3;
    s32 screen_bottom;
    struct { u16 a, b, c; } camera_angles;
    Vec4 shadow_scale;
    u8 *vertex0, *vertex1, *vertex2, *vertex3, *screen0, *screen1, *screen2, *screen3, *depth_out;
    u8 *flags_out;
    u8 *entities;
    u8 *view_matrix;
    u8 *rotation_matrix;
    u8 *transform;
    u8 *matrix_page;
    s32 depth_offset, flags_offset;
    register u8 *rotation_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *matrix_or_prim ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 angle_z;
    s32 angle_y;

    matrix_page = (u8 *)0x80070000;
    depth_offset = 0x90;
    flags_offset = 0x94;
    entity_index = 0;
    rotation_matrix = (u8 *)0x1F8000D0;
    transform = (u8 *)0x1F800050;
    vertex0 = (u8 *)0x1F800070;
    vertex1 = (u8 *)0x1F800078;
    vertex2 = (u8 *)0x1F800080;
    scratch = (u8 *)0x1F800000;
    render_state = D_80083160;
    render_ctx = *(u8 **)D_80083160;
    prim = *(u8 **)(render_ctx + 0x8D0);
    U32(scratch, 0x20) = (u32)(render_ctx + 0xB0);
    U32(scratch, 0xE4) = 0;
    U32(scratch, 0xE8) = 0;
    U32(scratch, 0xEC) = 0;
    U16(scratch, 0x8C) = 0;
    U16(scratch, 0x84) = 0;
    U16(scratch, 0x7C) = 0;
    U16(scratch, 0x74) = 0;
    camera_angles.a = U16(render_state, 196);
    camera_angles.b = U16(render_state, 198);
    camera_angles.c = U16(render_state, 200);

    do {
        if (((Ent4 *)((entity_index * 4) + (s32)D_800E3548))->b1 != 0) {
            entities = (u8 *)D_800E36C8;
            entity = entities + entity_index * 12;
            U16(scratch, 0) = (U8(entity, 0) << 6) + 0x20;
            U16(scratch, 2) = (U8(entity, 1) << 6) + 0x20;
            view_matrix = D_8006CD30;
            world_z = U16(entity, 4);
            U16(scratch, 4) = world_z;
            sprite = *(u8 **)(entity + 8);
            U16(entity, 2) = world_z;
            depth = func_80065420(scratch, scratch + 0xB8, scratch + depth_offset, scratch + flags_offset);
            U32(scratch, 0xC0) = depth;
            do {
                sort_depth = depth;
            } while (0);
            ASM_KEEP_NV(sort_depth);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_DEP_NV(sort_depth, depth * 4);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP_MEMDEP_NV(sort_depth, rotation_arg, U32(view_matrix, 0x1C));   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            U32(view_matrix, 0x1C) = depth * 4;
            sort_depth -= 2;
            U32(scratch, 0xC0) = sort_depth;
            if ((u32)sort_depth < 0x1E0) {
                func_800649A0();
                rotation_arg = scratch + 0x100;
                matrix_or_prim = rotation_matrix;
                vertex3 = scratch + 0x88;
                screen0 = scratch + 0xF0;
                screen1 = scratch + 0xF4;
                screen2 = scratch + 0xF8;
                screen3 = scratch + 0xFC;
                depth_out = scratch + 0x90;
                flags_out = scratch + 0x94;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                U16(scratch, 0xB8) = U16(scratch, 0xB8) - 0xA0;
                U16(scratch, 0xBA) = U16(scratch, 0xBA) - 0x78;
                tex_info = sprite + 4;
                prim_code = prim + 7;
                U16(scratch, 0x100) = U16(render_params, 0x16);
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                angle_z = U16(render_params, 0x1A);
                angle_z -= camera_angles.b;
                U16(scratch, 0x104) = U16(render_state, 184) + angle_z;
                angle_y = camera_angles.c;
                angle_y += 0x100;
                angle_y &= 0x1FF;
                angle_y_offset = U16(render_params, 0x18);
                angle_y_offset -= 0x100;
                angle_y += angle_y_offset;
                U16(scratch, 0x102) = angle_y;
                func_80065820(rotation_arg, matrix_or_prim);
                func_80064840(view_matrix, rotation_matrix, transform);
                func_80064D80(transform);
                func_80064CF0(transform);
                for (;;) {
                    if (!(U8(sprite, 0) & 0x20)) {
                        tex_u = U8(tex_info, 4);
                        U32(scratch, 8) = tex_u;
                        tex_width = U8(tex_info, 6);
                        U32(scratch, 0x10) = tex_width;
                        if (tex_u + tex_width >= 0x100) {
                            U32(scratch, 0x10) = tex_width - 1;
                        }
                        tex_v = U8(tex_info, 5);
                        U32(scratch, 0xC) = tex_v;
                        tex_height = U8(tex_info, 7);
                        U32(scratch, 0x14) = tex_height;
                        if (tex_v + tex_height >= 0x100) {
                            U32(scratch, 0x14) = tex_height - 1;
                        }
                        offset_x_byte = *(volatile u8 *)(tex_info - 2);
                        quad_left = (s8)offset_x_byte;
                        S16(scratch, 0x80) = quad_left;
                        S16(scratch, 0x70) = quad_left;
                        quad_right = quad_left + U16(scratch, 0x10);
                        S16(scratch, 0x88) = quad_right;
                        S16(scratch, 0x78) = quad_right;
                        offset_y_byte = *(volatile u8 *)(tex_info - 1);
                        quad_top = (s8)offset_y_byte;
                        S16(scratch, 0x7A) = quad_top;
                        S16(scratch, 0x72) = quad_top;
                        quad_bottom = quad_top + U16(scratch, 0x14);
                        S16(scratch, 0x8A) = quad_bottom;
                        S16(scratch, 0x82) = quad_bottom;
                        func_800654B0(vertex0, vertex1, vertex2, vertex3, screen0, screen1, screen2, screen3, depth_out, flags_out);
                        U16(prim_code, 1) = U16(scratch, 0xF0) + U16(scratch, 0xB8);
                        U16(prim_code, 3) = U16(scratch, 0xF2) + U16(scratch, 0xBA);
                        U16(prim_code, 9) = U16(scratch, 0xF4) + U16(scratch, 0xB8);
                        U16(prim_code, 0xB) = U16(scratch, 0xF6) + U16(scratch, 0xBA);
                        U16(prim_code, 0x11) = U16(scratch, 0xF8) + U16(scratch, 0xB8);
                        U16(prim_code, 0x13) = U16(scratch, 0xFA) + U16(scratch, 0xBA);
                        U16(prim_code, 0x19) = U16(scratch, 0xFC) + U16(scratch, 0xB8);
                        screen_bottom = U16(scratch, 0xFE) + U16(scratch, 0xBA);
                        U16(prim_code, 0x1B) = screen_bottom;
                        visible = 0;
                        if ((u16)(U16(prim_code, 1) + 0x20) < 0x181) {
                            visible = (u16)(U16(prim_code, 3) + 0x20) < 0x121;
                        }
                        visible1 = 0;
                        if ((u16)(U16(prim_code, 9) + 0x20) < 0x181) {
                            visible1 = (u16)(U16(prim_code, 0xB) + 0x20) < 0x121;
                        }
                        visible2 = 0;
                        visible = visible | visible1;
                        if ((u16)(U16(prim_code, 0x11) + 0x20) < 0x181) {
                            visible2 = (u16)(U16(prim_code, 0x13) + 0x20) < 0x121;
                        }
                        visible3 = 0;
                        visible |= visible2;
                        visible2 = visible;
                        if ((u16)(U16(prim_code, 0x19) + 0x20) < 0x181) {
                            visible3 = (u16)(screen_bottom + 0x20) < 0x121;
                        }
                        if ((visible2 | visible3) != 0) {
                            tex_right = U32(scratch, 0x10);
                            tex_left = U32(scratch, 8);
                            tex_bottom = U32(scratch, 0x14);
                            tex_top = U32(scratch, 0xC);
                            tex_right = tex_right + tex_left;
                            tex_bottom = tex_bottom + tex_top;
                            U32(scratch, 0x10) = tex_right;
                            ASM_SET(packed_uv);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                            packed_uv = tex_top;
                            ASM_KEEP_NV(packed_uv);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                            tex_bottom = tex_bottom << 8;
                            packed_uv = packed_uv << 8;
                            U32(scratch, 0x14) = tex_bottom;
                            U32(scratch, 0xC) = packed_uv;
                            packed_uv += tex_left;
                            packed_uv += U16(tex_info, 2) << 16;
                            S32(prim_code, 5) = packed_uv;
                            S32(prim_code, 0xD) = U32(scratch, 0xC) + U32(scratch, 0x10) + (S16(tex_info, 0) << 16);
                            S16(prim_code, 0x15) = U32(scratch, 0x14) + U32(scratch, 8);
                            S16(prim_code, 0x1D) = U32(scratch, 0x14) + U32(scratch, 0x10);
                            if ((s16)U16(scratch, 0x50) >= 0x1800) {
                                U8(prim_code, 0xD) = U8(prim_code, 0x1D)--;
                            }
                            if ((s16)U16(scratch, 0x58) >= 0x1800) {
                                U8(prim_code, 0x16) = U8(prim_code, 0x1E)--;
                            }
                            if (S16(prim_code, 1) > S16(prim_code, 0x19)) {
                                U8(prim_code, 0xD) = U8(prim_code, 0xD) - 1;
                                U8(prim_code, 0x1D) = U8(prim_code, 0x1D) - 1;
                            }
                            if (S16(prim_code, 3) > S16(prim_code, 0x1B)) {
                                U8(prim_code, 0x16) = U8(prim_code, 0x16) - 1;
                                U8(prim_code, 0x1E) = U8(prim_code, 0x1E) - 1;
                            }
                            S32(prim_code, -3) = S32(render_params, 0xC);
                            func_800666F4(prim);
                            matrix_or_prim = prim;
                            prim_code += 40;
                            ASM_KEEP(prim_code);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                            func_8006658C(U32(scratch, 0x20) + U32(scratch, 0xC0) * 4, matrix_or_prim);
                            prim += 40;
                            func_800649A0();
                            shadow_scale.vz = (s32)(s16)(*(volatile u16 *)(scratch + 4)) - 4;
                            shadow_scale.vz = ((shadow_scale.vz - (s32)(s16)(*(volatile u16 *)(scratch + 4))) << 5) + 0x1000;
                            if (shadow_scale.vz < 0) {
                                shadow_scale.vz = 0;
                            }
                            U16(scratch, 0x102) = 0;
                            shadow_scale.vx = shadow_scale.vz;
                            shadow_scale.vy = shadow_scale.vz / 2;
                            U16(scratch, 0x100) = -camera_angles.a;
                            U16(scratch, 0x104) = U16(render_state, 184) - camera_angles.b;
                            func_80065820(scratch + 0x100, rotation_matrix);
                            ASM_USE_G_NV(view_matrix);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                            func_80064840(matrix_page - 0x32D0, rotation_matrix, transform);
                            func_80064BC0(transform, &shadow_scale);
                            func_80064D80(transform);
                            func_80064CF0(transform);
                            U16(scratch, 0x70) = U16(scratch, 0x70) + 6;
                            U16(scratch, 0x78) = U16(scratch, 0x78) + 6;
                            func_800654B0(vertex0, vertex1, vertex2, vertex3, screen0, screen1, screen2, screen3, depth_out, flags_out);
                            U16(prim_code, 1) = U16(scratch, 0xF0) + U16(scratch, 0xB8);
                            U16(prim_code, 3) = U16(scratch, 0xF2) + U16(scratch, 0xBA);
                            U16(prim_code, 9) = U16(scratch, 0xF4) + U16(scratch, 0xB8);
                            U16(prim_code, 0xB) = U16(scratch, 0xF6) + U16(scratch, 0xBA);
                            U16(prim_code, 0x11) = U16(scratch, 0xF8) + U16(scratch, 0xB8);
                            U16(prim_code, 0x13) = U16(scratch, 0xFA) + U16(scratch, 0xBA);
                            U16(prim_code, 0x19) = U16(scratch, 0xFC) + U16(scratch, 0xB8);
                            U16(prim_code, 0x1B) = U16(scratch, 0xFE) + U16(scratch, 0xBA);
                            S32(prim_code, 5) = U32(scratch, 0xC) + U32(scratch, 8) + 0x7FC00000;
                            S32(prim_code, 0xD) = U32(scratch, 0xC) + U32(scratch, 0x10) + (S16(tex_info, 0) << 16);
                            S16(prim_code, 0x15) = U32(scratch, 0x14) + U32(scratch, 8);
                            S16(prim_code, 0x1D) = U32(scratch, 0x14) + U32(scratch, 0x10);
                            if (S16(prim_code, 1) > S16(prim_code, 0x19)) {
                                U8(prim_code, 0xD) = U8(prim_code, 0xD) - 1;
                                U8(prim_code, 0x1D) = U8(prim_code, 0x1D) - 1;
                            }
                            if (S16(prim_code, 3) > S16(prim_code, 0x1B)) {
                                U8(prim_code, 0x16) = U8(prim_code, 0x16) - 1;
                                U8(prim_code, 0x1E) = U8(prim_code, 0x1E) - 1;
                            }
                            S32(prim_code, -3) = S32(render_params, 0xC);
                            func_800666F4(prim);
                            U8(prim_code, 0) = U8(prim_code, 0) | 2;
                            prim_code += 40;
                            func_8006658C(U32(scratch, 0x20) + U32(scratch, 0xC0) * 4, prim);
                            prim += 40;
                            func_80064A40();
                        }
                    }
                    tex_info += 12;
                    if (S8(sprite, 0) < 0) {
                        break;
                    }
                    sprite += 12;
                }
                func_80064A40();
            }
        }
        entity_index += 1;
    } while (entity_index < 64);
    *(u8 **)(*(u8 **)render_state + 0x8D0) = prim;
    return 0;
}
