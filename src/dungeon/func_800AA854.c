#include "common.h"

typedef struct S_800AFFB4_0 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_800AFFB4_0;   /* arg0 in func_800AFFB4 */

typedef struct S_800AFFB4_1 {
    u8 pad_00[0x8];
    union { volatile s32 s32; u16 u16; } unk_08;   /* accessed as both */
    volatile s32 unk_0C;
    union { volatile s32 s32; u16 u16; } unk_10;   /* accessed as both */
    union { volatile s32 s32; u16 u16; } unk_14;   /* accessed as both */
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
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { s16 v; } at00p;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_F0;   /* overlapping accesses */
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { s16 v; } at00p;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_F4;   /* overlapping accesses */
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { s16 v; } at00p;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_F8;   /* overlapping accesses */
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { s16 v; } at00p;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_FC;   /* overlapping accesses */
    u8 pad_100[0x18];
    s32 unk_118;
} S_800AFFB4_1;   /* arg2 in func_800AFFB4 */

typedef struct S_800AFFB4_2_pre {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x1];
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
} S_800AFFB4_2_pre;   /* the near quad of the strip packet: StripPacket.near_quad, at packet_buffer + 4 */

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
} S_800AFFB4_2;   /* the far quad of the strip packet: StripPacket.far_quad, at packet_buffer + 0x50 */

typedef struct StripPacket {
    u8 pad_00[0x4];
    S_800AFFB4_2_pre near_quad;
    S_800AFFB4_2 far_quad;
} StripPacket;   /* packet_buffer: the two quads of one strip */

typedef struct StripQuad {
    u8 pad_00[0xC];
    s32 uv0;
    u8 pad_10[0x8];
    union { s32 word; u8 u; volatile s8 u_vol; } uv1;   /* accessed as both */
    u8 pad_1C[0x8];
    union { s16 half; struct { u8 u; volatile u8 v; } b; } uv2;   /* accessed as both */
    u8 pad_26[0xA];
    union { s16 half; struct { union { u8 u; volatile s8 u_vol; } u; volatile u8 v; } b; } uv3;   /* accessed as both */
} StripQuad;   /* one 0x34-byte quad of the strip packet */

typedef struct S_800AFFB4_3 {
    s16 unk_00;
    u16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 pad_08[0x4];
} S_800AFFB4_3;   /* texture entry data, 4 bytes into a TwelveByteEntry */

typedef struct TwelveByteEntry {
    u8 bytes[12];
} TwelveByteEntry;

extern s32 func_80065610();
extern void func_8006658C();
extern void func_8006671C();

