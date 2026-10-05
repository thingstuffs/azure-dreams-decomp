#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct S_800CEFB8_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CEFB8_0;   /* global_base in func_800CEFB8 */

typedef struct S_800CEFB8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
} S_800CEFB8_1;   /* arg2_hold in func_800CEFB8 */

typedef struct S_800CEFB8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800CEFB8_2;   /* arg1 in func_800CEFB8 */

typedef struct S_800CEFB8_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800CEFB8_3;   /* (s32 *)end_depth in func_800CEFB8 */


typedef struct S_SCRATCH {
    u16 unk_000;
    u16 unk_002;
    u16 unk_004;
    u8 pad_006[0x2];
    union {
        s32 s32;
        u16 u16;
    } unk_008;
    s32 unk_00C;
    union {
        s32 s32;
        u16 u16;
    } unk_010;
    union {
        s32 s32;
        u16 u16;
    } unk_014;
    u8 pad_018[0x8];
    s32 unk_020;
    u16 unk_024;
    u8 pad_026[0xA];
    s32 unk_030;
    s32 unk_034;
    s32 unk_038;
    u8 pad_03C[0x34];
    u16 unk_070;
    u16 unk_072;
    u16 unk_074;
    u8 pad_076[0x2];
    u16 unk_078;
    u16 unk_07A;
    u16 unk_07C;
    u8 pad_07E[0x2];
    u16 unk_080;
    u16 unk_082;
    u16 unk_084;
    u8 pad_086[0x2];
    u16 unk_088;
    u16 unk_08A;
    u16 unk_08C;
    u8 pad_08E[0x2A];
    u16 unk_0B8;
    u16 unk_0BA;
    u8 pad_0BC[0x4];
    s32 unk_0C0;
    u8 pad_0C4[0x20];
    s32 unk_0E4;
    s32 unk_0E8;
    s32 unk_0EC;
    u16 unk_0F0;
    u16 unk_0F2;
    u8 pad_0F4[0xC];
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
    u8 pad_106[0x2];
    u16 unk_108;
    u16 unk_10A;
    u8 pad_10C[0x2];
    u16 unk_10E;
} S_SCRATCH;

typedef struct S_800CEFB8_5 {
    void * unk_00;
    u8 pad_04[0xB4];
    s16 unk_B8;
    u8 pad_BA[0xA];
    s16 unk_C4;
    s16 unk_C6;
    s16 unk_C8;
} S_800CEFB8_5;   /* temp_s7 in func_800CEFB8 */

typedef struct S_800CEFB8_6 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_800CEFB8_6;   /* part in func_800CEFB8 */

