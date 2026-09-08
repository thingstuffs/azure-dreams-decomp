#include "common.h"

typedef struct S_800AFFB4_0 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_800AFFB4_0;   /* arg0 in func_800AFFB4 */

typedef struct S_800AFFB4_1 {
    u8 pad_00[0x8];
    union { volatile s32 s32; volatile u16 u16; } unk_08;   /* accessed as both */
    volatile s32 unk_0C;
    union { volatile s32 s32; volatile u16 u16; } unk_10;   /* accessed as both */
    union { volatile s32 s32; volatile u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    s32 unk_20;
    u8 pad_24[0x50];
    u16 unk_74;
    u8 pad_76[0x6];
    u16 unk_7C;
    u8 pad_7E[0x6];
    u16 unk_84;
    u8 pad_86[0x6];
    u16 unk_8C;
    u8 pad_8E[0x2];
    union { s32 s32; u16 u16; } unk_90;   /* accessed as both */
    u8 pad_94[0x5C];
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { s16 v; } at00p; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_F0;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { s16 v; } at00p; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_F4;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { s16 v; } at00p; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_F8;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { s16 v; } at00p; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_FC;   /* overlapping accesses */
    u8 pad_100[0x18];
    s32 unk_118;
} S_800AFFB4_1;   /* arg2 in func_800AFFB4 */

typedef struct S_800AFFB4_2_pre {
    s8 unk_00;
    u8 pad_01[0x3];
    s32 unk_04;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x4];
    s8 unk_18;
    s8 unk_19;
    s8 unk_1A;
    u8 pad_1B[0x1];
    s32 unk_1C;
    u8 pad_20[0x4];
    s8 unk_24;
    s8 unk_25;
    s8 unk_26;
    u8 pad_27[0x1];
    s16 unk_28;
    s16 unk_2A;
    u8 pad_2C[0x8];
    s8 unk_34;
    s8 unk_35;
    s8 unk_36;
    u8 pad_37[0x1];
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x4];
    s8 unk_40;
    s8 unk_41;
    s8 unk_42;
    u8 pad_43[0x1];
    s32 unk_44;
    u8 pad_48[0x4];
} S_800AFFB4_2_pre;   /* the 0x4C bytes before var_s2 in func_800AFFB4, addressed as var_s2[-1] */

typedef struct S_800AFFB4_2 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x1];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s32 unk_10;
} S_800AFFB4_2;   /* var_s2 in func_800AFFB4 */

typedef struct S_800AFFB4_3 {
    s16 unk_00;
    u16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
} S_800AFFB4_3;   /* var_s3 in func_800AFFB4 */

typedef struct S_800AFFB4_4_pre {
    union { volatile u8 v; volatile s8 v2; } unk_00;   /* accessed as both */
    u8 pad_01[0xC];
    volatile u8 unk_0D;
    u8 pad_0E[0xA];
    union { volatile u8 v; volatile s8 v2; } unk_18;   /* accessed as both */
} S_800AFFB4_4_pre;   /* the 0x19 bytes before var_s0 in func_800AFFB4, addressed as var_s0[-1] */

typedef struct S_800AFFB4_4 {
    volatile u8 unk_00;
} S_800AFFB4_4;   /* var_s0 in func_800AFFB4 */



typedef struct ShortArg {
    u16 value;
} ShortArg;

typedef struct TwelveByteEntry {
    u8 bytes[12];
} TwelveByteEntry;

extern s32 func_80065610();
extern void func_8006658C();
extern void func_8006671C();

