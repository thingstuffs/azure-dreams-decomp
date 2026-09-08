/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80064840();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
u32 func_80065420();
M2C_UNK func_800654B0();
M2C_UNK func_80065820();
M2C_UNK func_80170A78();
M2C_UNK func_80170B40();
M2C_UNK func_80170BAC();
M2C_UNK func_80170DF8();
M2C_UNK func_80170E48();
M2C_UNK func_80170F78();
extern M2C_UNK D_8006CD30[];
extern struct S_8003E2D8 D_80083160;

#ifdef __mips__
static const u32 split_prefix[] __asm__("func_80170800")
    __attribute__((section(".text.func_80170800"), aligned(4))) = {
    0x80171850, 0x80171A18,
    0x80172204, 0x80172204, 0x80172204, 0x80172230,
    0x801721B0, 0x801721B0, 0x801721B0, 0x8017215C,
    0x80172194, 0x80172230, 0x80172230, 0x801721F4,
    0x801738F8, 0x801738F0, 0x801738E8, 0x80173900,
    0x801738A8, 0x801738A0, 0x80173898,
    0x00000001, 0x00020002, 0x00010000, 0x0002FFFE,
    0x0000FFFF, 0xFFFEFFFE, 0xFFFF0000, 0xFFFE0002,
};
__asm__(".globl func_80170800\n"
        ".size func_80170800, 2008");
#define BODY_NAME func_80170874
#else
#define BODY_NAME func_80170800
#endif