typedef struct S_800CEFB8_8 {
    u8 pad_00[0x3];
    s8 unk_03;
    s32 unk_04;
    union { u16 u; s16 s; } unk_08;   /* accessed as both */
    u16 unk_0A;
    s16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    union { s16 s16; u8 u8; } unk_14;   /* accessed as both */
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    union { struct { s16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_1C;   /* overlapping accesses */
    u8 pad_1E[0x2];
    union { u16 u; s16 s; } unk_20;   /* accessed as both */
    u16 unk_22;
    union {
        struct { s16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
} S_800CEFB8_8;   /* packet in func_800CEFB8 */

typedef struct S_800CEFB8_9 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CEFB8_9;   /* ((S_800CEFB8_5 *)temp_s7)->unk_00 in func_800CEFB8 */


M2C_UNK func_80064840();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
s32 func_80065420();
M2C_UNK func_800654B0();
M2C_UNK func_80065820();
u16 func_80065F90();
M2C_UNK func_8006658C();
extern s32 D_8006CD30[];

/* Projects sprite parts between two endpoints and queues visible textured quads. */
void func_800CEFB8(void *unused, void *endpoints, void *sprite, s16 depth_bias, s16 orient_mode) {
    s32 camera_rot_x;
    s32 camera_rot_z;
    s32 camera_rot_y;
    s32 rotation_z;
    s32 visible_abc;
    s32 visible_ab;
    s16 draw_mode;
    s32 mean_depth;
    s32 sort_depth;
    s32 coord_work;
    s32 coord_end;
    s32 visible_c;
    s32 visible_a;
    s32 visible_b;
    s32 visible_d;
    u16 end_y;
    u16 end_x;
    u16 start_x;
    u16 second_coord;
    s32 start_depth;
    s32 end_depth;
    s32 otz2;
    s32 origin_x;
    s32 origin_y;
    u16 sprite_flags;
    u16 segment_angle;
    s32 texture_override;
    u16 packet_code;
    u8 right_u;
    u8 bottom_v;
    S_800CEFB8_8 *draw_packet;
    void *global_base;
    S_800CEFB8_6 *part;
    void *render_state;
    S_800CEFB8_8 *packet_next;
    
    S_SCRATCH *scratch;
    scratch = (S_SCRATCH *)0x1F800000;
    global_base = *(void **)((s8 *)(&gameWork));

#define SPA(off) ((void *)((u8 *)scratch + (off)))

    scratch->unk_0EC = 0;
    scratch->unk_08C = 0;
    scratch->unk_084 = 0;
    scratch->unk_07C = 0;
    scratch->unk_074 = 0;
    scratch->unk_020 = global_base + 0xB0;
    packet_next = ((S_800CEFB8_0 *)global_base)->unk_8D0;
    ((S_800CEFB8_1 *)sprite)->unk_14 = (u16) (((S_800CEFB8_1 *)sprite)->unk_14 | 0x8000);
    scratch->unk_000 = (u16) ((S_800CEFB8_2 *)endpoints)->unk_02;
    scratch->unk_002 = (u16) ((S_800CEFB8_2 *)endpoints)->unk_06;
    render_state = (void *)&gameWork;
    scratch->unk_004 = (u16) ((S_800CEFB8_2 *)endpoints)->unk_0A;
    start_depth = func_80065420((void *)0x1F800000, (void *)0x1F8000B8, (void *)0x1F800090, (void *)0x1F800094);
    scratch->unk_0C0 = start_depth;
    second_coord = ((S_800CEFB8_2 *)endpoints)->unk_0E;
    scratch->unk_000 = second_coord;
    second_coord = ((S_800CEFB8_2 *)endpoints)->unk_12;
    scratch->unk_002 = second_coord;
    second_coord = ((S_800CEFB8_2 *)endpoints)->unk_16;
    scratch->unk_004 = second_coord;
    otz2 = func_80065420((void *)scratch, (void *)0x1F8000F0, (void *)0x1F800090, (void *)0x1F800094);
    end_y = scratch->unk_0F2;
    packet_code = scratch->unk_0BA;
    end_x = scratch->unk_0F0;
    start_x = scratch->unk_0B8;
    scratch->unk_0C0 = (s32)(scratch->unk_0C0 + otz2) >> 1;
    scratch->unk_10E = func_80065F90((s16)end_y - (s16)packet_code,
                                (s16)end_x - (s16)start_x,
                                (s16)end_x);
    end_depth = (s32)D_8006CD30;
    mean_depth = scratch->unk_0C0;
    ((S_800CEFB8_3 *)(s32 *)end_depth)->unk_1C = (s32) (mean_depth * 4);
    sort_depth = mean_depth - depth_bias;
    scratch->unk_0C0 = sort_depth;
    draw_mode = orient_mode;
    if ((u32) sort_depth < 0x1E0U) {
        func_800649A0();
        scratch->unk_0B8 -= 0xA0;
        coord_end = scratch->unk_0BA;
        scratch->unk_0BA = coord_end - 0x78;
        scratch->unk_0F0 -= 0xA0;
        scratch->unk_0F2 -= 0x78;
        camera_rot_x = ((S_800CEFB8_5 *)render_state)->unk_C4;
        camera_rot_z = ((S_800CEFB8_5 *)render_state)->unk_C6;
        camera_rot_y = ((S_800CEFB8_5 *)render_state)->unk_C8;
        scratch->unk_030 = camera_rot_x;
        scratch->unk_034 = camera_rot_z;
        scratch->unk_038 = camera_rot_y;
        scratch->unk_100 = (u16) ((S_800CEFB8_1 *)sprite)->unk_16;
        rotation_z = (((S_800CEFB8_1 *)sprite)->unk_1A - camera_rot_z) + ((S_800CEFB8_5 *)render_state)->unk_B8;
        if (orient_mode == 0) {
            segment_angle = scratch->unk_10E;
            rotation_z += (s16)segment_angle;
        }
        {
            s32 rotation_y;
            scratch->unk_104 = rotation_z;
            rotation_y = ((S_800CEFB8_1 *)sprite)->unk_18;
            scratch->unk_102 = (s16) ((((u16) scratch->unk_038 + 0x100) & 0x1FF) + (s16) (rotation_y - 0x100));
            origin_x = ((S_800CEFB8_1 *)sprite)->unk_20;
            scratch->unk_0E4 = (s32) origin_x;
            scratch->unk_108 = origin_x;
            origin_y = ((S_800CEFB8_1 *)sprite)->unk_22;
            scratch->unk_0E8 = (s32) origin_y;
            scratch->unk_10A = origin_y;
            func_80065820((void *)0x1F800100, (void *)0x1F8000D0);
        }
        {
            s32 scale_x;
            s32 scale_y;
            s32 scale_z;
            scale_x = ((S_800CEFB8_1 *)sprite)->unk_1C;
            scratch->unk_030 = scale_x;
            scale_y = ((S_800CEFB8_1 *)sprite)->unk_1E;
            scale_z = 0x1000;
            scratch->unk_038 = scale_z;
            scratch->unk_034 = scale_y;
            func_80064BC0((void *)0x1F8000D0, (void *)0x1F800030);
        }
        func_80064840((s32 *)end_depth, (void *)0x1F8000D0, (void *)0x1F800050);
        func_80064D80((void *)0x1F800050);
        func_80064CF0((void *)0x1F800050);
        part = ((S_800CEFB8_1 *)sprite)->unk_08;
        scratch->unk_024 = (u16) ((S_800CEFB8_1 *)sprite)->unk_14;
        for (;;) {
        if (!(part->unk_00 & 0x20)) {
            scratch->unk_008.s32 = (s32) part->unk_08;
            scratch->unk_00C = (s32) part->unk_09;
            scratch->unk_010.s32 = (s32) part->unk_0A;
            scratch->unk_014.s32 = (s32) part->unk_0B;
            {
                s16 edge_coord;
                s8 part_coord;
                u16 axis_adjust;
                s32 axis_extent;
                if ((part->unk_00 ^ scratch->unk_024) & 1) {
                    part_coord = part->unk_02;
                    axis_adjust = scratch->unk_108;
                    axis_extent = (u16) scratch->unk_010.s32;
                    edge_coord = -part_coord - axis_adjust;
                    scratch->unk_080 = edge_coord;
                    scratch->unk_070 = edge_coord;
                    edge_coord -= axis_extent;
                    scratch->unk_088 = edge_coord;
                    scratch->unk_078 = edge_coord;
                } else {
                    part_coord = part->unk_02;
                    axis_adjust = scratch->unk_108;
                    axis_extent = (u16) scratch->unk_010.s32;
                    edge_coord = part_coord - axis_adjust;
                    scratch->unk_080 = edge_coord;
                    scratch->unk_070 = edge_coord;
                    edge_coord += axis_extent;
                    scratch->unk_088 = edge_coord;
                    scratch->unk_078 = edge_coord;
                }
            }
            {
                s16 edge_coord;
                s8 part_coord;
                u16 axis_adjust;
                s32 axis_extent;
                if ((part->unk_00 ^ scratch->unk_024) & 2) {
                    part_coord = part->unk_03;
                    axis_adjust = scratch->unk_10A;
                    axis_extent = (u16) scratch->unk_014.s32;
                    edge_coord = -part_coord - axis_adjust;
                    scratch->unk_07A = edge_coord;
                    scratch->unk_072 = edge_coord;
                    edge_coord -= axis_extent;
                    scratch->unk_08A = edge_coord;
                    scratch->unk_082 = edge_coord;
                } else {
                    part_coord = part->unk_03;
                    axis_adjust = scratch->unk_10A;
                    axis_extent = (u16) scratch->unk_014.s32;
                    edge_coord = part_coord - axis_adjust;
                    scratch->unk_07A = edge_coord;
                    scratch->unk_072 = edge_coord;
                    edge_coord += axis_extent;
                    scratch->unk_08A = edge_coord;
                    scratch->unk_082 = edge_coord;
                }
            }
            func_800654B0(SPA(0x70), SPA(0x78), SPA(0x80), SPA(0x88),
                          &packet_next->unk_08, &packet_next->unk_10, &packet_next->unk_18,
                          &packet_next->unk_20, SPA(0x90), SPA(0x94));
            if (draw_mode != 0) {
                if ((scratch->unk_0BA << 0x10) < (scratch->unk_0F2 << 0x10)) {
                    packet_next->unk_08.u = (u16) (packet_next->unk_08.u + scratch->unk_0B8);
                    packet_next->unk_10 = (u16) (packet_next->unk_10 + scratch->unk_0B8);
                    packet_next->unk_0A = (u16) (packet_next->unk_0A + scratch->unk_0BA);
                    packet_next->unk_12 = (u16) (packet_next->unk_12 + scratch->unk_0BA);
                    packet_next->unk_18 = (u16) (packet_next->unk_18 + scratch->unk_0F0);
                    packet_next->unk_20.u = (u16) (packet_next->unk_20.u + scratch->unk_0F0);
                    packet_next->unk_1A = (u16) (packet_next->unk_1A + scratch->unk_0F2);
                    goto coord_last;
                }
                packet_next->unk_18 = (u16) (packet_next->unk_18 + scratch->unk_0B8);
                packet_next->unk_20.u = (u16) (packet_next->unk_20.u + scratch->unk_0B8);
                packet_next->unk_1A = (u16) (packet_next->unk_1A + scratch->unk_0BA);
                packet_next->unk_22 = (u16) (packet_next->unk_22 + scratch->unk_0BA);
                packet_next->unk_08.u = (u16) (packet_next->unk_08.u + scratch->unk_0F0);
                packet_next->unk_10 = (u16) (packet_next->unk_10 + scratch->unk_0F0);
                packet_next->unk_0A = (u16) (packet_next->unk_0A + scratch->unk_0F2);
                packet_next->unk_12 = (u16) (packet_next->unk_12 + scratch->unk_0F2);
                goto coord_done;
            }
            packet_next->unk_18 = (u16) (packet_next->unk_18 + scratch->unk_0B8);
            packet_next->unk_1A = (u16) (packet_next->unk_1A + scratch->unk_0BA);
            packet_next->unk_10 = (u16) (packet_next->unk_10 + scratch->unk_0F0);
            packet_next->unk_12 = (u16) (packet_next->unk_12 + scratch->unk_0F2);
            packet_next->unk_08.u = (u16) (packet_next->unk_08.u + scratch->unk_0B8);
            packet_next->unk_0A = (u16) (packet_next->unk_0A + scratch->unk_0BA);
            packet_next->unk_20.u = (u16) (packet_next->unk_20.u + scratch->unk_0F0);
coord_last:
            packet_next->unk_22 = (u16) (packet_next->unk_22 + scratch->unk_0F2);
coord_done:
            visible_a = 0;
            if ((u32) ((packet_next->unk_08.u + 0x20) & 0xFFFF) < 0x181U) {
                coord_work = (packet_next->unk_0A + 0x20) & 0xFFFF;
                visible_a = (u32) coord_work < 0x121U;
            }
            visible_b = 0;
            if ((u32) ((packet_next->unk_10 + 0x20) & 0xFFFF) < 0x181U) {
                coord_work = (packet_next->unk_12 + 0x20) & 0xFFFF;
                visible_b = (u32) coord_work < 0x121U;
            }
            visible_c = 0;
            visible_ab = visible_a | visible_b;
            if ((u32) ((packet_next->unk_18 + 0x20) & 0xFFFF) < 0x181U) {
                coord_work = (packet_next->unk_1A + 0x20) & 0xFFFF;
                visible_c = (u32) coord_work < 0x121U;
            }
            visible_d = 0;
            visible_abc = visible_ab | visible_c;
            if ((u32) ((packet_next->unk_20.u + 0x20) & 0xFFFF) < 0x181U) {
                coord_work = (packet_next->unk_22 + 0x20) & 0xFFFF;
                visible_d = (u32) coord_work < 0x121U;
            }
            coord_work = visible_abc | visible_d;
            if (coord_work != 0) {
                packet_next->unk_03 = 9;
                ((S_800CEFB8_1 *)sprite)->unk_14 = (u16) (((S_800CEFB8_1 *)sprite)->unk_14 & 0x7FFF);
                coord_work = scratch->unk_010.s32;
                coord_end = scratch->unk_008.s32;
                coord_work -= 1;
                {
                    s32 total_coord = coord_work + coord_end;
                    coord_end = total_coord;
                }
                scratch->unk_010.s32 = coord_end;
                if (coord_end & 0x100) {
                    coord_work = coord_end - 1;
                    scratch->unk_010.s32 = coord_work;
                }
                coord_work = scratch->unk_014.s32;
                coord_end = scratch->unk_00C;
                coord_work -= 1;
                {
                    s32 total_coord = coord_work + coord_end;
                    coord_end = total_coord;
                }
                scratch->unk_014.s32 = coord_end;
                if (coord_end & 0x100) {
                    coord_work = coord_end - 1;
                    scratch->unk_014.s32 = coord_work;
                }
                scratch->unk_014.s32 <<= 8;
                scratch->unk_00C <<= 8;
                texture_override = ((S_800CEFB8_1 *)sprite)->unk_12;
                if (texture_override != 0) {
                    if (scratch->unk_024 & 0x100) {
                        packet_next->unk_0E = texture_override;
                        goto continuation_coords;
                    }
                    coord_work = part->unk_06;
                    {
                        s32 texture_sum = texture_override + coord_work;
                        coord_work = texture_sum;
                    }
                } else {
                    coord_work = (u16) part->unk_06;
                }
                packet_next->unk_0E = coord_work;
continuation_coords:
                packet_next->unk_0C = (s16) ((u16) scratch->unk_00C + (u16) scratch->unk_008.s32);
                packet_next->unk_14.s16 = (s16) ((u16) scratch->unk_00C + (u16) scratch->unk_010.s32);
                texture_override = ((S_800CEFB8_1 *)sprite)->unk_10;
                if (texture_override != 0) {
                    coord_work = part->unk_04;
                    coord_work &= 0xFF9F;
                    {
                        s32 texture_sum = texture_override + coord_work;
                        coord_work = texture_sum;
                    }
                } else {
                    coord_work = (u16) part->unk_04;
                }
                packet_next->unk_16 = coord_work;
                {
                    s32 left_x;
                    s32 packed_uv;
                    s32 right_uv;
                    packet_next->unk_1C.at00.v = (s16) (scratch->unk_014.u16 | scratch->unk_008.u16);
                    left_x = packet_next->unk_08.s;
                    packed_uv = scratch->unk_014.u16;
                    right_uv = scratch->unk_010.u16;
                    packed_uv |= right_uv;
                    packet_next->unk_24.at00.v = (s16) packed_uv;
                    if (packet_next->unk_20.s < left_x) {
                        right_u = packet_next->unk_24.at00u.v;
                        packet_next->unk_24.at00u.v = (u8) (right_u + 0xFF);
                        packet_next->unk_14.u8 = right_u;
                    }
                }
                if ((s16) packet_next->unk_0A > (s16) packet_next->unk_22) {
                    bottom_v = packet_next->unk_24.at01.v;
                    packet_next->unk_24.at01.v = (u8) (bottom_v + 0xFF);
                    packet_next->unk_1C.at01.v = bottom_v;
                }
                packet_code = part->unk_01;
                ((S_800CEFB8_1 *)sprite)->unk_0C.at03.v = packet_code;
                sprite_flags = scratch->unk_024;
                if (sprite_flags & 8) {
                    if (sprite_flags & 4) {
                        coord_work = packet_code | 2;
                    } else {
                        coord_work = packet_code & 0xFD;
                    }
                    ((S_800CEFB8_1 *)sprite)->unk_0C.at03.v = coord_work;
                }
                draw_packet = packet_next;
                packet_next->unk_04 = (s32) ((S_800CEFB8_1 *)sprite)->unk_0C.at00.v;
                packet_next = packet_next + 1;
                func_8006658C(scratch->unk_020 + (scratch->unk_0C0 * 4), draw_packet);
            }
        }
        if ((s8) part->unk_00 < 0) {
            break;
        }
        part = part + 1;
        }
        func_80064A40();
    }
    ((S_800CEFB8_9 *)(((S_800CEFB8_5 *)render_state)->unk_00))->unk_8D0 = packet_next;
}
