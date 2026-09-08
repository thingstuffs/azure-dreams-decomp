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
    void *quad;
    u8 *scratch;
    register u8 *globals_page ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *position ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *page_dependency;
    void *matrix_or_part;
    void *part;
    register void *render_state ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *packet;
    void *sprite;
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
        register void *render_root ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        world_pos = (u8 *)0x1F800000;
        screen_pos = world_pos;
        ASM_KEEP_NV(screen_pos);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        screen_pos = (void *) ((u32) screen_pos | 0xB8);
        depth_out = world_pos;
        ASM_KEEP_NV(depth_out);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP_MEMDEP_NV(world_pos, page_dependency, *(void **)D_80083160);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        scratch = world_pos;
        ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        render_root = *(void **)D_80083160;
        depth_out = (void *) ((u32) depth_out | 0x90);
        M2C_FIELD(scratch, u32 *, 0xEC) = 0;
        M2C_FIELD(scratch, u16 *, 0x8C) = 0;
        M2C_FIELD(scratch, u16 *, 0x84) = 0;
        M2C_FIELD(scratch, u16 *, 0x7C) = 0;
        M2C_FIELD(scratch, u16 *, 0x74) = 0;
        M2C_FIELD(scratch, u32 *, 0x20) = render_root + 0xB0;
        coord = M2C_FIELD(position, u16 *, 2);
        projection_flags = world_pos;
        M2C_FIELD(scratch, u16 *, 0) = coord;
        ASM_KEEP_MEMDEP_NV(scratch, page_dependency, *(void **)D_80083160);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        globals_page = D_80083160 - 0x3160;
#else
        ASM_SET(globals_page);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
