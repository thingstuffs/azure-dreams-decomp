/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct S_800C6B40_0 {
    u8 pad_00[0x8];
    void * unk_08;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
} S_800C6B40_0;   /* arg2 in func_800C6B40 */

typedef struct S_800C6B40_1 {
    u8 unk_00;
    u8 pad_01[0x3];
    u16 unk_04;
    u16 unk_06;
    union {
        struct { u8 v; } at00;
        struct { void * v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_08;   /* overlapping accesses */
} S_800C6B40_1;   /* var_s3 in func_800C6B40 */

typedef struct {
    u8 pad_00[0x3];
    s8 len;
    union {
        s32 color;
        struct { u8 pad[0x3]; s8 code; } at03;
    } unk_04;   /* overlapping accesses */
    u16 x0;
    u16 y0;
    s8 u0;
    s8 v0;
    s16 clut;
    u16 x1;
    u16 y1;
    s8 u1;
    s8 v1;
    u16 tpage;
    u16 x2;
    u16 y2;
    s8 u2;
    s8 v2;
    u8 pad_1E[0x2];
    u16 x3;
    s16 y3;
    s8 u3;
    s8 v3;
} QuadPrim;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
    u16 origin_x;
    u16 origin_y;
} RotationWork;

void func_80064840();
void func_800649A0();
void func_80064A40();
void func_80064BC0();
void func_80064CF0();
void func_80064D80();
u32 func_80065420();
void func_800654B0();
void func_80065820();
void func_8006658C();
extern s32 D_8006CD30[];

/* Draws sprite parts as a 4-by-4 grid of textured quads, invoking custom part callbacks. */
void func_800C6B40(s32 context, void *position, void *sprite, s16 depth_bias) {
    u8 *scratch = (u8 *)0x1F800000;
    u8 *state;
    GameWork *render_globals;
    s32 packet_next;
    s32 local_y;
    s32 local_x;
    s32 (*draw_callback)(s32, void *, void *, void *, s32);
    s32 top_visible;
    s32 three_visible;
    s32 top_dx;
    s32 left_dy;
    s32 bottom_dx;
    s32 right_dy;
    s32 height;
    s32 left_dy_fixed;
    s32 right_dy_fixed;
    s32 bottom_left_visible;
    s32 top_dx_fixed;
    s32 bottom_dx_fixed;
    s32 top_left_visible;
    s32 next_right_y;
    s32 right_y;
    s32 column;
    register s32 matrix_or_u;
    s32 texture_v;
    s32 bottom_x;
    s32 top_x;
    s32 left_y;
    s32 bottom_y;
    s32 row;
    register s32 bottom_x_step;
    register s32 top_x_step;
    register s32 left_y_step;
    register s32 u_step;
    register s32 v_step;
    register s32 right_y_step;
    s32 width;
    s32 kseg_base;
    s32 visible_or_result;
    s32 saved_right_y;
    s32 part_flags;
    s32 bottom_right_visible;
    s32 u_end;
    s32 v_end;
    u16 center_x;
    u16 projected_left_x;
    u16 center_y;
    u16 tpage;
    u32 clut;
    u32 flipped_width;
    u32 normal_width;
    u32 clip_y;
    u32 flipped_height;
    u32 normal_height;
    u32 sprite_flags;
    s32 angle_offset;
    u32 origin_x;
    u32 origin_y;
    u16 projected_left_y;
    u16 projected_right_y;
    u16 draw_flags;
    s8 command;
    u32 depth;
    u32 sort_depth;
    u32 bottom_clip_y;
    u8 uv_inset;
    void *part;

    render_globals = &gameWork;
    state = *(u8 **)((u8 *)(&gameWork));
    *(u32 *)(scratch + 0x0EC) = NULL;
    *(u16 *)(scratch + 0x08C) = 0;
    *(u16 *)(scratch + 0x084) = 0;
    *(u16 *)(scratch + 0x07C) = 0;
    *(u16 *)(scratch + 0x074) = 0;
    *(u32 *)(scratch + 0x020) = state + 0xB0;
    *(u16 *)(scratch + 0x000) = (u16)(*(u16 *)((u8 *)position + 2));
    *(u16 *)(scratch + 0x002) = (u16)(*(u16 *)((u8 *)position + 6));
    *(u16 *)(scratch + 0x004) = (u16)(*(u16 *)((u8 *)position + 0xA));
    packet_next = *(s32 *)(state + 0x8D0);
    *(u32 *)(scratch + 0x0C0) = func_80065420(scratch, scratch + 0xB8, scratch + 0x90, scratch + 0x94);
    matrix_or_u = (s32)D_8006CD30;
    (*(u16 *)((u8 *)sprite + 0x14)) = (u16)((*(u16 *)((u8 *)sprite + 0x14)) | 0x8000);
    depth = *(volatile u32 *)(scratch + 0x0C0);
    *(s32 *)((u8 *)matrix_or_u + 0x1C) = (s32)(depth * 4);
    depth -= 8;
    sort_depth = depth - depth_bias;
    *(u32 *)(scratch + 0x0C0) = sort_depth;
    if (sort_depth < 0x1E0U) {
        func_800649A0();
        *(u16 *)(scratch + 0x0B8) = (u16)(*(u16 *)(scratch + 0x0B8) - 0xA0);
        *(u16 *)(scratch + 0x0BA) = (u16)(*(u16 *)(scratch + 0x0BA) - 0x78);
        *(u32 *)(scratch + 0x030) = render_globals->view.unk_0AC;
        *(u32 *)(scratch + 0x034) = render_globals->view.unk_0AE;
        *(u32 *)(scratch + 0x038) = render_globals->view.viewAngle;
        ((RotationWork *)(scratch + 0x100))->x = (u16)(*(u16 *)((u8 *)sprite + 0x16));
        ((RotationWork *)(scratch + 0x100))->z = (s16)(((S_800C6B40_0 *)sprite)->unk_1A - (u16)*(u32 *)(scratch + 0x034));
        ((RotationWork *)(scratch + 0x100))->y = (s16)((((u16)*(u32 *)(scratch + 0x038) + 0x100) & 0x1FF)
            + (angle_offset = (s32)((S_800C6B40_0 *)sprite)->unk_18 - 0x100));
        origin_x = ((S_800C6B40_0 *)sprite)->unk_20;
        *(u32 *)(scratch + 0x0E4) = origin_x;
        ((RotationWork *)(scratch + 0x100))->origin_x = origin_x;
        origin_y = (*(u16 *)((u8 *)sprite + 0x22));
        *(u32 *)(scratch + 0x0E8) = origin_y;
        ((RotationWork *)(scratch + 0x100))->origin_y = origin_y;
        func_80065820(0x1F800100, 0x1F8000D0);
        *(u32 *)(scratch + 0x030) = (void *)((S_800C6B40_0 *)sprite)->unk_1C;
        *(u32 *)(scratch + 0x034) = (void *)(*(u16 *)((u8 *)sprite + 0x1E));
        *(u32 *)(scratch + 0x038) = NULL;
        func_80064BC0(scratch + 0xD0, scratch + 0x30);
        func_80064840((s32 *)matrix_or_u, scratch + 0xD0, scratch + 0x50);
        func_80064D80(scratch + 0x50);
        func_80064CF0(scratch + 0x50);
        sprite_flags = ((S_800C6B40_0 *)sprite)->unk_14;
        part = ((S_800C6B40_0 *)sprite)->unk_08;
        *(u16 *)(scratch + 0x024) = (u16)sprite_flags;
        do {
            if (!(((S_800C6B40_1 *)part)->unk_00 & 0x20)) {
                *(u32 *)(scratch + 0x008) = (s32)((S_800C6B40_1 *)part)->unk_08.at00.v;
                *(u32 *)(scratch + 0x00C) = (s32)((S_800C6B40_1 *)part)->unk_08.at01.v;
                *(u32 *)(scratch + 0x010) = (s32)((S_800C6B40_1 *)part)->unk_08.at02.v;
                *(u32 *)(scratch + 0x014) = (s32)((S_800C6B40_1 *)part)->unk_08.at03.v;
                if ((((S_800C6B40_1 *)part)->unk_00 ^ (u32)*(u16 *)(scratch + 0x024)) & 1) {
                    local_x = (0 - (s8)(*(volatile u8 *)((u8 *)part + 2))) - (s32)(u32)*(u16 *)(scratch + 0x108);
                    flipped_width = *(u16 *)(scratch + 0x010);
                    *(u16 *)(scratch + 0x080) = local_x;
                    *(u16 *)(scratch + 0x070) = local_x;
                    local_x -= flipped_width;
                } else {
                    local_x = (s8)(*(volatile u8 *)((u8 *)part + 2)) - (s32)(u32)*(u16 *)(scratch + 0x108);
                    normal_width = *(u16 *)(scratch + 0x010);
                    *(u16 *)(scratch + 0x080) = local_x;
                    *(u16 *)(scratch + 0x070) = local_x;
                    local_x += normal_width;
                }
                *(u16 *)(scratch + 0x088) = local_x;
                *(u16 *)(scratch + 0x078) = local_x;
                if ((((S_800C6B40_1 *)part)->unk_00 ^ (u32)*(u16 *)(scratch + 0x024)) & 2) {
                    local_y = (0 - (s8)(*(volatile u8 *)((u8 *)part + 3))) - (s32)(u32)*(u16 *)(scratch + 0x10A);
                    flipped_height = *(u16 *)(scratch + 0x014);
                    *(u16 *)(scratch + 0x07A) = local_y;
                    *(u16 *)(scratch + 0x072) = local_y;
                    local_y -= flipped_height;
                } else {
                    local_y = (s8)(*(volatile u8 *)((u8 *)part + 3)) - (s32)(u32)*(u16 *)(scratch + 0x10A);
                    normal_height = *(u16 *)(scratch + 0x014);
                    *(u16 *)(scratch + 0x07A) = local_y;
                    *(u16 *)(scratch + 0x072) = local_y;
                    local_y += normal_height;
                }
                *(u16 *)(scratch + 0x08A) = local_y;
                do {
                    *(u16 *)(scratch + 0x082) = local_y;
                    func_800654B0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88, scratch + 0xF0,
                        scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, scratch + 0x90, scratch + 0x94);
                } while (0);
                width = *(u32 *)(scratch + 0x010);
                if (width < 0) {
                    width += 3;
                }
                height = *(u32 *)(scratch + 0x014);
                u_step = width >> 2;
                if (height < 0) {
                    height += 3;
                }
                top_dx = (s16)*(u16 *)(scratch + 0x0F4) - (s16)*(u16 *)(scratch + 0x0F0);
                top_dx_fixed = top_dx << 0x10;
                v_step = height >> 2;
                if (top_dx_fixed < 0) {
                    top_dx_fixed += 3;
                }
                projected_left_y = *(u16 *)(scratch + 0x0F2);
                left_dy = (s16)*(u16 *)(scratch + 0x0FA) - (s16)projected_left_y;
                left_dy_fixed = left_dy << 0x10;
                top_x_step = top_dx_fixed >> 2;
                if (left_dy_fixed < 0) {
                    left_dy_fixed += 3;
                }
                bottom_dx = (s16)*(u16 *)(scratch + 0x0FC) - (s16)*(u16 *)(scratch + 0x0F8);
                bottom_dx_fixed = bottom_dx << 0x10;
                left_y_step = left_dy_fixed >> 2;
                if (bottom_dx_fixed < 0) {
                    bottom_dx_fixed += 3;
                }
                projected_right_y = *(u16 *)(scratch + 0x0F6);
                right_dy = (s16)*(u16 *)(scratch + 0x0FE) - (s16)projected_right_y;
                right_dy_fixed = right_dy << 0x10;
                bottom_x_step = bottom_dx_fixed >> 2;
                if (right_dy_fixed < 0) {
                    right_dy_fixed += 3;
                }
                row = 0;
                right_y_step = right_dy_fixed >> 2;
                center_y = *(u16 *)(scratch + 0x0BA);
                texture_v = *(u32 *)(scratch + 0x00C);
                left_y = ((s16)center_y + (s16)projected_left_y) << 0x10;
                right_y = ((s16)center_y + (s16)projected_right_y) << 0x10;
                next_right_y = right_y + right_y_step;
                do {
                    column = 0;
                    bottom_y = next_right_y >> 0x10;
                    bottom_clip_y = (bottom_y + 0x20) & 0xFFFF;
                    center_x = *(u16 *)(scratch + 0x0B8);
                    matrix_or_u = *(u32 *)(scratch + 0x008);
                    projected_left_x = *(u16 *)(scratch + 0x0F0);
                    top_x = ((s16)center_x + (s16)projected_left_x) << 0x10;
                    bottom_x = ((s16)center_x + (s16)*(u16 *)(scratch + 0x0F8)) << 0x10;
                    do {
                        top_left_visible = 0;
                        ((QuadPrim *)packet_next)->x0 = (u16)(top_x >> 0x10);
                        ((QuadPrim *)packet_next)->x1 = (u16)((s32)(top_x + top_x_step) >> 0x10);
                        ((QuadPrim *)packet_next)->x2 = (u16)(bottom_x >> 0x10);
                        ((QuadPrim *)packet_next)->x3 = (u16)((s32)(bottom_x + bottom_x_step) >> 0x10);
                        ((QuadPrim *)packet_next)->y0 = (u16)(left_y >> 0x10);
                        ((QuadPrim *)packet_next)->y1 = (u16)(right_y >> 0x10);
                        ((QuadPrim *)packet_next)->y2 = (u16)((s32)(left_y + left_y_step) >> 0x10);
                        ((QuadPrim *)packet_next)->y3 = (s16)bottom_y;
                        if ((u32)((((QuadPrim *)packet_next)->x0 + 0x20) & 0xFFFF) < 0x181U) {
                            clip_y = (((QuadPrim *)packet_next)->y0 + 0x20) & 0xFFFF;
                            top_left_visible = clip_y < 0x121U;
                        }
                        visible_or_result = 0;
                        if ((u32)((((QuadPrim *)packet_next)->x1 + 0x20) & 0xFFFF) < 0x181U) {
                            clip_y = (((QuadPrim *)packet_next)->y1 + 0x20) & 0xFFFF;
                            visible_or_result = clip_y < 0x121U;
                        }
                        bottom_left_visible = 0;
                        top_visible = top_left_visible | visible_or_result;
                        if ((u32)((((QuadPrim *)packet_next)->x2 + 0x20) & 0xFFFF) < 0x181U) {
                            clip_y = (((QuadPrim *)packet_next)->y2 + 0x20) & 0xFFFF;
                            bottom_left_visible = clip_y < 0x121U;
                        }
                        bottom_right_visible = 0;
                        three_visible = top_visible | bottom_left_visible;
                        if ((u32)((((QuadPrim *)packet_next)->x3 + 0x20) & 0xFFFF) < 0x181U) {
                            bottom_right_visible = bottom_clip_y < 0x121U;
                        }
                        if ((three_visible | bottom_right_visible) != 0) {
                            uv_inset = ((S_800C6B40_0 *)sprite)->unk_0C.at03.v;
                            u_end = (matrix_or_u + u_step) - uv_inset;
                            if (matrix_or_u >= u_end) {
                                u_end = matrix_or_u + 1;
                            }
                            v_end = (texture_v + v_step) - uv_inset;
                            if (texture_v >= v_end) {
                                v_end = texture_v + 1;
                            }
                            if (u_end >= 0x100) {
                                u_end = 0xFF;
                            }
                            if (v_end >= 0x100) {
                                v_end = 0xFF;
                            }
                            ((QuadPrim *)packet_next)->u0 = (s8)matrix_or_u;
                            ((QuadPrim *)packet_next)->v0 = (s8)texture_v;
                            ((QuadPrim *)packet_next)->u1 = (s8)u_end;
                            ((QuadPrim *)packet_next)->v1 = (s8)texture_v;
                            ((QuadPrim *)packet_next)->u2 = (s8)matrix_or_u;
                            ((QuadPrim *)packet_next)->v2 = (s8)v_end;
                            ((QuadPrim *)packet_next)->u3 = (s8)u_end;
                            ((QuadPrim *)packet_next)->v3 = (s8)v_end;
                            ((QuadPrim *)packet_next)->len = 9;
                            clut = ((S_800C6B40_0 *)sprite)->unk_12;
                            ((S_800C6B40_0 *)sprite)->unk_14 = (u16)(((S_800C6B40_0 *)sprite)->unk_14 & 0x7FFF);
                            clut += ((S_800C6B40_1 *)part)->unk_06;
                            ((QuadPrim *)packet_next)->clut = (s16)clut;
                            if (((S_800C6B40_0 *)sprite)->unk_10 != 0) {
                                tpage = ((S_800C6B40_0 *)sprite)->unk_10 + (((S_800C6B40_1 *)part)->unk_04 & 0xFF9F);
                            } else {
                                tpage = ((S_800C6B40_1 *)part)->unk_04;
                            }
                            ((QuadPrim *)packet_next)->tpage = tpage;
                            ((QuadPrim *)packet_next)->unk_04.color = (s32)((S_800C6B40_0 *)sprite)->unk_0C.at00.v;
                            ((QuadPrim *)packet_next)->unk_04.at03.code = 0x2C;
                            draw_flags = *(u16 *)(scratch + 0x024);
                            if (draw_flags & 8) {
                                if (!(draw_flags & 4)) {
                                    command = 0x2C;
                                    ((QuadPrim *)packet_next)->unk_04.at03.code = command;
                                } else {
                                    command = 0x2E;
                                    ((QuadPrim *)packet_next)->unk_04.at03.code = command;
                                }
                            }
                            func_8006658C((u8 *)*(u32 *)(scratch + 0x020) + ((u32)*(u32 *)(scratch + 0x0C0) * 4),
                                packet_next);
                            packet_next += 0x28;
                        }
                        column += 1;
                        matrix_or_u += u_step;
                        top_x += top_x_step;
                        bottom_x += bottom_x_step;
                    } while (column < 4);
                    row += 1;
                    texture_v += v_step;
                    left_y += left_y_step;
                    saved_right_y = next_right_y;
                    next_right_y += right_y_step;
                    right_y = saved_right_y;
                } while (row < 4);
            } else {
                draw_callback = (s32 (*)(s32, void *, void *, void *, s32))((S_800C6B40_1 *)part)->unk_08.at00u.v;
                if (draw_callback != NULL) {
                    visible_or_result = draw_callback(context, position, sprite, part, packet_next);
                    kseg_base = 0x80000000;
                    if (visible_or_result > 0) {
                        part = (void *)(visible_or_result | kseg_base);
                    } else {
                        packet_next = visible_or_result;
                    }
                }
            }
            part_flags = (s8)((S_800C6B40_1 *)part)->unk_00;
            part += 0xC;
        } while (part_flags >= 0);
        func_80064A40();
    }
    *(s32 *)(*(u32 *)render_globals + 0x8D0) = packet_next;
}
