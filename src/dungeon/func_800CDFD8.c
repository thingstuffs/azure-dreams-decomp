/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() 0
#define M2C_SYNC() 0

M2C_UNK func_80064840();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
u32 func_80065420();
M2C_UNK func_800654B0();
M2C_UNK func_80065820();
M2C_UNK func_800D3924();
M2C_UNK func_800D3AB8();
M2C_UNK func_800D3B28();
M2C_UNK func_800D3D40();
M2C_UNK func_800D3D90();
extern M2C_UNK D_8006CD30[];
extern u8 D_80083160[];

typedef struct S_func_800CDFD8_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    union {
        u32 unk_14_u32;
        u16 unk_14_u16;
    } unk_14;
    u8 pad_18[0x8];
    u32 unk_20;
    union {
        u32 unk_24_u32;
        u16 unk_24_u16;
    } unk_24;
    u8 pad_28[0x8];
    u32 unk_30;
    union {
        u32 unk_34_u32;
        u16 unk_34_u16;
    } unk_34;
    u32 unk_38;
    u8 pad_3C[0x14];
    u16 unk_50;
    u8 pad_52[0x6];
    u16 unk_58;
    u8 pad_5A[0x16];
    u16 unk_70;
    u16 unk_72;
    u16 unk_74;
    u8 pad_76[0x2];
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u8 pad_7E[0x2];
    u16 unk_80;
    u16 unk_82;
    u16 unk_84;
    u8 pad_86[0x2];
    u16 unk_88;
    u16 unk_8A;
    u16 unk_8C;
    u8 pad_8E[0x2A];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    u32 unk_C0;
    u8 pad_C4[0x20];
    u32 unk_E4;
    u32 unk_E8;
    u32 unk_EC;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
    u16 unk_F8;
    u16 unk_FA;
    u16 unk_FC;
    u16 unk_FE;
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
    u8 pad_106[0x2];
    u16 unk_108;
    u16 unk_10A;
} S_func_800CDFD8_1;

typedef struct S_func_800CDFD8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_func_800CDFD8_2;

typedef struct S_func_800CDFD8_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_func_800CDFD8_3;

typedef struct S_func_800CDFD8_4 {
    void * unk_00;
    u8 pad_04[0xB4];
    u16 unk_B8;
    u8 pad_BA[0xA];
    s16 unk_C4;
    s16 unk_C6;
    s16 unk_C8;
} S_func_800CDFD8_4;

typedef struct S_func_800CDFD8_5 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
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
} S_func_800CDFD8_5;

typedef struct S_func_800CDFD8_6 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
    u8 pad_0C[0x14];
    s32 unk_20;
} S_func_800CDFD8_6;

typedef struct S_func_800CDFD8_7 {
    u8 unk_00;
} S_func_800CDFD8_7;

typedef struct S_func_800CDFD8_8 {
    u8 pad_00[0x3];
    s8 unk_03;
    union {
        s32 unk_04_s32;
        struct {
            u8 pad_04[0x3];
            s8 unk_07;
        } unk_07_s8;
    } unk_04;
    u16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s32 unk_10;
    u16 unk_14;
    u16 unk_16;
    union {
        s16 unk_18_s16;
        u8 unk_18_u8;
    } unk_18;
    u16 unk_1A;
    s32 unk_1C;
    u16 unk_20;
    u16 unk_22;
    union {
        s16 unk_24_s16;
        struct {
            u8 pad_24[0x1];
            u8 unk_25;
        } unk_25_u8;
    } unk_24;
    u8 pad_26[0x2];
    s32 unk_28;
    u16 unk_2C;
    s16 unk_2E;
    union {
        s16 unk_30_s16;
        u8 unk_30_u8;
        struct {
            u8 pad_30[0x1];
            u8 unk_31;
        } unk_31_u8;
    } unk_30;
} S_func_800CDFD8_8;

typedef struct S_func_800CDFD8_9 {
    u32 unk_00;
} S_func_800CDFD8_9;