#endif
        coord = M2C_FIELD(position, u16 *, 6);
        projection_flags = (void *) ((u32) projection_flags | 0x94);
        M2C_FIELD(scratch, u16 *, 2) = coord;
        coord = M2C_FIELD(position, u16 *, 0xA);
        M2C_FIELD(scratch, u16 *, 4) = coord;
        packet = M2C_FIELD(render_root, void **, 0x8D0);
        M2C_FIELD(scratch, u32 *, 0xC0) = func_80065420((render_state = globals_page + 0x3160, world_pos), screen_pos, depth_out, projection_flags);
    }
    ASM_KEEP_NV(render_state);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    M2C_FIELD(sprite, u16 *, 0x14) = (u16) (M2C_FIELD(sprite, u16 *, 0x14) | 0x8000);
    depth = M2C_FIELD(scratch, u32 *, 0xC0);
    matrix_or_part = &D_8006CD30;
    ASM_KEEP_NV(matrix_or_part);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    M2C_FIELD(matrix_or_part, s32 *, 0x1C) = (s32) (depth * 4);
    depth -= 0xA;
    ot_depth = depth - depth_bias;
    M2C_FIELD(scratch, u32 *, 0xC0) = ot_depth;
    if (ot_depth < 0x1D6U) {
        quad = packet + 7;
        func_800649A0();
        {
            void *angles;
            void *local_matrix;
            register u16 screen_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            angles = scratch;
            ASM_KEEP_NV(angles);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            screen_offset = M2C_FIELD(scratch, u16 *, 0xB8);
            angles = (void *) ((u32) angles | 0x100);
            ASM_KEEP_NV(angles);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            screen_offset -= 0xA0;
            M2C_FIELD(scratch, u16 *, 0xB8) = screen_offset;
            screen_offset = M2C_FIELD(scratch, u16 *, 0xBA);
            camera_rot_x = M2C_FIELD(render_state, s16 *, 0xC4);
            camera_rot_y = M2C_FIELD(render_state, s16 *, 0xC6);
            camera_rot_z = M2C_FIELD(render_state, s16 *, 0xC8);
            screen_offset -= 0x78;
            M2C_FIELD(scratch, u16 *, 0xBA) = screen_offset;
            M2C_FIELD(scratch, u32 *, 0x30) = (u32) camera_rot_x;
            M2C_FIELD(scratch, u32 *, 0x34) = (u32) camera_rot_y;
            M2C_FIELD(scratch, u32 *, 0x38) = (u32) camera_rot_z;
            camera_y = M2C_FIELD(scratch, u16 *, 0x34);
            M2C_FIELD(scratch, u16 *, 0x100) = (u16) M2C_FIELD(sprite, u16 *, 0x16);
            rotation_delta = M2C_FIELD(sprite, u16 *, 0x1A);
            rotation_z = M2C_FIELD(render_state, u16 *, 0xB8);
            rotation_delta -= camera_y;
            rotation_z += rotation_delta;
            M2C_FIELD(scratch, u16 *, 0x104) = (s16) rotation_z;
            rotation_y = M2C_FIELD(sprite, u16 *, 0x18) - 0x100;
            rotation_y += ((u16) M2C_FIELD(scratch, u32 *, 0x38) + 0x100) & 0x1FF;
            M2C_FIELD(scratch, u16 *, 0x102) = (s16) rotation_y;
            pivot_x = M2C_FIELD(sprite, u16 *, 0x20);
            ASM_SET(local_matrix);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            local_matrix = scratch;
            ASM_KEEP_NV(local_matrix);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            M2C_FIELD(scratch, u32 *, 0xE4) = (u32) pivot_x;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            M2C_FIELD(scratch, u16 *, 0x108) = pivot_x;
            pivot_y = M2C_FIELD(sprite, u16 *, 0x22);
            local_matrix = (void *) ((u32) local_matrix | 0xD0);
            M2C_FIELD(scratch, u32 *, 0xE8) = (u32) pivot_y;
            M2C_FIELD(scratch, u16 *, 0x10A) = pivot_y;
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
            scale_x = M2C_FIELD(sprite, u16 *, 0x1C);
            scale = (void *) ((u32) scale | 0x30);
            M2C_FIELD(scratch, u32 *, 0x30) = scale_x;
            scale_y = M2C_FIELD(sprite, u16 *, 0x1E);
            M2C_FIELD(scratch, u32 *, 0x38) = 0x1000;
            M2C_FIELD(scratch, u32 *, 0x34) = scale_y;
            func_80064BC0(local_matrix, scale);
        }
        {
            void *view_matrix;
            void *local_matrix;
            void *combined_matrix;
            view_matrix = matrix_or_part;
            ASM_KEEP_NV(view_matrix);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_SET(local_matrix);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            local_matrix = scratch;
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
        part = M2C_FIELD(sprite, void **, 8);
        matrix_or_part = part + 4;
        M2C_FIELD(scratch, u16 *, 0x24) = (u16) M2C_FIELD(sprite, u16 *, 0x14);
next_part:
        if (!(M2C_FIELD(part, u8 *, 0) & 0x20)) {
            part_u = M2C_FIELD(matrix_or_part, u8 *, 4);
            M2C_FIELD(scratch, u32 *, 8) = (u32) part_u;
            part_width = M2C_FIELD(matrix_or_part, u8 *, 6);
            M2C_FIELD(scratch, u32 *, 0x10) = (u32) part_width;
            if (((part_u + part_width) >= 0x100) || (M2C_FIELD(sprite, u16 *, 0x1A) != 0)) {
                M2C_FIELD(scratch, u32 *, 0x10) = part_width - 1;
            }
            part_v = M2C_FIELD(matrix_or_part, u8 *, 5);
            M2C_FIELD(scratch, u32 *, 0xC) = (u32) part_v;
            part_height = M2C_FIELD(matrix_or_part, u8 *, 7);
            M2C_FIELD(scratch, u32 *, 0x14) = (u32) part_height;
            if (((part_v + part_height) >= 0x100) || (M2C_FIELD(sprite, u16 *, 0x1A) != 0)) {
                M2C_FIELD(scratch, u32 *, 0x14) = part_height - 1;
            }
            if ((M2C_FIELD(part, u8 *, 0) ^ M2C_FIELD(scratch, u16 *, 0x24)) & 1) {
                flipped_width = M2C_FIELD(scratch, u32 *, 0x10);
                flipped_x = (0 - (s8) M2C_FIELD(matrix_or_part, volatile u8 *, -2)) - M2C_FIELD(scratch, u16 *, 0x108);
                flipped_top_x = flipped_x + ((s32) ((s16) flipped_x + ((u32) (flipped_x << 0x10) >> 0x1F)) >> 1);
                half_width = (s32) (flipped_width + (flipped_width >> 0x1F)) >> 1;
                M2C_FIELD(scratch, u16 *, 0x70) = flipped_top_x;
                M2C_FIELD(scratch, u16 *, 0x78) = (s16) (flipped_top_x - ((u16) M2C_FIELD(scratch, u32 *, 0x10) + half_width));
                M2C_FIELD(scratch, u16 *, 0x80) = (s16) ((0 - (s8) M2C_FIELD(matrix_or_part, u8 *, -2)) - M2C_FIELD(scratch, u16 *, 0x108));
                M2C_FIELD(scratch, u16 *, 0x88) = (s16) (M2C_FIELD(scratch, u16 *, 0x80) - (u16) M2C_FIELD(scratch, u32 *, 0x10));
                goto x_ready;
            }
            left_x = (s8) M2C_FIELD(matrix_or_part, volatile u8 *, -2) - M2C_FIELD(scratch, volatile u16 *, 0x108);
            width = M2C_FIELD(scratch, volatile u32 *, 0x10);
            half_left_x = (s16) left_x;
            half_left_x = (s32) (half_left_x + ((u32) (left_x << 0x10) >> 0x1F)) >> 1;
            left_x += half_left_x;
            M2C_FIELD(scratch, u16 *, 0x70) = left_x;
            left_x += (u16) M2C_FIELD(scratch, u32 *, 0x10) + ((s32) (width + (width >> 0x1F)) >> 1);
            M2C_FIELD(scratch, u16 *, 0x78) = left_x;
            bottom_left_x = (s8) M2C_FIELD(matrix_or_part, u8 *, -2) - M2C_FIELD(scratch, u16 *, 0x108);
            M2C_FIELD(scratch, u16 *, 0x80) = bottom_left_x;
            M2C_FIELD(scratch, u16 *, 0x88) = (s16) (bottom_left_x + (u16) M2C_FIELD(scratch, u32 *, 0x10));
x_ready:
            if ((M2C_FIELD(part, u8 *, 0) ^ M2C_FIELD(scratch, u16 *, 0x24)) & 2) {
                edge_y = (0 - (s8) M2C_FIELD(matrix_or_part, volatile u8 *, -1)) - M2C_FIELD(scratch, volatile u16 *, 0x10A);
                height = M2C_FIELD(scratch, volatile u16 *, 0x14);
                M2C_FIELD(scratch, volatile u16 *, 0x7A) = edge_y;
                M2C_FIELD(scratch, volatile u16 *, 0x72) = edge_y;
                edge_y -= height;
                goto y_ready;
            }
            edge_y = (s8) M2C_FIELD(matrix_or_part, volatile u8 *, -1) - M2C_FIELD(scratch, volatile u16 *, 0x10A);
            height = M2C_FIELD(scratch, volatile u16 *, 0x14);
            M2C_FIELD(scratch, volatile u16 *, 0x7A) = edge_y;
            M2C_FIELD(scratch, volatile u16 *, 0x72) = edge_y;
            edge_y = height + edge_y;
y_ready:
            M2C_FIELD(scratch, u16 *, 0x8A) = edge_y;
            M2C_FIELD(scratch, u16 *, 0x82) = edge_y;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            func_800654B0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88, scratch + 0xF0, scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, scratch + 0x90, scratch + 0x94);
            M2C_FIELD(quad, u16 *, 1) = (u16) (M2C_FIELD(scratch, u16 *, 0xF0) + M2C_FIELD(scratch, u16 *, 0xB8));
            M2C_FIELD(quad, u16 *, 3) = (u16) (M2C_FIELD(scratch, u16 *, 0xF2) + M2C_FIELD(scratch, u16 *, 0xBA));
            M2C_FIELD(quad, u16 *, 0xD) = (u16) (M2C_FIELD(scratch, u16 *, 0xF4) + M2C_FIELD(scratch, u16 *, 0xB8));
            M2C_FIELD(quad, u16 *, 0xF) = (u16) (M2C_FIELD(scratch, u16 *, 0xF6) + M2C_FIELD(scratch, u16 *, 0xBA));
            M2C_FIELD(quad, u16 *, 0x19) = (u16) (M2C_FIELD(scratch, u16 *, 0xF8) + M2C_FIELD(scratch, u16 *, 0xB8));
            M2C_FIELD(quad, u16 *, 0x1B) = (u16) (M2C_FIELD(scratch, u16 *, 0xFA) + M2C_FIELD(scratch, u16 *, 0xBA));
            vertex0_visible = 0;
            M2C_FIELD(quad, u16 *, 0x25) = (u16) (M2C_FIELD(scratch, u16 *, 0xFC) + M2C_FIELD(scratch, u16 *, 0xB8));
            screen_y3 = M2C_FIELD(scratch, u16 *, 0xFE) + M2C_FIELD(scratch, u16 *, 0xBA);
            M2C_FIELD(quad, s16 *, 0x27) = screen_y3;
            if ((u32) ((M2C_FIELD(quad, u16 *, 1) + 0x20) & 0xFFFF) < 0x181U) {
                screen_bound = (M2C_FIELD(quad, u16 *, 3) + 0x20) & 0xFFFF;
                vertex0_visible = screen_bound < 0x121U;
            }
            vertex1_visible = 0;
            if ((u32) ((M2C_FIELD(quad, u16 *, 0xD) + 0x20) & 0xFFFF) < 0x181U) {
                screen_bound = (M2C_FIELD(quad, u16 *, 0xF) + 0x20) & 0xFFFF;
                vertex1_visible = screen_bound < 0x121U;
            }
            vertex2_visible = 0;
            first_two_visible = vertex0_visible | vertex1_visible;
            if ((u32) ((M2C_FIELD(quad, u16 *, 0x19) + 0x20) & 0xFFFF) < 0x181U) {
                screen_bound = (M2C_FIELD(quad, u16 *, 0x1B) + 0x20) & 0xFFFF;
                vertex2_visible = screen_bound < 0x121U;
            }
            vertex3_visible = 0;
            first_three_visible = first_two_visible | vertex2_visible;
            if ((u32) ((M2C_FIELD(quad, u16 *, 0x25) + 0x20) & 0xFFFF) < 0x181U) {
                screen_bound = (screen_y3 + 0x20) & 0xFFFF;
                vertex3_visible = screen_bound < 0x121U;
            }
            any_visible = first_three_visible | vertex3_visible;
            if (any_visible != 0) {
                M2C_FIELD(sprite, u16 *, 0x14) = (u16) (M2C_FIELD(sprite, u16 *, 0x14) & 0x7FFF);
                texture_right = M2C_FIELD(scratch, volatile u32 *, 0x10);
                texture_u = M2C_FIELD(scratch, volatile u32 *, 8);
                packed_v = M2C_FIELD(scratch, volatile u32 *, 0x14);
                texture_v = M2C_FIELD(scratch, volatile u32 *, 0xC);
                texture_right += texture_u;
                packed_v += texture_v;
                packed_v <<= 8;
                M2C_FIELD(scratch, u32 *, 0x14) = packed_v;
                packed_v = texture_v;
                ASM_KEEP_NV(packed_v);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                M2C_FIELD(scratch, u32 *, 0x10) = texture_right;
                sprite_flags = M2C_FIELD(scratch, u16 *, 0x24);
                packed_v <<= 8;
                M2C_FIELD(scratch, u32 *, 0xC) = packed_v;
                if (sprite_flags & 0x100) {
                    M2C_FIELD(quad, s16 *, 7) = (s16) M2C_FIELD(sprite, u16 *, 0x12);
                } else {
                    M2C_FIELD(quad, s16 *, 7) = (s16) (M2C_FIELD(sprite, u16 *, 0x12) + M2C_FIELD(matrix_or_part, u16 *, 2));
                }
                M2C_FIELD(quad, s16 *, 5) = (s16) ((u16) M2C_FIELD(scratch, u32 *, 0xC) + (u16) M2C_FIELD(scratch, u32 *, 8));
                M2C_FIELD(quad, s16 *, 0x11) = (s16) ((u16) M2C_FIELD(scratch, u32 *, 0xC) + (u16) M2C_FIELD(scratch, u32 *, 0x10));
                if (M2C_FIELD(sprite, u16 *, 0x10) != 0) {
                    M2C_FIELD(quad, u16 *, 0x13) = (u16) (M2C_FIELD(sprite, u16 *, 0x10) + (M2C_FIELD(matrix_or_part, u16 *, 0) & 0xFF9F));
                } else {
                    M2C_FIELD(quad, u16 *, 0x13) = (u16) M2C_FIELD(matrix_or_part, u16 *, 0);
                }
                M2C_FIELD(quad, s16 *, 0x1D) = (s16) ((u16) M2C_FIELD(scratch, u32 *, 0x14) | (u16) M2C_FIELD(scratch, u32 *, 8));
                M2C_FIELD(quad, s16 *, 0x29) = (s16) ((u16) M2C_FIELD(scratch, u32 *, 0x14) | (u16) M2C_FIELD(scratch, u32 *, 0x10));
                matrix_xx = (s16) M2C_FIELD(scratch, volatile u16 *, 0x50);
                if (matrix_xx >= 0x1800) {
                    scaled_right_u = (u8) M2C_FIELD(quad, s16 *, 0x29);
                    M2C_FIELD(quad, u8 *, 0x29) = (u8) (scaled_right_u + 0xFF);
                    M2C_FIELD(quad, u8 *, 0x11) = scaled_right_u;
                }
                matrix_yy = (s16) M2C_FIELD(scratch, volatile u16 *, 0x58);
                if (matrix_yy >= 0x1800) {
                    scaled_bottom_v = M2C_FIELD(quad, u8 *, 0x2A);
                    M2C_FIELD(quad, u8 *, 0x2A) = (u8) (scaled_bottom_v + 0xFF);
                    M2C_FIELD(quad, u8 *, 0x1E) = scaled_bottom_v;
                }
                if ((s16) M2C_FIELD(quad, u16 *, 1) > (s16) M2C_FIELD(quad, u16 *, 0x25)) {
                    flipped_right_u = (u8) M2C_FIELD(quad, s16 *, 0x29);
                    M2C_FIELD(quad, u8 *, 0x29) = (u8) (flipped_right_u + 0xFF);
                    M2C_FIELD(quad, u8 *, 0x11) = flipped_right_u;
                }
                if ((s16) M2C_FIELD(quad, u16 *, 3) > M2C_FIELD(quad, s16 *, 0x27)) {
                    flipped_bottom_v = M2C_FIELD(quad, u8 *, 0x2A);
                    M2C_FIELD(quad, u8 *, 0x2A) = (u8) (flipped_bottom_v + 0xFF);
                    M2C_FIELD(quad, u8 *, 0x1E) = flipped_bottom_v;
                }
                M2C_FIELD(quad, s32 *, -3) = 0;
                M2C_FIELD(quad, s32 *, 9) = 0;
                color2 = M2C_FIELD(sprite, volatile s32 *, 0xC);
                M2C_FIELD(quad, s32 *, 0x15) = color2;
                color3 = M2C_FIELD(sprite, volatile s32 *, 0xC);
                M2C_FIELD(quad, s8 *, -4) = 0xC;
                M2C_FIELD(quad, s8 *, 0) = 0x3C;
                M2C_FIELD(quad, s32 *, 0x21) = color3;
                if ((M2C_FIELD(scratch, u32 *, 0x24) & 0xC) == 0xC) {
                    M2C_FIELD(quad, s8 *, 0) = 0x3E;
                }
                address_mask = 0xFFFFFF;
                quad += 0x34;
                tag_mask = 0xFF000000;
                ot_entry = (M2C_FIELD(scratch, u32 *, 0xC0) * 4) + M2C_FIELD(scratch, u32 *, 0x20);
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                packet_tag = M2C_FIELD(packet, u32 *, 0);
                ot_tag = *ot_entry;
                packet_tag = (packet_tag & tag_mask) | (ot_tag & address_mask);
                address_mask = (u32) packet & address_mask;
                M2C_FIELD(packet, u32 *, 0) = packet_tag;
                ot_link = (M2C_FIELD(scratch, u32 *, 0xC0) * 4) + M2C_FIELD(scratch, u32 *, 0x20);
                packet += 0x34;
                *ot_link = (*ot_link & tag_mask) | address_mask;
                goto advance_part;
            }
            goto advance_part;
        }
advance_part:
        if ((s8) M2C_FIELD(part, u8 *, 0) >= 0) {
            matrix_or_part += 0xC;
            part += 0xC;
            goto next_part;
        }
        func_80064A40();
        M2C_FIELD(M2C_FIELD(render_state, void **, 0), void **, 0x8D0) = packet;
        return;
    }
    M2C_FIELD(M2C_FIELD(render_state, void **, 0), void **, 0x8D0) = packet;
}