/* Project sprite entries into textured quads and append visible quads to the ordering table. */
void BODY_NAME(void *size_arg, void *position_arg, void *sprite_arg, s16 depth_bias_arg) {
    s32 screen_y3;
    register s32 view_rot_z;
    register s32 view_rot_x;
    register s32 view_rot_y;
    s16 top_y;
    s16 bottom_y;
    s16 flipped_left_x;
    s16 left_x;
    s16 right_x;
    s16 flipped_top_y;
    s32 first_three_visible;
    s32 first_two_visible;
    s32 *ot_entry;
    s32 corner2_visible;
    s32 corner0_visible;
    s32 corner1_visible;
    s32 corner3_visible;
    u32 view_y_angle;
    u16 field_value;
    u16 scale_y;
    register u16 sprite_flags;
    u32 depth;
    u32 ot_index;
    u32 neg_width;
    u32 depth_scaled;
    register u32 coord_offset;
    register u32 uv_right ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 uv_bottom ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 screen_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u32 coord_value;
    u32 packet_addr;
    register u8 packet_code ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 right_u;
    u8 bottom_v;
    register u8 blend_code ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *(*draw_callback)(void *, void *, void *, void *, void *);
    void *entry_uv;
    void *render_data;
    register void *render_state ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u32 address_mask;
    register void *render_buffer ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 load_dependency;
    void *packet;
    void *sprite_size = size_arg;
    register void *position = position_arg;
    register void *sprite ASM_REG("$20") = sprite_arg;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s16 depth_bias ASM_REG("$16") = depth_bias_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *work_src ASM_REG("$4") = (u8 *)0x1F800004;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *work_dst ASM_REG("$5") = (u8 *)0x1F8000F8;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register u8 *work_aux ASM_REG("$6") = (u8 *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register u8 *state_page ASM_REG("$8") = (u8 *)0x80080000;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *scratch_page;
    register u8 *projection_flags;
    ASM_KEEP_MEMDEP_NV(position, load_dependency, M2C_FIELD(&D_80083160, void **, 0));   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    scratch_page = (u8 *)0x1F800000;
    ASM_KEEP_NV(work_aux);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(sprite_size);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(sprite);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(depth_bias);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    work_aux = (u8 *)((u32)work_aux | 0xD0);
    render_buffer = M2C_FIELD(&D_80083160, void **, 0);
    M2C_FIELD(scratch_page, u32 *, 0x90) = 0;
    M2C_FIELD(scratch_page, u16 *, 0xCC) = 0;
    M2C_FIELD(scratch_page, u16 *, 0xC4) = 0;
    M2C_FIELD(scratch_page, u16 *, 0xBC) = 0;
    M2C_FIELD(scratch_page, u16 *, 0xB4) = 0;
    M2C_FIELD(scratch_page, u32 *, 0x24) = render_buffer + 0xB0;
    M2C_FIELD(scratch_page, u16 *, 4) = M2C_FIELD(position, u16 *, 2);
    projection_flags = scratch_page;
    ASM_KEEP_MEMDEP_NV(scratch_page, load_dependency, M2C_FIELD(&D_80083160, void **, 0));   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    ASM_SET(state_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(projection_flags);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    M2C_FIELD(scratch_page, u16 *, 6) = M2C_FIELD(position, u16 *, 6);
    M2C_FIELD(scratch_page, u16 *, 8) = M2C_FIELD(position, u16 *, 0xA);
    projection_flags = (u8 *)((u32)projection_flags | 0xD4);
    packet = M2C_FIELD(render_buffer, void **, 0x8D0);
    render_state = (void *)(state_page + 0x3160);
    M2C_FIELD(scratch_page, u32 *, 0x100) = func_80065420(work_src, work_dst, work_aux, projection_flags);
    M2C_FIELD(sprite, u16 *, 0x14) = (u16)(M2C_FIELD(sprite, u16 *, 0x14) | 0x8000);
    depth = M2C_FIELD(scratch_page, u32 *, 0x100);
    depth_scaled = depth * 4;
    depth -= 0xA;
    ot_index = depth - depth_bias;
    render_data = &D_8006CD30;
    M2C_FIELD(render_data, s32 *, 0x1C) = (s32)depth_scaled;
    M2C_FIELD(scratch_page, u32 *, 0x100) = ot_index;
    if (ot_index < 0x1D6U) {
        address_mask = 0x00FF0000;
        func_800649A0();
        work_src = scratch_page;
        ASM_KEEP_NV(work_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_src = (u8 *)((u32)work_src | 0xA4);
        screen_offset = M2C_FIELD(scratch_page, u16 *, 0xF8);
        work_dst = scratch_page;
        screen_offset -= 0xA0;
        M2C_FIELD(scratch_page, u16 *, 0xF8) = screen_offset;
        screen_offset = M2C_FIELD(scratch_page, u16 *, 0xFA);
        view_rot_x = M2C_FIELD(render_state, s16 *, 0xC4);
        view_rot_y = M2C_FIELD(render_state, s16 *, 0xC6);
        view_rot_z = M2C_FIELD(render_state, s16 *, 0xC8);
        screen_offset -= 0x78;
        M2C_FIELD(scratch_page, u16 *, 0xFA) = screen_offset;
        M2C_FIELD(scratch_page, u32 *, 0x34) = view_rot_x;
        M2C_FIELD(scratch_page, u32 *, 0x38) = view_rot_y;
        M2C_FIELD(scratch_page, u32 *, 0x3C) = view_rot_z;
        ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        field_value = M2C_FIELD(sprite, u16 *, 0x16);
        view_y_angle = M2C_FIELD(scratch_page, u16 *, 0x38);
        work_dst = (u8 *)((u32)work_dst | 0x74);
        ASM_KEEP_NV(work_dst);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        M2C_FIELD(scratch_page, u16 *, 0xA4) = field_value;
        coord_offset = M2C_FIELD(sprite, u16 *, 0x1A);
        coord_value = M2C_FIELD(render_state, u16 *, 0xB8);
        coord_offset -= view_y_angle;
        coord_value += coord_offset;
        M2C_FIELD(scratch_page, u16 *, 0xA8) = coord_value;
        coord_offset = M2C_FIELD(sprite, u16 *, 0x18);
        coord_value = M2C_FIELD(scratch_page, u16 *, 0x3C);
        coord_offset -= 0x100;
        coord_value = (coord_value + 0x100) & 0x1FF;
        coord_offset += coord_value;
        M2C_FIELD(scratch_page, u16 *, 0xA6) = coord_offset;
        field_value = M2C_FIELD(sprite, u16 *, 0x20);
        M2C_FIELD(scratch_page, u32 *, 0x88) = field_value;
        M2C_FIELD(scratch_page, u16 *, 0xAC) = field_value;
        coord_value = M2C_FIELD(sprite, u16 *, 0x22);
        ASM_KEEP_DEP_NV(address_mask, coord_value);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        address_mask |= 0xFFFF;
        ASM_KEEP_NV(address_mask);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        M2C_FIELD(scratch_page, u32 *, 0x8C) = coord_value;
        M2C_FIELD(scratch_page, u16 *, 0xAE) = coord_value;
        func_80065820(work_src, work_dst, view_y_angle, view_rot_z);
        work_src = scratch_page;
        ASM_KEEP_NV(work_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_src = (u8 *)((u32)work_src | 0x74);
        work_dst = scratch_page;
        ASM_KEEP_NV(work_dst);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_dst = (u8 *)((u32)work_dst | 0x34);
        M2C_FIELD(scratch_page, u32 *, 0x34) = M2C_FIELD(sprite, u16 *, 0x1C);
        scale_y = M2C_FIELD(sprite, u16 *, 0x1E);
        M2C_FIELD(scratch_page, u32 *, 0x3C) = 0x1000;
        M2C_FIELD(scratch_page, u32 *, 0x38) = scale_y;
        func_80064BC0(work_src, work_dst);
        work_src = render_data;
        ASM_KEEP_NV(work_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_dst = scratch_page;
        ASM_KEEP_NV(work_dst);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_dst = (u8 *)((u32)work_dst | 0x74);
        work_aux = scratch_page;
        ASM_KEEP_NV(work_aux);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        work_aux = (u8 *)((u32)work_aux | 0x54);
        func_80064840(work_src, work_dst, work_aux);
        work_src = scratch_page;
        ASM_KEEP_NV(work_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_src = (u8 *)((u32)work_src | 0x54);
        func_80064D80(work_src);
        work_src = scratch_page;
        ASM_KEEP_NV(work_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_src = (u8 *)((u32)work_src | 0x54);
        func_80064CF0(work_src);
        render_data = M2C_FIELD(sprite, void **, 8);
        entry_uv = render_data + 8;
        M2C_FIELD(scratch_page, u16 *, 0x28) = M2C_FIELD(sprite, u16 *, 0x14);
next_entry:
        if (!(M2C_FIELD(render_data, u8 *, 0) & 0x20)) {
            M2C_FIELD(scratch_page, u32 *, 0xC) = M2C_FIELD(entry_uv, u8 *, 0);
            M2C_FIELD(scratch_page, u32 *, 0x10) = M2C_FIELD(entry_uv, u8 *, 1);
            M2C_FIELD(scratch_page, u32 *, 0x14) = M2C_FIELD(entry_uv, u8 *, 2);
            M2C_FIELD(scratch_page, u32 *, 0x18) = M2C_FIELD(entry_uv, u8 *, 3);
            if ((M2C_FIELD(render_data, u8 *, 0) ^ M2C_FIELD(scratch_page, u16 *, 0x28)) & 1) {
                flipped_left_x = (0 - ((s32)(0 - M2C_FIELD(sprite_size, s16 *, 0x4E)) / 2)) - M2C_FIELD(scratch_page, u16 *, 0xAC);
                M2C_FIELD(scratch_page, u16 *, 0xC0) = flipped_left_x;
                M2C_FIELD(scratch_page, u16 *, 0xB0) = flipped_left_x;
                right_x = flipped_left_x - M2C_FIELD(sprite_size, u16 *, 0x4E);
            } else {
                neg_width = 0 - M2C_FIELD(sprite_size, s16 *, 0x4E);
                left_x = ((s32)(neg_width + (neg_width >> 0x1F)) >> 1) - M2C_FIELD(scratch_page, u16 *, 0xAC);
                M2C_FIELD(scratch_page, u16 *, 0xC0) = left_x;
                M2C_FIELD(scratch_page, u16 *, 0xB0) = left_x;
                coord_offset = (u16)M2C_FIELD(sprite_size, s16 *, 0x4E);
                right_x = left_x + coord_offset;
            }
            M2C_FIELD(scratch_page, u16 *, 0xC8) = right_x;
            M2C_FIELD(scratch_page, u16 *, 0xB8) = right_x;
            if ((M2C_FIELD(render_data, u8 *, 0) ^ M2C_FIELD(scratch_page, u16 *, 0x28)) & 2) {
                flipped_top_y = M2C_FIELD(sprite_size, u16 *, 0x50) - M2C_FIELD(scratch_page, u16 *, 0xAE);
                M2C_FIELD(scratch_page, u16 *, 0xBA) = flipped_top_y;
                M2C_FIELD(scratch_page, u16 *, 0xB2) = flipped_top_y;
                bottom_y = flipped_top_y - M2C_FIELD(sprite_size, u16 *, 0x50);
            } else {
                top_y = (0 - M2C_FIELD(sprite_size, u16 *, 0x50)) - M2C_FIELD(scratch_page, u16 *, 0xAE);
                M2C_FIELD(scratch_page, u16 *, 0xBA) = top_y;
                M2C_FIELD(scratch_page, u16 *, 0xB2) = top_y;
                coord_offset = M2C_FIELD(sprite_size, u16 *, 0x50);
                bottom_y = top_y + coord_offset;
            }
            M2C_FIELD(scratch_page, u16 *, 0xCA) = bottom_y;
            M2C_FIELD(scratch_page, u16 *, 0xC2) = bottom_y;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            func_800654B0(scratch_page + 0xB0, scratch_page + 0xB8, scratch_page + 0xC0, scratch_page + 0xC8, scratch_page + 0x94, scratch_page + 0x98, scratch_page + 0x9C, scratch_page + 0xA0, scratch_page + 0xD0, scratch_page + 0xD4);
            M2C_FIELD(packet, u16 *, 8) = M2C_FIELD(scratch_page, u16 *, 0x94) + M2C_FIELD(scratch_page, u16 *, 0xF8);
            M2C_FIELD(packet, u16 *, 0xA) = M2C_FIELD(scratch_page, u16 *, 0x96) + M2C_FIELD(scratch_page, u16 *, 0xFA);
            M2C_FIELD(packet, u16 *, 0x10) = M2C_FIELD(scratch_page, u16 *, 0x98) + M2C_FIELD(scratch_page, u16 *, 0xF8);
            M2C_FIELD(packet, u16 *, 0x12) = M2C_FIELD(scratch_page, u16 *, 0x9A) + M2C_FIELD(scratch_page, u16 *, 0xFA);
            M2C_FIELD(packet, u16 *, 0x18) = M2C_FIELD(scratch_page, u16 *, 0x9C) + M2C_FIELD(scratch_page, u16 *, 0xF8);
            M2C_FIELD(packet, u16 *, 0x1A) = M2C_FIELD(scratch_page, u16 *, 0x9E) + M2C_FIELD(scratch_page, u16 *, 0xFA);
            corner0_visible = 0;
            M2C_FIELD(packet, u16 *, 0x20) = M2C_FIELD(scratch_page, u16 *, 0xA0) + M2C_FIELD(scratch_page, u16 *, 0xF8);
            screen_y3 = M2C_FIELD(scratch_page, u16 *, 0xA2) + M2C_FIELD(scratch_page, u16 *, 0xFA);
            M2C_FIELD(packet, s16 *, 0x22) = screen_y3;
            if ((u32)((M2C_FIELD(packet, u16 *, 8) + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((M2C_FIELD(packet, u16 *, 0xA) + 0x20) & 0xFFFF);
                corner0_visible = y_bound < 0x121U;
            }
            corner1_visible = 0;
            if ((u32)((M2C_FIELD(packet, u16 *, 0x10) + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((M2C_FIELD(packet, u16 *, 0x12) + 0x20) & 0xFFFF);
                corner1_visible = y_bound < 0x121U;
            }
            corner2_visible = 0;
            first_two_visible = corner0_visible | corner1_visible;
            if ((u32)((M2C_FIELD(packet, u16 *, 0x18) + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((M2C_FIELD(packet, u16 *, 0x1A) + 0x20) & 0xFFFF);
                corner2_visible = y_bound < 0x121U;
            }
            corner3_visible = 0;
            first_three_visible = first_two_visible | corner2_visible;
            if ((u32)((M2C_FIELD(packet, u16 *, 0x20) + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((screen_y3 + 0x20) & 0xFFFF);
                corner3_visible = y_bound < 0x121U;
            }
            if ((first_three_visible | corner3_visible) != 0) {
                M2C_FIELD(packet, s8 *, 3) = 9;
                M2C_FIELD(sprite, u16 *, 0x14) = (u16)(M2C_FIELD(sprite, u16 *, 0x14) & 0x7FFF);
                {
                    u32 texel_count = M2C_FIELD(scratch_page, u32 *, 0x14);
                    uv_right = M2C_FIELD(scratch_page, u32 *, 0xC);
                    texel_count -= 1;
                    uv_right = texel_count + uv_right;
                }
                M2C_FIELD(scratch_page, u32 *, 0x14) = uv_right;
                if (uv_right & 0x100) {
                    register u32 uv_adjusted ASM_REG("$2") = uv_right - 1;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    M2C_FIELD(scratch_page, u32 *, 0x14) = uv_adjusted;
                }
                {
                    u32 texel_count = M2C_FIELD(scratch_page, u32 *, 0x18);
                    uv_bottom = M2C_FIELD(scratch_page, u32 *, 0x10);
                    texel_count -= 1;
                    uv_bottom = texel_count + uv_bottom;
                }
                M2C_FIELD(scratch_page, u32 *, 0x18) = uv_bottom;
                if (uv_bottom & 0x100) {
                    register u32 uv_adjusted ASM_REG("$2") = uv_bottom - 1;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    M2C_FIELD(scratch_page, u32 *, 0x18) = uv_adjusted;
                }
                M2C_FIELD(scratch_page, u32 *, 0x18) <<= 8;
                M2C_FIELD(scratch_page, u32 *, 0x10) <<= 8;
                if (M2C_FIELD(scratch_page, u16 *, 0x28) & 0x100) {
                    M2C_FIELD(packet, s16 *, 0xE) = M2C_FIELD(sprite, u16 *, 0x12);
                } else {
                    M2C_FIELD(packet, s16 *, 0xE) = (s16)(M2C_FIELD(sprite, u16 *, 0x12) + M2C_FIELD(entry_uv, u16 *, -2));
                }
                M2C_FIELD(packet, s16 *, 0xC) = (s16)((u16)M2C_FIELD(scratch_page, u32 *, 0x10) + (u16)M2C_FIELD(scratch_page, u32 *, 0xC));
                M2C_FIELD(packet, s16 *, 0x14) = (s16)((u16)M2C_FIELD(scratch_page, u32 *, 0x10) + (u16)M2C_FIELD(scratch_page, u32 *, 0x14));
                if (M2C_FIELD(sprite, u16 *, 0x10) != 0) {
                    field_value = (M2C_FIELD(entry_uv, u16 *, -4) & 0xFF9F) + M2C_FIELD(sprite, u16 *, 0x10);
                } else {
                    field_value = M2C_FIELD(entry_uv, u16 *, -4);
                }
                M2C_FIELD(packet, u16 *, 0x16) = field_value;
                M2C_FIELD(packet, s16 *, 0x1C) = (s16)((u16)M2C_FIELD(scratch_page, u32 *, 0x18) | (u16)M2C_FIELD(scratch_page, u32 *, 0xC));
                uv_right = (u16)M2C_FIELD(scratch_page, u32 *, 0x18);
                uv_right |= (u16)M2C_FIELD(scratch_page, u32 *, 0x14);
                M2C_FIELD(packet, s16 *, 0x24) = uv_right;
                if ((s16)M2C_FIELD(packet, u16 *, 0x20) < (s16)M2C_FIELD(packet, u16 *, 8)) {
                    right_u = M2C_FIELD(packet, u8 *, 0x24);
                    M2C_FIELD(packet, u8 *, 0x24) = (u8)(right_u + 0xFF);
                    M2C_FIELD(packet, u8 *, 0x14) = right_u;
                }
                if ((s16)M2C_FIELD(packet, u16 *, 0xA) > M2C_FIELD(packet, s16 *, 0x22)) {
                    bottom_v = M2C_FIELD(packet, u8 *, 0x25);
                    M2C_FIELD(packet, u8 *, 0x25) = (u8)(bottom_v + 0xFF);
                    M2C_FIELD(packet, u8 *, 0x1D) = bottom_v;
                }
                packet_code = M2C_FIELD(entry_uv, u8 *, -7);
                M2C_FIELD(sprite, u8 *, 0xF) = packet_code;
                sprite_flags = M2C_FIELD(scratch_page, u16 *, 0x28);
                if (sprite_flags & 8) {
                    blend_code = sprite_flags & 4;
                    if (blend_code) {
                        blend_code = packet_code | 2;
                    } else {
                        blend_code = packet_code & 0xFD;
                    }
                    M2C_FIELD(sprite, u8 *, 0xF) = blend_code;
                }
                M2C_FIELD(packet, s32 *, 4) = (s32)M2C_FIELD(sprite, s32 *, 0xC);
                packet_addr = (u32)packet & address_mask;
                M2C_FIELD(packet, s32 *, 0) = (s32)((M2C_FIELD(packet, s32 *, 0) & 0xFF000000) | (*((u32 *)((M2C_FIELD(scratch_page, u32 *, 0x100) * 4) + M2C_FIELD(scratch_page, u32 *, 0x24))) & address_mask));
                ot_entry = (s32 *)((M2C_FIELD(scratch_page, u32 *, 0x100) * 4) + M2C_FIELD(scratch_page, u32 *, 0x24));
                packet += 0x28;
                *ot_entry = (*ot_entry & 0xFF000000) | packet_addr;
            }
        } else {
            draw_callback = (void *(*)(void *, void *, void *, void *, void *))M2C_FIELD(entry_uv, void **, 0);
            if (draw_callback != NULL) {
                packet = draw_callback(sprite_size, position, sprite, render_data, packet);
            }
        }
        if ((s8)M2C_FIELD(render_data, u8 *, 0) >= 0) {
            entry_uv += 0xC;
            render_data += 0xC;
            goto next_entry;
        }
        func_80064A40();
    }
    M2C_FIELD(M2C_FIELD(render_state, void **, 0), void **, 0x8D0) = packet;
}
