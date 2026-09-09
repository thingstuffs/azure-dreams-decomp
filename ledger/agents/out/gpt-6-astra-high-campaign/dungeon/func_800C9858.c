#include "common.h"
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
} S_800CEFB8_3;   /* coeff_base in func_800CEFB8 */

typedef struct S_800CEFB8_4 {
    u8 pad_00[0xB8];
    volatile u16 unk_B8;
    volatile u16 unk_BA;
    u8 pad_BC[0x34];
    volatile u16 unk_F0;
    volatile u16 unk_F2;
    u8 pad_F4[0x14];
    volatile u16 unk_108;
    volatile u16 unk_10A;
} S_800CEFB8_4;   /* scratch in func_800CEFB8 */

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
} S_800CEFB8_6;   /* temp_s4 in func_800CEFB8 */

typedef struct S_800CEFB8_7 {
    u8 unk_00;
    volatile u8 unk_01;
    volatile u8 unk_02;
    u8 pad_03[0x4];
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
} S_800CEFB8_7;   /* temp_s1 in func_800CEFB8 */

typedef struct S_800CEFB8_8_pre {
    s8 unk_00;
} S_800CEFB8_8_pre;   /* the 0x1 bytes before temp_s0 in func_800CEFB8, addressed as temp_s0[-1] */