/* Project sprite parts into textured quads and link visible quads into the ordering table. */
void func_800D3738(void *unused, void *position_in, void *sprite_in, s16 depth_bias_in) {
    s32 screen_y3;
    s32 left_x;
    register s32 half_left_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 first_three_visible;
    s32 edge_y;
    s16 bottom_left_x;
    s32 matrix_xx;
    s32 matrix_yy;
    s32 flipped_x;
    s32 flipped_top_x;
    s32 *ot_entry;
    s32 *ot_link;
    u32 address_mask;
    u32 tag_mask;
    u32 packet_tag;
    u32 ot_tag;
    s32 color2;
    s32 color3;
    s32 half_width;
    s32 first_two_visible;
    s32 camera_rot_x;
    s32 camera_rot_y;
    s32 camera_rot_z;
    s32 rotation_delta;
    s32 rotation_z;
    s32 rotation_y;
    u32 scale_x;
    u32 scale_y;
    s32 vertex2_visible;
    s32 vertex0_visible;
    s32 vertex1_visible;
    s32 vertex3_visible;
    s32 camera_y;
    register u16 height ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 coord;
    u16 pivot_x;
    u16 pivot_y;
    register u32 width ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 texture_u;
    u32 flipped_width;
    u32 texture_v;
    register u32 texture_right ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 packed_v ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 screen_bound;
    register u32 sprite_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 any_visible;
    u32 depth;
    u32 ot_depth;
    u8 part_u;
    u8 part_v;
    u8 part_width;
    u8 part_height;
    u8 scaled_right_u;
    u8 scaled_bottom_v;
    u8 flipped_right_u;
    u8 flipped_bottom_v;
    S_func_800CDFD8_8 *quad;
    S_func_800CDFD8_1 *scratch;
    register u8 *globals_page ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register S_func_800CDFD8_2 *position ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *page_dependency;
    S_func_800CDFD8_6 *matrix_or_part;
    S_func_800CDFD8_7 *part;
    S_func_800CDFD8_4 *render_state;
    S_func_800CDFD8_9 *packet;
    S_func_800CDFD8_5 *sprite;
    register s16 depth_bias ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    position = position_in;
    sprite = sprite_in;
    ASM_KEEP_NV(sprite);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    depth_bias = depth_bias_in;
    ASM_KEEP_NV(depth_bias);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    {
        u8 *world_pos;
        void *screen_pos;
        void *depth_out;
        register void *projection_flags ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        register S_func_800CDFD8_3 *render_root ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        world_pos = (u8 *)0x1F800000;
        screen_pos = world_pos;
        ASM_KEEP_NV(screen_pos);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        screen_pos = (void *) ((u32) screen_pos | 0xB8);
        depth_out = world_pos;
        ASM_KEEP_NV(depth_out);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP_MEMDEP_NV(world_pos, page_dependency, *(void **)D_80083160);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        scratch = (S_func_800CDFD8_1 *)world_pos;
        ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        render_root = *(void **)D_80083160;
        depth_out = (void *) ((u32) depth_out | 0x90);
        scratch->unk_EC = 0;
        scratch->unk_8C = 0;
        scratch->unk_84 = 0;
        scratch->unk_7C = 0;
        scratch->unk_74 = 0;
        scratch->unk_20 = (u8 *)render_root + 0xB0;
        coord = position->unk_02;
        projection_flags = world_pos;
        scratch->unk_00 = coord;
        ASM_KEEP_MEMDEP_NV(scratch, page_dependency, *(void **)D_80083160);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        globals_page = D_80083160 - 0x3160;
#else
        ASM_SET(globals_page);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
#endif
        coord = position->unk_06;
        projection_flags = (void *) ((u32) projection_flags | 0x94);
        scratch->unk_02 = coord;
        coord = position->unk_0A;
        scratch->unk_04 = coord;
        packet = render_root->unk_8D0;
        scratch->unk_C0 = func_80065420((render_state = (S_func_800CDFD8_4 *)(globals_page + 0x3160), world_pos), screen_pos, depth_out, projection_flags);
    }
    sprite->unk_14 = (u16) (sprite->unk_14 | 0x8000);
    depth = scratch->unk_C0;
    matrix_or_part = (S_func_800CDFD8_6 *)&D_8006CD30;
    ASM_KEEP_NV(matrix_or_part);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ((S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_20 = (s32) (depth * 4);
    depth -= 0xA;
    ot_depth = depth - depth_bias;
    scratch->unk_C0 = ot_depth;
    if (ot_depth < 0x1D6U) {
        quad = (S_func_800CDFD8_8 *)((u8 *)packet + 7);
        func_800649A0();
        {
            void *angles;
            void *local_matrix;
            register u16 screen_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            angles = scratch;
            ASM_KEEP_NV(angles);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            screen_offset = scratch->unk_B8;
            angles = (void *) ((u32) angles | 0x100);
            ASM_KEEP_NV(angles);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            screen_offset -= 0xA0;
            scratch->unk_B8 = screen_offset;
            screen_offset = scratch->unk_BA;
            camera_rot_x = render_state->unk_C4;
            camera_rot_y = render_state->unk_C6;
            camera_rot_z = render_state->unk_C8;
            screen_offset -= 0x78;
            scratch->unk_BA = screen_offset;
            scratch->unk_30 = (u32) camera_rot_x;
            scratch->unk_34.unk_34_u32 = (u32) camera_rot_y;
            scratch->unk_38 = (u32) camera_rot_z;
            camera_y = scratch->unk_34.unk_34_u16;
            scratch->unk_100 = (u16) sprite->unk_16;
            rotation_delta = sprite->unk_1A;
            rotation_z = render_state->unk_B8;
            rotation_delta -= camera_y;
            rotation_z += rotation_delta;
            scratch->unk_104 = (s16) rotation_z;
            rotation_y = sprite->unk_18 - 0x100;
            rotation_y += ((u16) scratch->unk_38 + 0x100) & 0x1FF;
            scratch->unk_102 = (s16) rotation_y;
            pivot_x = sprite->unk_20;
            ASM_SET(local_matrix);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            local_matrix = scratch;
            ASM_KEEP_NV(local_matrix);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            scratch->unk_E4 = (u32) pivot_x;
            do {
                scratch->unk_108 = pivot_x;
            } while (0);
            pivot_y = sprite->unk_22;
            local_matrix = (void *) ((u32) local_matrix | 0xD0);
            scratch->unk_E8 = (u32) pivot_y;
            scratch->unk_10A = pivot_y;
            func_80065820(angles, local_matrix, camera_y);
        }
        {
            void *local_matrix;
            void *scale;
            local_matrix = scratch;
            ASM_KEEP_NV(local_matrix);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            local_matrix = (void *) ((u32) local_matrix | 0xD0);
            ASM_SET(scale);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            scale = scratch;
            ASM_KEEP_NV(scale);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            scale_x = sprite->unk_1C;
            scale = (void *) ((u32) scale | 0x30);
            scratch->unk_30 = scale_x;
            scale_y = sprite->unk_1E;
            scratch->unk_38 = 0x1000;
            scratch->unk_34.unk_34_u32 = scale_y;
            func_80064BC0(local_matrix, scale);
        }
        {
            void *view_matrix;
            void *local_matrix;
            void *combined_matrix;
            view_matrix = matrix_or_part;
            ASM_KEEP_NV(view_matrix);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            do {
                local_matrix = scratch;
            } while (0);
            ASM_KEEP_NV(local_matrix);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            local_matrix = (void *) ((u32) local_matrix | 0xD0);
            ASM_SET(combined_matrix);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            combined_matrix = scratch;
            ASM_KEEP_NV(combined_matrix);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            combined_matrix = (void *) ((u32) combined_matrix | 0x50);
            func_80064840(view_matrix, local_matrix, combined_matrix);
        }
        {
            void *matrix;
            matrix = scratch;
            ASM_KEEP_NV(matrix);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            matrix = (void *) ((u32) matrix | 0x50);
            func_80064D80(matrix);
        }
        {
            void *matrix;
            matrix = scratch;
            ASM_KEEP_NV(matrix);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            matrix = (void *) ((u32) matrix | 0x50);
            func_80064CF0(matrix);
        }
        part = sprite->unk_08;
        matrix_or_part = (S_func_800CDFD8_6 *)((u8 *)part + 4);
        scratch->unk_24.unk_24_u16 = (u16) sprite->unk_14;
next_part:
        if (!(part->unk_00 & 0x20)) {
            part_u = ((S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_08;
            scratch->unk_08 = (u32) part_u;
            part_width = ((S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_0A;
            scratch->unk_10 = (u32) part_width;
            if (((part_u + part_width) >= 0x100) || (sprite->unk_1A != 0)) {
                scratch->unk_10 = part_width - 1;
            }
            part_v = ((S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_09;
            scratch->unk_0C = (u32) part_v;
            part_height = ((S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_0B;
            scratch->unk_14.unk_14_u32 = (u32) part_height;
            if (((part_v + part_height) >= 0x100) || (sprite->unk_1A != 0)) {
                scratch->unk_14.unk_14_u32 = part_height - 1;
            }
            if ((part->unk_00 ^ scratch->unk_24.unk_24_u16) & 1) {
                flipped_width = scratch->unk_10;
                flipped_x = (0 - (s8) ((volatile S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_02) - scratch->unk_108;
                flipped_top_x = flipped_x + ((s32) ((s16) flipped_x + ((u32) (flipped_x << 0x10) >> 0x1F)) >> 1);
                half_width = (s32) (flipped_width + (flipped_width >> 0x1F)) >> 1;
                scratch->unk_70 = flipped_top_x;
                scratch->unk_78 = (s16) (flipped_top_x - ((u16) scratch->unk_10 + half_width));
                scratch->unk_80 = (s16) ((0 - (s8) ((S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_02) - scratch->unk_108);
                scratch->unk_88 = (s16) (scratch->unk_80 - (u16) scratch->unk_10);
                goto x_ready;
            }
            left_x = (s8) ((volatile S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_02 - ((volatile S_func_800CDFD8_1 *)scratch)->unk_108;
            width = ((volatile S_func_800CDFD8_1 *)scratch)->unk_10;
            half_left_x = (s16) left_x;
            half_left_x = (s32) (half_left_x + ((u32) (left_x << 0x10) >> 0x1F)) >> 1;
            left_x += half_left_x;
            scratch->unk_70 = left_x;
            left_x += (u16) scratch->unk_10 + ((s32) (width + (width >> 0x1F)) >> 1);
            scratch->unk_78 = left_x;
            bottom_left_x = (s8) ((S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_02 - scratch->unk_108;
            scratch->unk_80 = bottom_left_x;
            scratch->unk_88 = (s16) (bottom_left_x + (u16) scratch->unk_10);
x_ready:
            if ((part->unk_00 ^ scratch->unk_24.unk_24_u16) & 2) {
                edge_y = (0 - (s8) ((volatile S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_03) - ((volatile S_func_800CDFD8_1 *)scratch)->unk_10A;
                height = ((volatile S_func_800CDFD8_1 *)scratch)->unk_14.unk_14_u16;
                ((volatile S_func_800CDFD8_1 *)scratch)->unk_7A = edge_y;
                ((volatile S_func_800CDFD8_1 *)scratch)->unk_72 = edge_y;
                edge_y -= height;
                goto y_ready;
            }
            edge_y = (s8) ((volatile S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_03 - ((volatile S_func_800CDFD8_1 *)scratch)->unk_10A;
            height = ((volatile S_func_800CDFD8_1 *)scratch)->unk_14.unk_14_u16;
            ((volatile S_func_800CDFD8_1 *)scratch)->unk_7A = edge_y;
            ((volatile S_func_800CDFD8_1 *)scratch)->unk_72 = edge_y;
            edge_y = height + edge_y;
y_ready:
            scratch->unk_8A = edge_y;
            scratch->unk_82 = edge_y;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            func_800654B0((u8 *)scratch + 0x70, (u8 *)scratch + 0x78, (u8 *)scratch + 0x80, (u8 *)scratch + 0x88, (u8 *)scratch + 0xF0, (u8 *)scratch + 0xF4, (u8 *)scratch + 0xF8, (u8 *)scratch + 0xFC, (u8 *)scratch + 0x90, (u8 *)scratch + 0x94);
            ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_08 = (u16) (scratch->unk_F0 + scratch->unk_B8);
            ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_0A = (u16) (scratch->unk_F2 + scratch->unk_BA);
            ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_14 = (u16) (scratch->unk_F4 + scratch->unk_B8);
            ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_16 = (u16) (scratch->unk_F6 + scratch->unk_BA);
            ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_20 = (u16) (scratch->unk_F8 + scratch->unk_B8);
            ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_22 = (u16) (scratch->unk_FA + scratch->unk_BA);
            vertex0_visible = 0;
            ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_2C = (u16) (scratch->unk_FC + scratch->unk_B8);
            screen_y3 = scratch->unk_FE + scratch->unk_BA;
            ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_2E = screen_y3;
            if ((u32) ((((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_08 + 0x20) & 0xFFFF) < 0x181U) {
                screen_bound = (((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_0A + 0x20) & 0xFFFF;
                vertex0_visible = screen_bound < 0x121U;
            }
            vertex1_visible = 0;
            if ((u32) ((((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_14 + 0x20) & 0xFFFF) < 0x181U) {
                screen_bound = (((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_16 + 0x20) & 0xFFFF;
                vertex1_visible = screen_bound < 0x121U;
            }
            vertex2_visible = 0;
            first_two_visible = vertex0_visible | vertex1_visible;
            if ((u32) ((((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_20 + 0x20) & 0xFFFF) < 0x181U) {
                screen_bound = (((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_22 + 0x20) & 0xFFFF;
                vertex2_visible = screen_bound < 0x121U;
            }
            vertex3_visible = 0;
            first_three_visible = first_two_visible | vertex2_visible;
            if ((u32) ((((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_2C + 0x20) & 0xFFFF) < 0x181U) {
                screen_bound = (screen_y3 + 0x20) & 0xFFFF;
                vertex3_visible = screen_bound < 0x121U;
            }
            any_visible = first_three_visible | vertex3_visible;
            if (any_visible != 0) {
                sprite->unk_14 = (u16) (sprite->unk_14 & 0x7FFF);
                texture_right = ((volatile S_func_800CDFD8_1 *)scratch)->unk_10;
                texture_u = ((volatile S_func_800CDFD8_1 *)scratch)->unk_08;
                packed_v = ((volatile S_func_800CDFD8_1 *)scratch)->unk_14.unk_14_u32;
                texture_v = ((volatile S_func_800CDFD8_1 *)scratch)->unk_0C;
                texture_right += texture_u;
                packed_v += texture_v;
                packed_v <<= 8;
                scratch->unk_14.unk_14_u32 = packed_v;
                packed_v = texture_v;
                ASM_KEEP_NV(packed_v);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                scratch->unk_10 = texture_right;
                sprite_flags = scratch->unk_24.unk_24_u16;
                packed_v <<= 8;
                scratch->unk_0C = packed_v;
                if (sprite_flags & 0x100) {
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_0E = (s16) sprite->unk_12;
                } else {
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_0E = (s16) (sprite->unk_12 + ((S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_06);
                }
                ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_0C = (s16) ((u16) scratch->unk_0C + (u16) scratch->unk_08);
                ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_18.unk_18_s16 = (s16) ((u16) scratch->unk_0C + (u16) scratch->unk_10);
                if (sprite->unk_10 != 0) {
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_1A = (u16) (sprite->unk_10 + (((S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_04 & 0xFF9F));
                } else {
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_1A = (u16) ((S_func_800CDFD8_6 *)((u8 *)matrix_or_part - 4))->unk_04;
                }
                ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_24.unk_24_s16 = (s16) ((u16) scratch->unk_14.unk_14_u32 | (u16) scratch->unk_08);
                ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_30.unk_30_s16 = (s16) ((u16) scratch->unk_14.unk_14_u32 | (u16) scratch->unk_10);
                matrix_xx = (s16) ((volatile S_func_800CDFD8_1 *)scratch)->unk_50;
                if (matrix_xx >= 0x1800) {
                    scaled_right_u = (u8) ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_30.unk_30_s16;
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_30.unk_30_u8 = (u8) (scaled_right_u + 0xFF);
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_18.unk_18_u8 = scaled_right_u;
                }
                matrix_yy = (s16) ((volatile S_func_800CDFD8_1 *)scratch)->unk_58;
                if (matrix_yy >= 0x1800) {
                    scaled_bottom_v = ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_30.unk_31_u8.unk_31;
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_30.unk_31_u8.unk_31 = (u8) (scaled_bottom_v + 0xFF);
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_24.unk_25_u8.unk_25 = scaled_bottom_v;
                }
                if ((s16) ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_08 > (s16) ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_2C) {
                    flipped_right_u = (u8) ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_30.unk_30_s16;
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_30.unk_30_u8 = (u8) (flipped_right_u + 0xFF);
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_18.unk_18_u8 = flipped_right_u;
                }
                if ((s16) ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_0A > ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_2E) {
                    flipped_bottom_v = ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_30.unk_31_u8.unk_31;
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_30.unk_31_u8.unk_31 = (u8) (flipped_bottom_v + 0xFF);
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_24.unk_25_u8.unk_25 = flipped_bottom_v;
                }
                ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_04.unk_04_s32 = 0;
                ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_10 = 0;
                color2 = ((volatile S_func_800CDFD8_5 *)sprite)->unk_0C;
                ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_1C = color2;
                color3 = ((volatile S_func_800CDFD8_5 *)sprite)->unk_0C;
                ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_03 = 0xC;
                ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_04.unk_07_s8.unk_07 = 0x3C;
                ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_28 = color3;
                if ((scratch->unk_24.unk_24_u32 & 0xC) == 0xC) {
                    ((S_func_800CDFD8_8 *)((u8 *)quad - 7))->unk_04.unk_07_s8.unk_07 = 0x3E;
                }
                address_mask = 0xFFFFFF;
                quad = (S_func_800CDFD8_8 *)((u8 *)quad + 0x34);
                tag_mask = 0xFF000000;
                ot_entry = (scratch->unk_C0 * 4) + scratch->unk_20;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                packet_tag = packet->unk_00;
                ot_tag = *ot_entry;
                packet_tag = (packet_tag & tag_mask) | (ot_tag & address_mask);
                address_mask = (u32) packet & address_mask;
                packet->unk_00 = packet_tag;
                ot_link = (scratch->unk_C0 * 4) + scratch->unk_20;
                packet = (S_func_800CDFD8_9 *)((u8 *)packet + 0x34);
                *ot_link = (*ot_link & tag_mask) | address_mask;
                goto advance_part;
            }
            goto advance_part;
        }
advance_part:
        if ((s8) part->unk_00 >= 0) {
            matrix_or_part = (S_func_800CDFD8_6 *)((u8 *)matrix_or_part + 0xC);
            part = (S_func_800CDFD8_7 *)((u8 *)part + 0xC);
            goto next_part;
        }
        func_80064A40();
        ((S_func_800CDFD8_3 *)render_state->unk_00)->unk_8D0 = packet;
        return;
    }
    ((S_func_800CDFD8_3 *)render_state->unk_00)->unk_8D0 = packet;
}