/* Projects depth strips and queues visible textured quad pairs with distance shading. */
s32 func_800AFFB4(S_800AFFB4_0 *origin, void *unused, S_800AFFB4_1 *render_data_in, u8 *packet_buffer, s16 texture_arg) {
    s32 depth_step;
    s32 shade_uv;
    s32 shade_uv_2;
    s32 raw_height;
    register s32 shade_u ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 near_shade;
    s32 texture_height;
    s32 coord_bits;
    u8 edge_u;
    u8 edge_v;
    s32 vertex_value;
    s32 entry_v;
    s32 x_in_bounds;
    s32 near_mid_x;
    s32 texture_right;
    s32 far_mid_x;
    s32 near_mid_y;
    s32 far_mid_y;
    s32 visible_left;
    s32 visible_near;
    s32 visible_strips;
    TwelveByteEntry *texture_entry;
    s32 quad_index;
    s32 strip_index;
    s32 visible_right;
    u16 screen_y;
    u16 texture_index;
    u16 shade_offset;
    register u8 *uv_end ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_800AFFB4_3 *texture_info;

    (void)unused;
    visible_strips = 0;
    texture_index = texture_arg;
    shade_offset = origin->unk_08.s >= 0xE00;
    entry_v = origin->unk_08.u;
    coord_bits = entry_v - 0x6200;
    vertex_value = entry_v - 0x5400;
    render_data_in->unk_7C = coord_bits;
    render_data_in->unk_74 = coord_bits;
    render_data_in->unk_8C = vertex_value;
    render_data_in->unk_84 = vertex_value;
    for (strip_index = 0; strip_index < 0xE; strip_index++) {
        render_data_in->unk_74 += 0xE00;
        render_data_in->unk_7C += 0xE00;
        render_data_in->unk_84 += 0xE00;
        render_data_in->unk_8C += 0xE00;
        if (func_80065610((u8 *)render_data_in + 0x70, (u8 *)render_data_in + 0x78,
                (u8 *)render_data_in + 0x80, (u8 *)render_data_in + 0x88,
                (u8 *)render_data_in + 0xF0, (u8 *)render_data_in + 0xF4,
                (u8 *)render_data_in + 0xF8, (u8 *)render_data_in + 0xFC,
                (u8 *)render_data_in + 0x90, (u8 *)render_data_in + 0xC0,
                (u8 *)render_data_in + 0x94) > 0) {
            visible_near = 0;
            if ((u32)((render_data_in->unk_F0.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = render_data_in->unk_F0.at02.v + 0x20;
                visible_near = screen_y < 0x121U;
            }
            visible_right = 0;
            if ((u32)((render_data_in->unk_F4.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = render_data_in->unk_F4.at02.v + 0x20;
                visible_right = screen_y < 0x121U;
            }
            visible_left = 0;
            x_in_bounds = (u32)((render_data_in->unk_F8.at00.v + 0x20) & 0xFFFF) < 0x181U;
            visible_near |= visible_right;
            if (x_in_bounds) {
                screen_y = render_data_in->unk_F8.at02.v + 0x20;
                visible_left = screen_y < 0x121U;
            }
            visible_right = 0;
            x_in_bounds = (u32)((render_data_in->unk_FC.at00.v + 0x20) & 0xFFFF) < 0x181U;
            shade_uv_2 = visible_near | visible_left;
            visible_left = shade_uv_2;
            if (x_in_bounds) {
                screen_y = render_data_in->unk_FC.at02.v + 0x20;
                visible_right = screen_y < 0x121U;
            }
            if ((visible_left | visible_right) != 0) {
                ((StripPacket *)packet_buffer)->near_quad.unk_04 = render_data_in->unk_F0.at00u.v;
                ((StripPacket *)packet_buffer)->near_quad.unk_1C = render_data_in->unk_F8.at00u.v;
                ((StripPacket *)packet_buffer)->near_quad.unk_44 = render_data_in->unk_F4.at00u.v;
                ((StripPacket *)packet_buffer)->far_quad.unk_10 = render_data_in->unk_FC.at00u.v;
                near_mid_x = (render_data_in->unk_F0.at00p.v
                    + render_data_in->unk_F4.at00p.v) >> 1;
                ((StripPacket *)packet_buffer)->near_quad.unk_38 = near_mid_x;
                ((StripPacket *)packet_buffer)->near_quad.unk_10 = near_mid_x;
                far_mid_x = (render_data_in->unk_F8.at00p.v
                    + render_data_in->unk_FC.at00p.v) >> 1;
                ((StripPacket *)packet_buffer)->far_quad.unk_04 = far_mid_x;
                ((StripPacket *)packet_buffer)->near_quad.unk_28 = far_mid_x;
                near_mid_y = (render_data_in->unk_F0.at02u.v
                    + render_data_in->unk_F4.at02u.v) >> 1;
                ((StripPacket *)packet_buffer)->near_quad.unk_3A = near_mid_y;
                ((StripPacket *)packet_buffer)->near_quad.unk_12 = near_mid_y;
                far_mid_y = (render_data_in->unk_F8.at02u.v
                    + render_data_in->unk_FC.at02u.v) >> 1;
                ((StripPacket *)packet_buffer)->far_quad.unk_06 = far_mid_y;
                ((StripPacket *)packet_buffer)->near_quad.unk_2A = far_mid_y;
                depth_step = (s16)render_data_in->unk_74 % 3584;
                render_data_in->unk_90.s32 = depth_step;
                if (depth_step < 0) {
                    depth_step += 0xFF;
                }
                depth_step >>= 8;
                render_data_in->unk_90.s32 = depth_step;
                screen_y = shade_offset;
                if (screen_y != 0) {
                    render_data_in->unk_90.s32 = depth_step + 0x10;
                }
                shade_uv = 0x80;
                vertex_value = render_data_in->unk_90.u16;
                coord_bits = strip_index << 4;
                vertex_value += coord_bits;
                coord_bits = 0xE0;
                shade_u = coord_bits - vertex_value;
                near_shade = (s16)shade_u;
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
                ((StripPacket *)packet_buffer)->near_quad.unk_02 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_0E = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_42 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_36 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_01 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_0D = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_41 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_35 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_00 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_0C = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_40 = shade_uv;
                ((StripPacket *)packet_buffer)->near_quad.unk_34 = shade_uv;
                shade_uv = coord_bits >> 0x10;
                if (shade_uv >= 0x81) {
                    vertex_value = 0x80;
                } else {
                    if (shade_uv < 0) {
                        vertex_value = 0;
                    }
                }
                quad_index = 0;
                uv_end = packet_buffer + 0x31;
                ((StripPacket *)packet_buffer)->near_quad.unk_1A = vertex_value;
                ((StripPacket *)packet_buffer)->near_quad.unk_26 = vertex_value;
                ((StripPacket *)packet_buffer)->far_quad.unk_0E = vertex_value;
                ((StripPacket *)packet_buffer)->far_quad.unk_02 = vertex_value;
                ((StripPacket *)packet_buffer)->near_quad.unk_19 = vertex_value;
                ((StripPacket *)packet_buffer)->near_quad.unk_25 = vertex_value;
                ((StripPacket *)packet_buffer)->far_quad.unk_0D = vertex_value;
                ((StripPacket *)packet_buffer)->far_quad.unk_01 = vertex_value;
                ((StripPacket *)packet_buffer)->near_quad.unk_18 = vertex_value;
                ((StripPacket *)packet_buffer)->near_quad.unk_24 = vertex_value;
                ((StripPacket *)packet_buffer)->far_quad.unk_0C = vertex_value;
                ((StripPacket *)packet_buffer)->far_quad.unk_00 = vertex_value;
                texture_entry = (TwelveByteEntry *)render_data_in->unk_118 + (((strip_index & 1) << 1) + ((s16)texture_index << 2));
                texture_info = (S_800AFFB4_3 *)((u8 *)texture_entry + 4);
loop_0:
                func_8006671C(packet_buffer);
                render_data_in->unk_08.s32 = texture_info->unk_04;
                shade_u = render_data_in->unk_08.s32;
                render_data_in->unk_0C = texture_info->unk_05;
                shade_uv = render_data_in->unk_0C;
                render_data_in->unk_10.s32 = texture_info->unk_06;
                vertex_value = shade_uv;
                raw_height = texture_info->unk_07;
                shade_uv <<= 8;
                render_data_in->unk_0C = shade_uv;
                render_data_in->unk_14.s32 = raw_height;
                texture_right = render_data_in->unk_10.s32;
                texture_height = render_data_in->unk_14.s32;
                texture_right += shade_u;
                vertex_value += texture_height;
                vertex_value <<= 8;
                render_data_in->unk_14.s32 = vertex_value;
                vertex_value = shade_u;
                shade_u = (s32)packet_buffer;
                render_data_in->unk_10.s32 = texture_right;
                coord_bits = texture_info->unk_02;
                shade_uv += vertex_value;
                coord_bits <<= 0x10;
                shade_uv |= coord_bits;
                ((StripQuad *)(uv_end - 0x31))->uv0 = shade_uv;
                coord_bits = render_data_in->unk_0C;
                shade_uv = render_data_in->unk_10.s32;
                vertex_value = texture_info->unk_00;
                coord_bits += shade_uv;
                vertex_value <<= 0x10;
                coord_bits |= vertex_value;
                ((StripQuad *)(uv_end - 0x31))->uv1.word = coord_bits;
                coord_bits = render_data_in->unk_14.u16;
                vertex_value = render_data_in->unk_08.u16;
                coord_bits += vertex_value;
                ((StripQuad *)(uv_end - 0x31))->uv2.half = coord_bits;
                vertex_value = render_data_in->unk_14.u16;
                coord_bits = ((StripQuad *)(uv_end - 0x31))->uv1.u;
                shade_uv = render_data_in->unk_10.u16;
                coord_bits -= 1;
                vertex_value += shade_uv;
                ((StripQuad *)(uv_end - 0x31))->uv1.u_vol = coord_bits;
                ((StripQuad *)(uv_end - 0x31))->uv3.half = vertex_value;
                edge_u = ((StripQuad *)(uv_end - 0x31))->uv3.b.u.u;
                edge_v = ((StripQuad *)(uv_end - 0x31))->uv2.b.v;
                edge_u -= 1;
                edge_v -= 1;
                ((StripQuad *)(uv_end - 0x31))->uv3.b.u.u_vol = edge_u;
                ((StripQuad *)(uv_end - 0x31))->uv2.b.v = edge_v;
                coord_bits = ((StripQuad *)(uv_end - 0x31))->uv3.b.v;
                coord_bits -= 1;
                ((StripQuad *)(uv_end - 0x31))->uv3.b.v = coord_bits;
                shade_uv = (u32)(texture_entry - (TwelveByteEntry *)render_data_in->unk_118) / 12;
                texture_info += 1;
                uv_end += 0x34;
                texture_entry += 1;
                func_8006658C(render_data_in->unk_20 + ((u32)shade_uv * 4),
                    (void *)shade_u, texture_height);
                packet_buffer += 0x34;
                quad_index += 1;
                if (quad_index < 2)
                    goto loop_0;
                visible_strips += 1;
            }
        }
    }
    coord_bits = 0;
    if (visible_strips != 0) {
        coord_bits = (s32)packet_buffer;
    }
    return coord_bits;
}