typedef struct S_800CEFB8_8 {
    s32 unk_00;
    union { u16 u; s16 s; } unk_04;   /* accessed as both */
    u16 unk_06;
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s16; u8 u8; } unk_10;   /* accessed as both */
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    union { struct { s16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_18;   /* overlapping accesses */
    u8 pad_1A[0x2];
    union { u16 u; s16 s; } unk_1C;   /* accessed as both */
    u16 unk_1E;
    union { struct { s16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_20;   /* overlapping accesses */
} S_800CEFB8_8;   /* temp_s0 in func_800CEFB8 */

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
extern s8 D_80083160[];

/* Projects sprite parts between two endpoints and queues visible textured quads. */
void func_800CEFB8(void *unused, void *endpoints, void *sprite, s16 depth_bias, s32 orient_mode) {
    s32 camera_rot_x;
    s32 camera_rot_z;
    s32 camera_rot_y;
    s32 rotation_z;
    s32 visible_abc;
    s32 visible_ab;
    s32 draw_mode;
    s32 mean_depth;
    s32 depth_offset;
    s32 sort_depth;
    register s32 coord_work ASM_REG("$2");
    register s32 coord_end ASM_REG("$3");
    s32 visible_c;
    s32 visible_a;
    s32 visible_b;
    s32 visible_d;
    u16 end_y;
    u16 start_y;
    u16 end_x;
    u16 start_x;
    u16 second_coord;
    s32 start_depth;
    s32 end_depth;
    u16 origin_x;
    u16 origin_y;
    u16 sprite_flags;
    register u16 segment_angle ASM_REG("$2");
    s32 texture_override;
    register s32 texture_word ASM_REG("$2");
    register u8 packet_code ASM_REG("$4");
    u8 right_u;
    u8 bottom_v;
    register u8 blend_code ASM_REG("$2");
    void *draw_packet;
    void *global_base;
    register u8 *global_page ASM_REG("$8") = (u8 *)0x80080000;
    register u8 *scratch_base ASM_REG("$4");
    register u8 *screen_out ASM_REG("$5");
    register u8 *depth_out ASM_REG("$6");
    u8 *second_vertex;
    u8 *clip_out;
    void *quad;
    void *part_data;
    register void *part ASM_REG("$20");
    void *render_state;
    void *state_alias;
    s32 *coeff_base;
    void *packet_next;
    register void *sprite_data ASM_REG("$21") = sprite;
    register s16 sort_bias ASM_REG("$17") = depth_bias;
    s16 bias_copy = depth_bias;
    s32 mode = orient_mode;
    register u32 state_dep;
    u8 *scratch;
    scratch_base = (u8 *)0x1F800000;
    screen_out = scratch_base;
    screen_out = (u8 *)((u32)screen_out | 0xB8);
    depth_out = scratch_base;
    ASM_KEEP_MEM_NV(screen_out, *(u8 **)D_80083160);
    scratch = scratch_base;
    ASM_KEEP_NV(mode);
    global_base = *(void **)D_80083160;
    ASM_KEEP_DEP_NV(depth_out, global_base);
    depth_out = (u8 *)((u32)depth_out | 0x90);
    ASM_KEEP_NV(sort_bias);

#define SP8(off) M2C_FIELD(scratch, u8 *, (off))
#define SPS8(off) M2C_FIELD(scratch, s8 *, (off))
#define SP16(off) M2C_FIELD(scratch, u16 *, (off))
#define SPS16(off) M2C_FIELD(scratch, s16 *, (off))
#define SP32(off) M2C_FIELD(scratch, s32 *, (off))
#define SPA(off) ((void *)(scratch + (off)))

    SP32(0xEC) = 0;
    SP16(0x8C) = 0;
    SP16(0x84) = 0;
    SP16(0x7C) = 0;
    SP16(0x74) = 0;
    SP32(0x20) = global_base + 0xB0;
    packet_next = ((S_800CEFB8_0 *)global_base)->unk_8D0;
    ((S_800CEFB8_1 *)sprite_data)->unk_14 = (u16) (((S_800CEFB8_1 *)sprite_data)->unk_14 | 0x8000);
    ASM_KEEP_MEMDEP(sprite_data, state_dep, *(u8 **)D_80083160);
    ASM_SET(global_page);
    ASM_KEEP(bias_copy);
    SP16(0x00) = (u16) ((S_800CEFB8_2 *)endpoints)->unk_02;
    SP16(0x02) = (u16) ((S_800CEFB8_2 *)endpoints)->unk_06;
    render_state = global_page + 0x3160;
    state_alias = render_state;
    SP16(0x04) = (u16) ((S_800CEFB8_2 *)endpoints)->unk_0A;
    start_depth = func_80065420(scratch_base,
                                 screen_out,
                                 depth_out,
                                 (void *)0x1F800094);
    ASM_KEEP_NV(scratch);
    second_vertex = scratch;
    ASM_KEEP_NV(second_vertex);
    screen_out = second_vertex;
    ASM_KEEP_NV(screen_out);
    screen_out = (u8 *)((u32)screen_out | 0xF0);
    depth_out = second_vertex;
    SP32(0xC0) = start_depth;
    second_coord = ((S_800CEFB8_2 *)endpoints)->unk_0E;
    ASM_KEEP_DEP_NV(depth_out, second_coord);
    depth_out = (u8 *)((u32)depth_out | 0x90);
    SP16(0x00) = second_coord;
    second_coord = ((S_800CEFB8_2 *)endpoints)->unk_12;
    ASM_KEEP_DEP_NV(second_vertex, second_coord);
    clip_out = second_vertex;
    ASM_KEEP_NV(clip_out);
    SP16(0x02) = second_coord;
    second_coord = ((S_800CEFB8_2 *)endpoints)->unk_16;
    clip_out = (u8 *)((u32)clip_out | 0x94);
    SP16(0x04) = second_coord;
    end_depth = func_80065420(second_vertex, screen_out, depth_out, clip_out);
    end_y = SP16(0xF2);
    start_y = SP16(0xBA);
    end_x = SP16(0xF0);
    start_x = SP16(0xB8);
    SP32(0xC0) = (s32)(SP32(0xC0) + end_depth) >> 1;
    SP16(0x10E) = func_80065F90((s16)end_y - (s16)start_y,
                                (s16)end_x - (s16)start_x,
                                (s16)end_x);
    {
        register u8 *coeff_page ASM_REG("$3") = (u8 *)0x80070000;
        ASM_KEEP_NV(coeff_page);
        coeff_base = (s32 *)(coeff_page - 0x32D0);
    }
    depth_offset = sort_bias;
    ASM_SCHED_BARRIER();
    mean_depth = SP32(0xC0);
    ((S_800CEFB8_3 *)coeff_base)->unk_1C = (s32) (mean_depth * 4);
    sort_depth = mean_depth - depth_offset;
    SP32(0xC0) = sort_depth;
    if ((u32) sort_depth < 0x1E0U) {
        draw_mode = mode;
        ASM_KEEP(draw_mode);
        func_800649A0();
        coord_work = ((S_800CEFB8_4 *)scratch)->unk_B8;
        coord_end = ((S_800CEFB8_4 *)scratch)->unk_BA;
        coord_work -= 0xA0;
        ((S_800CEFB8_4 *)scratch)->unk_B8 = coord_work;
        coord_work = ((S_800CEFB8_4 *)scratch)->unk_F0;
        coord_end -= 0x78;
        ((S_800CEFB8_4 *)scratch)->unk_BA = coord_end;
        coord_work -= 0xA0;
        ((S_800CEFB8_4 *)scratch)->unk_F0 = coord_work;
        coord_work = ((S_800CEFB8_4 *)scratch)->unk_F2;
        camera_rot_x = ((S_800CEFB8_5 *)render_state)->unk_C4;
        camera_rot_z = ((S_800CEFB8_5 *)render_state)->unk_C6;
        camera_rot_y = ((S_800CEFB8_5 *)render_state)->unk_C8;
        coord_work -= 0x78;
        ((S_800CEFB8_4 *)scratch)->unk_F2 = coord_work;
        SP32(0x30) = camera_rot_x;
        SP32(0x34) = camera_rot_z;
        SP32(0x38) = camera_rot_y;
        SP16(0x100) = (u16) ((S_800CEFB8_1 *)sprite_data)->unk_16;
        rotation_z = (((S_800CEFB8_1 *)sprite_data)->unk_1A - camera_rot_z) + ((S_800CEFB8_5 *)render_state)->unk_B8;
        if (((u32)mode << 0x10) == 0) {
            ASM_KEEP(mode);
            segment_angle = SP16(0x10E);
            rotation_z += (s16)segment_angle;
        }
        {
            register void *rotation_in ASM_REG("$4");
            register u8 *matrix_out ASM_REG("$5");
            s32 rotation_y;
            rotation_in = (void *)0x1F800100;
            SP16(0x104) = rotation_z;
            rotation_y = ((S_800CEFB8_1 *)sprite_data)->unk_18;
            SP16(0x102) = (s16) ((((u16) SP32(0x38) + 0x100) & 0x1FF) + (s16) (rotation_y - 0x100));
            matrix_out = (u8 *)0x1F800000;
            ASM_KEEP(matrix_out);
            origin_x = ((S_800CEFB8_1 *)sprite_data)->unk_20;
            matrix_out = (u8 *)((u32)matrix_out | 0xD0);
            SP32(0xE4) = (s32) origin_x;
            SP16(0x108) = origin_x;
            origin_y = ((S_800CEFB8_1 *)sprite_data)->unk_22;
            quad = packet_next + 4;
            SP32(0xE8) = (s32) origin_y;
            SP16(0x10A) = origin_y;
            func_80065820(rotation_in, matrix_out);
        }
        {
            s32 scale_x;
            s32 scale_y;
            s32 scale_z;
            scale_x = ((S_800CEFB8_1 *)sprite_data)->unk_1C;
            SP32(0x30) = scale_x;
            scale_y = ((S_800CEFB8_1 *)sprite_data)->unk_1E;
            scale_z = 0x1000;
            SP32(0x38) = scale_z;
            SP32(0x34) = scale_y;
            func_80064BC0((void *)0x1F8000D0, (void *)0x1F800030);
        }
        func_80064840(coeff_base, (void *)0x1F8000D0, (void *)0x1F800050);
        func_80064D80((void *)0x1F800050);
        func_80064CF0((void *)0x1F800050);
        part = ((S_800CEFB8_1 *)sprite_data)->unk_08;
        part_data = part + 1;
        SP16(0x24) = (u16) ((S_800CEFB8_1 *)sprite_data)->unk_14;
entry_loop:
        if (!(((S_800CEFB8_6 *)part)->unk_00 & 0x20)) {
            SP32(0x08) = (s32) ((S_800CEFB8_7 *)part_data)->unk_07;
            SP32(0x0C) = (s32) ((S_800CEFB8_7 *)part_data)->unk_08;
            SP32(0x10) = (s32) ((S_800CEFB8_7 *)part_data)->unk_09;
            SP32(0x14) = (s32) ((S_800CEFB8_7 *)part_data)->unk_0A;
            {
                s16 edge_coord;
                u16 axis_adjust;
                s32 axis_extent;
                if ((((S_800CEFB8_6 *)part)->unk_00 ^ SP16(0x24)) & 1) {
                    edge_coord = (s8) ((S_800CEFB8_7 *)part_data)->unk_01;
                    axis_adjust = ((S_800CEFB8_4 *)scratch)->unk_108;
                    axis_extent = (u16) SP32(0x10);
                    edge_coord = -edge_coord - axis_adjust;
                    SP16(0x80) = edge_coord;
                    SP16(0x70) = edge_coord;
                    ASM_SCHED_BARRIER();
                    edge_coord -= axis_extent;
                    goto axis_x_join;
                }
                edge_coord = (s8) ((S_800CEFB8_7 *)part_data)->unk_01;
                axis_adjust = ((S_800CEFB8_4 *)scratch)->unk_108;
                axis_extent = (u16) SP32(0x10);
                edge_coord -= axis_adjust;
                SP16(0x80) = edge_coord;
                SP16(0x70) = edge_coord;
                ASM_SCHED_BARRIER();
                edge_coord += axis_extent;
axis_x_join:
                SP16(0x88) = edge_coord;
                SP16(0x78) = edge_coord;
            }
            {
                s16 edge_coord;
                u16 axis_adjust;
                s32 axis_extent;
                if ((((S_800CEFB8_6 *)part)->unk_00 ^ SP16(0x24)) & 2) {
                    edge_coord = (s8) ((S_800CEFB8_7 *)part_data)->unk_02;
                    axis_adjust = ((S_800CEFB8_4 *)scratch)->unk_10A;
                    axis_extent = (u16) SP32(0x14);
                    edge_coord = -edge_coord - axis_adjust;
                    SP16(0x7A) = edge_coord;
                    SP16(0x72) = edge_coord;
                    ASM_SCHED_BARRIER();
                    edge_coord -= axis_extent;
                    goto axis_y_join;
                }
                edge_coord = (s8) ((S_800CEFB8_7 *)part_data)->unk_02;
                axis_adjust = ((S_800CEFB8_4 *)scratch)->unk_10A;
                axis_extent = (u16) SP32(0x14);
                edge_coord -= axis_adjust;
                SP16(0x7A) = edge_coord;
                SP16(0x72) = edge_coord;
                ASM_SCHED_BARRIER();
                edge_coord += axis_extent;
axis_y_join:
                SP16(0x8A) = edge_coord;
                SP16(0x82) = edge_coord;
                ASM_SCHED_BARRIER();
            }
            func_800654B0(SPA(0x70), SPA(0x78), SPA(0x80), SPA(0x88),
                         packet_next + 8, packet_next + 0x10, packet_next + 0x18,
                         packet_next + 0x20, SPA(0x90), SPA(0x94));
            if (((u32)draw_mode << 0x10) != 0) {
                if ((SP16(0xBA) << 0x10) < (SP16(0xF2) << 0x10)) {
                    ((S_800CEFB8_8 *)quad)->unk_04.u = (u16) (((S_800CEFB8_8 *)quad)->unk_04.u + SP16(0xB8));
                    ((S_800CEFB8_8 *)quad)->unk_0C = (u16) (((S_800CEFB8_8 *)quad)->unk_0C + SP16(0xB8));
                    ((S_800CEFB8_8 *)quad)->unk_06 = (u16) (((S_800CEFB8_8 *)quad)->unk_06 + SP16(0xBA));
                    ((S_800CEFB8_8 *)quad)->unk_0E = (u16) (((S_800CEFB8_8 *)quad)->unk_0E + SP16(0xBA));
                    ((S_800CEFB8_8 *)quad)->unk_14 = (u16) (((S_800CEFB8_8 *)quad)->unk_14 + SP16(0xF0));
                    ((S_800CEFB8_8 *)quad)->unk_1C.u = (u16) (((S_800CEFB8_8 *)quad)->unk_1C.u + SP16(0xF0));
                    ((S_800CEFB8_8 *)quad)->unk_16 = (u16) (((S_800CEFB8_8 *)quad)->unk_16 + SP16(0xF2));
                    goto coord_last;
                }
                ((S_800CEFB8_8 *)quad)->unk_14 = (u16) (((S_800CEFB8_8 *)quad)->unk_14 + SP16(0xB8));
                ((S_800CEFB8_8 *)quad)->unk_1C.u = (u16) (((S_800CEFB8_8 *)quad)->unk_1C.u + SP16(0xB8));
                ((S_800CEFB8_8 *)quad)->unk_16 = (u16) (((S_800CEFB8_8 *)quad)->unk_16 + SP16(0xBA));
                ((S_800CEFB8_8 *)quad)->unk_1E = (u16) (((S_800CEFB8_8 *)quad)->unk_1E + SP16(0xBA));
                ((S_800CEFB8_8 *)quad)->unk_04.u = (u16) (((S_800CEFB8_8 *)quad)->unk_04.u + SP16(0xF0));
                ((S_800CEFB8_8 *)quad)->unk_0C = (u16) (((S_800CEFB8_8 *)quad)->unk_0C + SP16(0xF0));
                ((S_800CEFB8_8 *)quad)->unk_06 = (u16) (((S_800CEFB8_8 *)quad)->unk_06 + SP16(0xF2));
                ((S_800CEFB8_8 *)quad)->unk_0E = (u16) (((S_800CEFB8_8 *)quad)->unk_0E + SP16(0xF2));
                goto coord_done;
            }
            ((S_800CEFB8_8 *)quad)->unk_14 = (u16) (((S_800CEFB8_8 *)quad)->unk_14 + SP16(0xB8));
            ((S_800CEFB8_8 *)quad)->unk_16 = (u16) (((S_800CEFB8_8 *)quad)->unk_16 + SP16(0xBA));
            ((S_800CEFB8_8 *)quad)->unk_0C = (u16) (((S_800CEFB8_8 *)quad)->unk_0C + SP16(0xF0));
            ((S_800CEFB8_8 *)quad)->unk_0E = (u16) (((S_800CEFB8_8 *)quad)->unk_0E + SP16(0xF2));
            ((S_800CEFB8_8 *)quad)->unk_04.u = (u16) (((S_800CEFB8_8 *)quad)->unk_04.u + SP16(0xB8));
            ((S_800CEFB8_8 *)quad)->unk_06 = (u16) (((S_800CEFB8_8 *)quad)->unk_06 + SP16(0xBA));
            ((S_800CEFB8_8 *)quad)->unk_1C.u = (u16) (((S_800CEFB8_8 *)quad)->unk_1C.u + SP16(0xF0));
coord_last:
            ((S_800CEFB8_8 *)quad)->unk_1E = (u16) (((S_800CEFB8_8 *)quad)->unk_1E + SP16(0xF2));
coord_done:
            visible_a = 0;
            if ((u32) ((((S_800CEFB8_8 *)quad)->unk_04.u + 0x20) & 0xFFFF) < 0x181U) {
                coord_work = (((S_800CEFB8_8 *)quad)->unk_06 + 0x20) & 0xFFFF;
                visible_a = (u32) coord_work < 0x121U;
            }
            visible_b = 0;
            if ((u32) ((((S_800CEFB8_8 *)quad)->unk_0C + 0x20) & 0xFFFF) < 0x181U) {
                coord_work = (((S_800CEFB8_8 *)quad)->unk_0E + 0x20) & 0xFFFF;
                visible_b = (u32) coord_work < 0x121U;
            }
            visible_c = 0;
            visible_ab = visible_a | visible_b;
            if ((u32) ((((S_800CEFB8_8 *)quad)->unk_14 + 0x20) & 0xFFFF) < 0x181U) {
                coord_work = (((S_800CEFB8_8 *)quad)->unk_16 + 0x20) & 0xFFFF;
                visible_c = (u32) coord_work < 0x121U;
            }
            visible_d = 0;
            visible_abc = visible_ab | visible_c;
            if ((u32) ((((S_800CEFB8_8 *)quad)->unk_1C.u + 0x20) & 0xFFFF) < 0x181U) {
                coord_work = (((S_800CEFB8_8 *)quad)->unk_1E + 0x20) & 0xFFFF;
                visible_d = (u32) coord_work < 0x121U;
            }
            coord_work = visible_abc | visible_d;
            if (coord_work != 0) {
                ((S_800CEFB8_8_pre *)quad)[-1].unk_00 = 9;
                ((S_800CEFB8_1 *)sprite_data)->unk_14 = (u16) (((S_800CEFB8_1 *)sprite_data)->unk_14 & 0x7FFF);
                coord_work = SP32(0x10);
                coord_end = SP32(0x08);
                coord_work -= 1;
                coord_end = coord_work + coord_end;
                SP32(0x10) = coord_end;
                if (coord_end & 0x100) {
                    coord_work = coord_end - 1;
                    SP32(0x10) = coord_work;
                }
                coord_work = SP32(0x14);
                coord_end = SP32(0x0C);
                coord_work -= 1;
                coord_end = coord_work + coord_end;
                SP32(0x14) = coord_end;
                if (coord_end & 0x100) {
                    coord_work = coord_end - 1;
                    SP32(0x14) = coord_work;
                }
                SP32(0x14) <<= 8;
                SP32(0x0C) <<= 8;
                texture_override = ((S_800CEFB8_1 *)sprite_data)->unk_12;
                if (texture_override != 0) {
                    if (SP16(0x24) & 0x100) {
                        ((S_800CEFB8_8 *)quad)->unk_0A = texture_override;
                        goto continuation_coords;
                    }
                    texture_word = (*(u16 *)((u8 *)part_data + 5));
                    texture_word = texture_override + texture_word;
                    goto continuation_color;
                }
                texture_word = (u16) (*(u16 *)((u8 *)part_data + 5));
continuation_color:
                ((S_800CEFB8_8 *)quad)->unk_0A = texture_word;
continuation_coords:
                ((S_800CEFB8_8 *)quad)->unk_08 = (s16) ((u16) SP32(0x0C) + (u16) SP32(0x08));
                ((S_800CEFB8_8 *)quad)->unk_10.s16 = (s16) ((u16) SP32(0x0C) + (u16) SP32(0x10));
                texture_override = ((S_800CEFB8_1 *)sprite_data)->unk_10;
                if (texture_override != 0) {
                    texture_word = (*(u16 *)((u8 *)part_data + 3));
                    texture_word &= 0xFF9F;
                    texture_word = texture_override + texture_word;
                    goto continuation_texture;
                }
                texture_word = (u16) (*(u16 *)((u8 *)part_data + 3));
continuation_texture:
                ((S_800CEFB8_8 *)quad)->unk_12 = texture_word;
                {
                    s32 left_x;
                    register u16 packed_uv ASM_REG("$3");
                    register u16 right_uv ASM_REG("$4");
                    ((S_800CEFB8_8 *)quad)->unk_18.at00.v = (s16) (SP16(0x14) | SP16(0x08));
                    left_x = ((S_800CEFB8_8 *)quad)->unk_04.s;
                    packed_uv = SP16(0x14);
                    right_uv = SP16(0x10);
                    packed_uv |= right_uv;
                    ((S_800CEFB8_8 *)quad)->unk_20.at00.v = (s16) packed_uv;
                    if (((S_800CEFB8_8 *)quad)->unk_1C.s < left_x) {
                        right_u = ((S_800CEFB8_8 *)quad)->unk_20.at00u.v;
                        ((S_800CEFB8_8 *)quad)->unk_20.at00u.v = (u8) (right_u + 0xFF);
                        ((S_800CEFB8_8 *)quad)->unk_10.u8 = right_u;
                    }
                }
                if ((s16) ((S_800CEFB8_8 *)quad)->unk_06 > (s16) ((S_800CEFB8_8 *)quad)->unk_1E) {
                    bottom_v = ((S_800CEFB8_8 *)quad)->unk_20.at01.v;
                    ((S_800CEFB8_8 *)quad)->unk_20.at01.v = (u8) (bottom_v + 0xFF);
                    ((S_800CEFB8_8 *)quad)->unk_18.at01.v = bottom_v;
                }
                packet_code = ((S_800CEFB8_7 *)part_data)->unk_00;
                ((S_800CEFB8_1 *)sprite_data)->unk_0C.at03.v = packet_code;
                sprite_flags = SP16(0x24);
                if (sprite_flags & 8) {
                    if (sprite_flags & 4) {
                        blend_code = packet_code | 2;
                    } else {
                        blend_code = packet_code & 0xFD;
                    }
                    ((S_800CEFB8_1 *)sprite_data)->unk_0C.at03.v = blend_code;
                }
                draw_packet = packet_next;
                packet_next += 0x28;
                ((S_800CEFB8_8 *)quad)->unk_00 = (s32) ((S_800CEFB8_1 *)sprite_data)->unk_0C.at00.v;
                quad += 0x28;
                func_8006658C(SP32(0x20) + (SP32(0xC0) * 4), draw_packet);
                goto next_part;
            }
            goto next_part;
        }
next_part:
        if ((s8) ((S_800CEFB8_6 *)part)->unk_00 >= 0) {
            part_data += 0xC;
            part += 0xC;
            goto entry_loop;
        }
        func_80064A40();
        ((S_800CEFB8_9 *)(((S_800CEFB8_5 *)render_state)->unk_00))->unk_8D0 = packet_next;
        return;
    }
    ((S_800CEFB8_9 *)(((S_800CEFB8_5 *)render_state)->unk_00))->unk_8D0 = packet_next;
}