/* Projects depth strips and queues visible textured quad pairs with distance shading. */
s32 func_800AFFB4(void *origin, void *unused, void *render_data_in, u8 *packet_buffer, volatile ShortArg texture_arg) {
    s32 depth_step;
    register s32 shade_uv ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 raw_height;
    register s32 shade_u ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 near_shade;
    s32 texture_height;
    register s32 coord_bits ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 vertex_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 x_in_bounds;
    s32 near_mid_x;
    s32 texture_right;
    s32 far_mid_x;
    s32 near_mid_y;
    s32 far_mid_y;
    s32 visible_left;
    s32 visible_near;
    register void *render_data ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 visible_strips;
    TwelveByteEntry *texture_entry;
    s32 quad_index;
    register u8 *packet ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 strip_index;
    s32 packet_end;
    s32 visible_right;
    u16 screen_y;
    s32 depth_flag;
    u16 texture_index;
    u16 shade_offset;
    u32 bucket_index;
    register u8 *uv_end ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u8 *far_vertex;
    register u8 *texture_info ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    (void)unused;
    render_data = render_data_in;
    packet = packet_buffer;
    visible_strips = 0;
    strip_index = 0;
    far_vertex = packet + 0x50;
    ASM_KEEP(render_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    depth_flag = ((S_800AFFB4_0 *)origin)->unk_08.s;
    depth_flag = depth_flag < 0xE00;
    texture_index = texture_arg.value;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    vertex_value = ((S_800AFFB4_0 *)origin)->unk_08.u;
    depth_flag ^= 1;
    shade_offset = depth_flag;
    coord_bits = vertex_value - 0x6200;
    vertex_value -= 0x5400;
    ((S_800AFFB4_1 *)render_data)->unk_7C = coord_bits;
    ((S_800AFFB4_1 *)render_data)->unk_74 = coord_bits;
    ((S_800AFFB4_1 *)render_data)->unk_8C = vertex_value;
    ((S_800AFFB4_1 *)render_data)->unk_84 = vertex_value;
next_strip:
    ((S_800AFFB4_1 *)render_data)->unk_74 = ((S_800AFFB4_1 *)render_data)->unk_74 + 0xE00;
    ((S_800AFFB4_1 *)render_data)->unk_7C = ((S_800AFFB4_1 *)render_data)->unk_7C + 0xE00;
    ((S_800AFFB4_1 *)render_data)->unk_84 = ((S_800AFFB4_1 *)render_data)->unk_84 + 0xE00;
    ((S_800AFFB4_1 *)render_data)->unk_8C = ((S_800AFFB4_1 *)render_data)->unk_8C + 0xE00;
    if (func_80065610((u8 *)render_data + 0x70, (u8 *)render_data + 0x78,
            (u8 *)render_data + 0x80, (u8 *)render_data + 0x88,
            (u8 *)render_data + 0xF0, (u8 *)render_data + 0xF4,
            (u8 *)render_data + 0xF8, (u8 *)render_data + 0xFC,
            (u8 *)render_data + 0x90, (u8 *)render_data + 0xC0,
            (u8 *)render_data + 0x94) > 0) {
        visible_near = 0;
        if ((u32)((((S_800AFFB4_1 *)render_data)->unk_F0.at00.v + 0x20) & 0xFFFF) < 0x181U) {
            screen_y = ((S_800AFFB4_1 *)render_data)->unk_F0.at02.v + 0x20;
            visible_near = screen_y < 0x121U;
        }
        visible_right = 0;
        if ((u32)((((S_800AFFB4_1 *)render_data)->unk_F4.at00.v + 0x20) & 0xFFFF) < 0x181U) {
            screen_y = ((S_800AFFB4_1 *)render_data)->unk_F4.at02.v + 0x20;
            visible_right = screen_y < 0x121U;
        }
        visible_left = 0;
        x_in_bounds = (u32)((((S_800AFFB4_1 *)render_data)->unk_F8.at00.v + 0x20) & 0xFFFF) < 0x181U;
        visible_near |= visible_right;
        if (x_in_bounds) {
            screen_y = ((S_800AFFB4_1 *)render_data)->unk_F8.at02.v + 0x20;
            visible_left = screen_y < 0x121U;
        }
        visible_right = 0;
        x_in_bounds = (u32)((((S_800AFFB4_1 *)render_data)->unk_FC.at00.v + 0x20) & 0xFFFF) < 0x181U;
        shade_uv = visible_near | visible_left;
        visible_left = shade_uv;
        if (x_in_bounds) {
            screen_y = ((S_800AFFB4_1 *)render_data)->unk_FC.at02.v + 0x20;
            visible_right = screen_y < 0x121U;
        }
        if ((visible_left | visible_right) != 0) {
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_04 = ((S_800AFFB4_1 *)render_data)->unk_F0.at00u.v;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_1C = ((S_800AFFB4_1 *)render_data)->unk_F8.at00u.v;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_44 = ((S_800AFFB4_1 *)render_data)->unk_F4.at00u.v;
            ((S_800AFFB4_2 *)far_vertex)->unk_10 = ((S_800AFFB4_1 *)render_data)->unk_FC.at00u.v;
            near_mid_x = (((S_800AFFB4_1 *)render_data)->unk_F0.at00p.v + ((S_800AFFB4_1 *)render_data)->unk_F4.at00p.v) >> 1;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_38 = near_mid_x;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_10 = near_mid_x;
            far_mid_x = (((S_800AFFB4_1 *)render_data)->unk_F8.at00p.v + ((S_800AFFB4_1 *)render_data)->unk_FC.at00p.v) >> 1;
            ((S_800AFFB4_2 *)far_vertex)->unk_04 = far_mid_x;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_28 = far_mid_x;
            near_mid_y = (((S_800AFFB4_1 *)render_data)->unk_F0.at02u.v + ((S_800AFFB4_1 *)render_data)->unk_F4.at02u.v) >> 1;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_3A = near_mid_y;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_12 = near_mid_y;
            far_mid_y = (((S_800AFFB4_1 *)render_data)->unk_F8.at02u.v + ((S_800AFFB4_1 *)render_data)->unk_FC.at02u.v) >> 1;
            ((S_800AFFB4_2 *)far_vertex)->unk_06 = far_mid_y;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_2A = far_mid_y;
            depth_step = (s16)((S_800AFFB4_1 *)render_data)->unk_74 % 3584;
            ((S_800AFFB4_1 *)render_data)->unk_90.s32 = depth_step;
            if (depth_step < 0) {
                depth_step += 0xFF;
            }
            depth_step >>= 8;
            ((S_800AFFB4_1 *)render_data)->unk_90.s32 = depth_step;
            coord_bits = shade_offset;
            if (coord_bits != 0) {
                ((S_800AFFB4_1 *)render_data)->unk_90.s32 = depth_step + 0x10;
            }
            shade_uv = 0x80;
            vertex_value = ((S_800AFFB4_1 *)render_data)->unk_90.u16;
            coord_bits = strip_index << 4;
            vertex_value += coord_bits;
            coord_bits = 0xE0;
            shade_u = coord_bits - vertex_value;
            coord_bits = shade_u << 0x10;
            near_shade = coord_bits >> 0x10;
            vertex_value = shade_u;
            if (near_shade < 0x81) {
                shade_uv = shade_u;
                if (near_shade < 0) {
                    shade_uv = 0;
                }
            }
            coord_bits = vertex_value - 0x10;
            vertex_value = coord_bits;
            coord_bits <<= 0x10;
            (*(s8 *)((u8 *)far_vertex + -0x4A)) = shade_uv;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_0E = shade_uv;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_42 = shade_uv;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_36 = shade_uv;
            (*(s8 *)((u8 *)far_vertex + -0x4B)) = shade_uv;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_0D = shade_uv;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_41 = shade_uv;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_35 = shade_uv;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_00 = shade_uv;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_0C = shade_uv;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_40 = shade_uv;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_34 = shade_uv;
            shade_uv = coord_bits >> 0x10;
            if (shade_uv >= 0x81) {
                vertex_value = 0x80;
            } else {
                quad_index = 0;
                if (shade_uv < 0) {
                    vertex_value = 0;
                }
            }
            quad_index = 0;
            uv_end = packet + 0x31;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_1A = vertex_value;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_26 = vertex_value;
            ((S_800AFFB4_2 *)far_vertex)->unk_0E = vertex_value;
            ((S_800AFFB4_2 *)far_vertex)->unk_02 = vertex_value;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_19 = vertex_value;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_25 = vertex_value;
            ((S_800AFFB4_2 *)far_vertex)->unk_0D = vertex_value;
            ((S_800AFFB4_2 *)far_vertex)->unk_01 = vertex_value;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_18 = vertex_value;
            ((S_800AFFB4_2_pre *)far_vertex)[-1].unk_24 = vertex_value;
            ((S_800AFFB4_2 *)far_vertex)->unk_0C = vertex_value;
            ((S_800AFFB4_2 *)far_vertex)->unk_00 = vertex_value;
            vertex_value = strip_index & 1;
            ASM_KEEP(vertex_value);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            vertex_value <<= 1;
            coord_bits = (s32)(texture_index << 0x10) >> 0xE;
            vertex_value += coord_bits;
            coord_bits = vertex_value << 1;
            coord_bits += vertex_value;
            vertex_value = ((S_800AFFB4_1 *)render_data)->unk_118;
            coord_bits <<= 2;
            texture_entry = (TwelveByteEntry *)((u8 *)vertex_value + coord_bits);
            texture_info = (u8 *)texture_entry + 4;
            do {
                func_8006671C(packet);
                ((S_800AFFB4_1 *)render_data)->unk_08.s32 = ((S_800AFFB4_3 *)texture_info)->unk_04;
                shade_u = ((S_800AFFB4_1 *)render_data)->unk_08.s32;
                ((S_800AFFB4_1 *)render_data)->unk_0C = ((S_800AFFB4_3 *)texture_info)->unk_05;
                shade_uv = ((S_800AFFB4_1 *)render_data)->unk_0C;
                ((S_800AFFB4_1 *)render_data)->unk_10.s32 = ((S_800AFFB4_3 *)texture_info)->unk_06;
                vertex_value = shade_uv;
                raw_height = ((S_800AFFB4_3 *)texture_info)->unk_07;
                shade_uv <<= 8;
                ((S_800AFFB4_1 *)render_data)->unk_0C = shade_uv;
                ((S_800AFFB4_1 *)render_data)->unk_14.s32 = raw_height;
                texture_right = ((S_800AFFB4_1 *)render_data)->unk_10.s32;
                texture_height = ((S_800AFFB4_1 *)render_data)->unk_14.s32;
                texture_right += shade_u;
                vertex_value += texture_height;
                vertex_value <<= 8;
                ((S_800AFFB4_1 *)render_data)->unk_14.s32 = vertex_value;
                vertex_value = shade_u;
                ASM_KEEP(vertex_value);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ((S_800AFFB4_1 *)render_data)->unk_10.s32 = texture_right;
                coord_bits = ((S_800AFFB4_3 *)texture_info)->unk_02;
                shade_uv += vertex_value;
                coord_bits <<= 0x10;
                shade_uv |= coord_bits;
                (*(s32 *)((u8 *)uv_end + -0x25)) = shade_uv;
                coord_bits = ((S_800AFFB4_1 *)render_data)->unk_0C;
                shade_uv = ((S_800AFFB4_1 *)render_data)->unk_10.s32;
                vertex_value = ((S_800AFFB4_3 *)texture_info)->unk_00;
                coord_bits += shade_uv;
                vertex_value <<= 0x10;
                coord_bits |= vertex_value;
                (*(s32 *)((u8 *)uv_end + -0x19)) = coord_bits;
                coord_bits = ((S_800AFFB4_1 *)render_data)->unk_14.u16;
                vertex_value = ((S_800AFFB4_1 *)render_data)->unk_08.u16;
                ASM_KEEP(coord_bits);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                coord_bits += vertex_value;
                (*(volatile s16 *)((u8 *)uv_end + -0xD)) = coord_bits;
                vertex_value = ((S_800AFFB4_1 *)render_data)->unk_14.u16;
                coord_bits = ((S_800AFFB4_4_pre *)uv_end)[-1].unk_00.v;
                shade_uv = ((S_800AFFB4_1 *)render_data)->unk_10.u16;
                ASM_KEEP(coord_bits);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                coord_bits -= 1;
                vertex_value += shade_uv;
                ((S_800AFFB4_4_pre *)uv_end)[-1].unk_00.v2 = coord_bits;
                (*(volatile s16 *)((u8 *)uv_end + -1)) = vertex_value;
                coord_bits = ((S_800AFFB4_4_pre *)uv_end)[-1].unk_18.v;
                vertex_value = ((S_800AFFB4_4_pre *)uv_end)[-1].unk_0D;
                coord_bits -= 1;
                vertex_value -= 1;
                ((S_800AFFB4_4_pre *)uv_end)[-1].unk_18.v2 = coord_bits;
                ((S_800AFFB4_4_pre *)uv_end)[-1].unk_0D = vertex_value;
                coord_bits = ((S_800AFFB4_4 *)uv_end)->unk_00;
                coord_bits -= 1;
                ((S_800AFFB4_4 *)uv_end)->unk_00 = coord_bits;
                vertex_value = ((S_800AFFB4_1 *)render_data)->unk_118;
                bucket_index = (u32)(texture_entry - (TwelveByteEntry *)vertex_value) / 12;
                far_vertex += 0x34;
                quad_index += 1;
                shade_u = (s32)packet;
                texture_info += 0xC;
                uv_end += 0x34;
                texture_entry += 1;
                func_8006658C(((S_800AFFB4_1 *)render_data)->unk_20 + (bucket_index * 4),
                    (void *)shade_u, texture_height);
                packet += 0x34;
            } while (quad_index < 2);
            visible_strips += 1;
        }
    }
    strip_index += 1;
    if (strip_index >= 0xE) {
        packet_end = 0;
        if (visible_strips != 0) {
            packet_end = (s32)packet;
        }
        return packet_end;
    }
    goto next_strip;
}
