/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
typedef u8 *(*FnPtr)(void *, s32, void *, void *, u8 *);
typedef struct { s32 w0, w1, w2, w3; } Blk16;
typedef struct { s32 w0, w1; } Blk8;
typedef struct { s32 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9; } Blk40;
#define D_FIELD(type_ptr, offset) (*(type_ptr)(D_80083160 + (offset)))
#define D_LITERAL(type_ptr, offset) (*(type_ptr)((u8 *)0x80083160 + (offset)))

void func_80024390() __attribute__((noreturn));
void func_8002443C() __attribute__((noreturn));
void func_800244B0() __attribute__((noreturn));
void func_80024638() __attribute__((noreturn));
void func_80024640() __attribute__((noreturn));
void func_80024690() __attribute__((noreturn));
void func_80024958() __attribute__((noreturn));
void func_80024AA0() __attribute__((noreturn));
M2C_UNK func_80064840();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
M2C_UNK func_800654B0();
M2C_UNK func_80065820();
M2C_UNK func_80067EF4();
extern M2C_UNK D_8006CD10[3];
extern u8 D_80083160[];

/* Build textured sprite strips and append their packets to the ordering table. */
void func_81904990(void *screen_pos, void *sprite, s32 *ordering_table, s32 draw_mode) {
    u16 saved_draw_mode;
    s32 callback_arg;
    M2C_UNK matrix_arg;
    s32 origin_byte;
    s32 restore_mode;
    s32 angle_bias;
    u8 *row_quad;
    void *render_state;
    void *callback_sprite;
    s32 callback_param;
    void *callback_frame;
    void *callback_data;
    s16 left_x;
    s16 right_x;
    s16 top_y;
    s16 bottom_y;
    s16 strip_bottom;
    u16 base_tpage;
    FnPtr draw_callback;
    u8 *first_quad;
    s32 *mode_link;
    s32 *right_row_link;
    s32 *restore_link;
    s32 *first_link;
    s32 *second_link;
    s32 *left_row_link;
    u8 *restore_packet;
    u8 *packet;
    register u8 *quad_end ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 row_v_offset;
    s32 first_addr;
    s32 second_addr;
    s32 left_row_addr;
    s32 right_row_addr;
    s32 mode_bits;
    s32 u_end;
    s32 v_end;
    s32 wrapped_v_offset;
    s32 row_index;
    u16 angle_or_pivot;
    u16 pivot_y;
    u32 clut_override;
    u16 tpage_offset;
    u16 sprite_flags;
    register u8 prim_code ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 right_u;
    u8 bottom_v;
    register u8 blend_code ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    u8 *frame_data;
    void *frame;
    u8 *frame_header;
    void *setup_arg;
    void *row_heights;
    M2C_UNK *view_matrix;
    s32 quad_words;
    s32 tail_value;
    s32 tail_uv;
    register s32 addr_mask ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 length_mask;
    register u8 *scratch ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *sprite_base ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */

    setup_arg = screen_pos;
    sprite_base = sprite;
    frame = M2C_FIELD(sprite_base, void **, -0x14);
    {
        void **state_ptr;
        state_ptr = (void **)D_80083160;
        ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        callback_arg = M2C_FIELD(sprite_base, s32 *, -0x18);
        render_state = *state_ptr;
    }
    frame_header = M2C_FIELD(frame, void **, 8);
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    M2C_FIELD(scratch, s32 *, 0x0EC) = NULL;
    M2C_FIELD(scratch, u16 *, 0x08C) = 0;
    M2C_FIELD(scratch, u16 *, 0x084) = 0;
    M2C_FIELD(scratch, u16 *, 0x07C) = 0;
    M2C_FIELD(scratch, u16 *, 0x074) = 0;
    packet = M2C_FIELD(render_state, u8 **, 0x8D0);
    M2C_FIELD(scratch, s32 **, 0x020) = ordering_table;
    M2C_FIELD(scratch, s32 *, 0x0C0) = NULL;
    M2C_FIELD(scratch, u16 *, 0x0B8) = (s16) (M2C_FIELD(setup_arg, u16 *, 0) - 0xA0);
    M2C_FIELD(scratch, u16 *, 0x0BA) = (u16) (M2C_FIELD(setup_arg, u16 *, 2) - 0x78);
    saved_draw_mode = (u16) draw_mode;
    mode_bits = draw_mode << 0x10;
    matrix_arg = 0;
    if (mode_bits != 0) {
        func_80067EF4(packet, 0, 0, mode_bits);
        {
            s32 link_mask = 0xFFFFFF;
            matrix_arg = 0xFF000000;
            M2C_FIELD(packet, s32 *, 0) = (M2C_FIELD(packet, s32 *, 0) & 0xFF000000) | (*M2C_FIELD(scratch, s32 **, 0x020) & link_mask);
        }
        mode_link = M2C_FIELD(scratch, s32 **, 0x020);
        setup_arg = (void *) ((s32) packet & 0xFFFFFF);
        packet += 12;
        *mode_link = (*mode_link & 0xFF000000) | (s32) setup_arg;
    }
    quad_words = 9;
    ASM_KEEP_NV(quad_words);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    addr_mask = 0xFFFFFF;
    length_mask = 0xFF000000;
    ASM_KEEP_NV(length_mask);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    view_matrix = D_8006CD10;
    M2C_FIELD(view_matrix, s32 *, 0x1C) = (s32) D_FIELD(s32 *, 0xA0);
    func_800649A0((s32) setup_arg, matrix_arg);
    {
        s32 view_x;
        s32 view_y;
        s32 view_z;
        view_x = D_FIELD(s16 *, 0xC4);
        view_y = D_FIELD(s16 *, 0xC6);
        view_z = D_FIELD(s16 *, 0xC8);
        M2C_FIELD(scratch, s32 *, 0x030) = view_x;
        M2C_FIELD(scratch, s32 *, 0x034) = view_y;
        M2C_FIELD(scratch, s32 *, 0x038) = view_z;
    }
    M2C_FIELD(scratch, u16 *, 0x100) = (u16) M2C_FIELD(frame, u16 *, 0x16);
    M2C_FIELD(scratch, u16 *, 0x104) = (s16) (M2C_FIELD(frame, u16 *, 0x1A) - (u16) M2C_FIELD(scratch, s32 *, 0x034));
    angle_or_pivot = (((u16) M2C_FIELD(scratch, s32 *, 0x038) + 0x100) & 0x1FF);
    angle_bias = M2C_FIELD(frame, u16 *, 0x18) - 0x100;
    M2C_FIELD(scratch, u16 *, 0x102) = angle_or_pivot + angle_bias;
    angle_or_pivot = M2C_FIELD(frame, u16 *, 0x20);
    M2C_FIELD(scratch, s32 *, 0x0E4) = (s32) angle_or_pivot;
    M2C_FIELD(scratch, u16 *, 0x108) = angle_or_pivot;
    pivot_y = M2C_FIELD(frame, u16 *, 0x22);
    M2C_FIELD(scratch, s32 *, 0x0E8) = (s32) pivot_y;
    M2C_FIELD(scratch, u16 *, 0x10A) = pivot_y;
    func_80065820((void *)0x1F800100, (void *)0x1F8000D0);
    {
        s32 scale_x;
        s32 scale_y;
        scale_x = M2C_FIELD(frame, u16 *, 0x1C);
        M2C_FIELD(scratch, s32 *, 0x030) = scale_x;
        scale_y = M2C_FIELD(frame, u16 *, 0x1E);
        M2C_FIELD(scratch, s32 *, 0x038) = (s32)0x1000;
        M2C_FIELD(scratch, s32 *, 0x034) = scale_y;
    }
    func_80064BC0((void *)0x1F8000D0, (void *)0x1F800030);
    func_80064840(view_matrix, (void *)0x1F8000D0, (void *)0x1F800050);
    func_80064D80((void *)0x1F800050);
    func_80064CF0((void *)0x1F800050);
    frame_data = frame_header + 8;
    ASM_KEEP_NV(frame_data);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    M2C_FIELD(scratch, u16 *, 0x024) = (u16) M2C_FIELD(frame, u16 *, 0x14);
    if (!(M2C_FIELD(frame_header, u8 *, 0) & 0x20)) {
        M2C_FIELD(scratch, s32 *, 0x008) = (s32) M2C_FIELD(frame_data, u8 *, 0);
        M2C_FIELD(scratch, s32 *, 0x00C) = (s32) M2C_FIELD(frame_data, u8 *, 1);
        M2C_FIELD(scratch, s32 *, 0x010) = (s32) M2C_FIELD(frame_data, u8 *, 2);
        M2C_FIELD(scratch, s32 *, 0x014) = (s32) M2C_FIELD(frame_data, u8 *, 3);
        if ((M2C_FIELD(frame_header, u8 *, 0) ^ M2C_FIELD(scratch, u16 *, 0x024)) & 1) {
            origin_byte = *(volatile u8 *)((s8 *)frame_data + -6);
            tail_value = (0 - (s32)(s8) origin_byte) - M2C_FIELD(scratch, u16 *, 0x108);
            M2C_FIELD(scratch, u16 *, 0x080) = tail_value;
            M2C_FIELD(scratch, u16 *, 0x070) = tail_value;
            tail_value = tail_value - M2C_FIELD(scratch, u16 *, 0x010);
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_8002443C((u16) M2C_FIELD(scratch, s32 *, 0x010));
            return;
        }
        origin_byte = *(volatile u8 *)((s8 *)frame_data + -6);
        left_x = (s32)(s8) origin_byte - M2C_FIELD(scratch, u16 *, 0x108);
        M2C_FIELD(scratch, u16 *, 0x080) = left_x;
        M2C_FIELD(scratch, u16 *, 0x070) = left_x;
        right_x = left_x + (u16) M2C_FIELD(scratch, s32 *, 0x010);
        M2C_FIELD(scratch, u16 *, 0x088) = right_x;
        M2C_FIELD(scratch, u16 *, 0x078) = right_x;
        if ((M2C_FIELD(frame_header, u8 *, 0) ^ M2C_FIELD(scratch, u16 *, 0x024)) & 2) {
            origin_byte = *(volatile u8 *)((s8 *)frame_data + -5);
            tail_value = (0 - (s32)(s8) origin_byte) - M2C_FIELD(scratch, u16 *, 0x10A);
            M2C_FIELD(scratch, u16 *, 0x07A) = tail_value;
            M2C_FIELD(scratch, u16 *, 0x072) = tail_value;
            tail_value = tail_value - M2C_FIELD(scratch, u16 *, 0x014);
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_800244B0((u16) M2C_FIELD(scratch, s32 *, 0x014));
            return;
        }
        origin_byte = *(volatile u8 *)((s8 *)frame_data + -5);
        top_y = (s32)(s8) origin_byte - M2C_FIELD(scratch, u16 *, 0x10A);
        M2C_FIELD(scratch, u16 *, 0x07A) = top_y;
        M2C_FIELD(scratch, u16 *, 0x072) = top_y;
        bottom_y = top_y + (u16) M2C_FIELD(scratch, s32 *, 0x014);
        M2C_FIELD(scratch, u16 *, 0x08A) = bottom_y;
        M2C_FIELD(scratch, u16 *, 0x082) = bottom_y;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800654B0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88, scratch + 0xF0, scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, scratch + 0x90, scratch + 0x94);
        M2C_FIELD(packet, s16 *, 8) = (s16) (M2C_FIELD(scratch, u16 *, 0x0F0) + M2C_FIELD(scratch, u16 *, 0x0B8));
        M2C_FIELD(packet, s16 *, 0xA) = (s16) (M2C_FIELD(scratch, u16 *, 0x0F2) + M2C_FIELD(scratch, u16 *, 0x0BA));
        M2C_FIELD(packet, s16 *, 0x10) = (s16) (M2C_FIELD(scratch, u16 *, 0x0F4) + M2C_FIELD(scratch, u16 *, 0x0B8));
        M2C_FIELD(packet, s16 *, 0x12) = (s16) (M2C_FIELD(scratch, u16 *, 0x0F6) + M2C_FIELD(scratch, u16 *, 0x0BA));
        M2C_FIELD(packet, s16 *, 0x18) = (s16) (M2C_FIELD(scratch, u16 *, 0x0F8) + M2C_FIELD(scratch, u16 *, 0x0B8));
        M2C_FIELD(packet, s16 *, 0x1A) = (s16) (M2C_FIELD(scratch, u16 *, 0x0FA) + M2C_FIELD(scratch, u16 *, 0x0BA));
        M2C_FIELD(packet, s16 *, 0x20) = (s16) (M2C_FIELD(scratch, u16 *, 0x0FC) + M2C_FIELD(scratch, u16 *, 0x0B8));
        M2C_FIELD(packet, s16 *, 0x22) = (s16) (M2C_FIELD(scratch, u16 *, 0x0FE) + M2C_FIELD(scratch, u16 *, 0x0BA));
        M2C_FIELD(packet, s8 *, 3) = quad_words;
        ASM_USE2_NV(quad_words, quad_words);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        {
            s32 width = M2C_FIELD(scratch, s32 *, 0x010);
            s32 u_start = M2C_FIELD(scratch, s32 *, 0x008);
            width = width - 1;
            {
                s32 last_u = width + u_start;
                u_end = last_u;
            }
        }
        M2C_FIELD(scratch, s32 *, 0x010) = u_end;
        if (u_end & 0x100) {
            M2C_FIELD(scratch, s32 *, 0x010) = u_end - 1;
        }
        {
            s32 height = M2C_FIELD(scratch, s32 *, 0x014);
            s32 v_start = M2C_FIELD(scratch, s32 *, 0x00C);
            height = height - 1;
            {
                s32 last_v = height + v_start;
                v_end = last_v;
            }
        }
        M2C_FIELD(scratch, s32 *, 0x014) = v_end;
        if (v_end & 0x100) {
            M2C_FIELD(scratch, s32 *, 0x014) = v_end - 1;
        }
        M2C_FIELD(scratch, s32 *, 0x014) <<= 8;
        M2C_FIELD(scratch, s32 *, 0x00C) <<= 8;
        clut_override = M2C_FIELD(frame, u16 *, 0x12);
        if (clut_override != 0) {
            if (M2C_FIELD(scratch, u16 *, 0x024) & 0x100) {
                M2C_FIELD(packet, u16 *, 0xE) = clut_override;
                func_80024640();
                return;
            }
            tail_value = clut_override + M2C_FIELD(frame_data, u16 *, -2);
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024638();
            return;
        }
        M2C_FIELD(packet, u16 *, 0xE) = (u16) M2C_FIELD(frame_data, u16 *, -2);
        M2C_FIELD(packet, s16 *, 0xC) = (s16) ((u16) M2C_FIELD(scratch, s32 *, 0x00C) + (u16) M2C_FIELD(scratch, s32 *, 0x008));
        M2C_FIELD(packet, s16 *, 0x14) = (s16) ((u16) M2C_FIELD(scratch, s32 *, 0x00C) + (u16) M2C_FIELD(scratch, s32 *, 0x010));
        tpage_offset = M2C_FIELD(frame, u16 *, 0x10);
        if (tpage_offset != 0) {
            base_tpage = M2C_FIELD(frame_data, u16 *, -4) & 0xFF9F;
            tail_value = tpage_offset + base_tpage;
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024690();
            return;
        }
        M2C_FIELD(packet, u16 *, 0x16) = (u16) M2C_FIELD(frame_data, u16 *, -4);
        M2C_FIELD(packet, s16 *, 0x1C) = (s16) ((u16) M2C_FIELD(scratch, s32 *, 0x014) | (u16) M2C_FIELD(scratch, s32 *, 0x008));
        {
            register s32 packed_v ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            packed_v = (u16) M2C_FIELD(scratch, s32 *, 0x014);
            M2C_FIELD(packet, s16 *, 0x24) = (s16) (packed_v | (u16) M2C_FIELD(scratch, s32 *, 0x010));
        }
        if (M2C_FIELD(packet, s16 *, 0x20) < M2C_FIELD(packet, s16 *, 8)) {
            right_u = (u8) M2C_FIELD(packet, s16 *, 0x24);
            M2C_FIELD(packet, u8 *, 0x24) = (u8) (right_u + 0xFF);
            M2C_FIELD(packet, u8 *, 0x14) = right_u;
        }
        if (M2C_FIELD(packet, s16 *, 0xA) > M2C_FIELD(packet, s16 *, 0x22)) {
            bottom_v = M2C_FIELD(packet, u8 *, 0x25);
            M2C_FIELD(packet, u8 *, 0x25) = (u8) (bottom_v + 0xFF);
            M2C_FIELD(packet, u8 *, 0x1D) = bottom_v;
        }
        prim_code = M2C_FIELD(frame_data, u8 *, -7);
        M2C_FIELD(frame, u8 *, 0xF) = prim_code;
        sprite_flags = M2C_FIELD(scratch, u16 *, 0x024);
        if (sprite_flags & 8) {
            blend_code = sprite_flags & 4;
            if (blend_code != 0) {
                blend_code = prim_code | 2;
            } else {
                blend_code = prim_code & 0xFD;
            }
            M2C_FIELD(frame, u8 *, 0xF) = blend_code;
        }
        first_quad = packet;
        M2C_FIELD(packet, s32 *, 4) = (s32) M2C_FIELD(frame, s32 *, 0xC);
        M2C_FIELD(sprite_base, u16 *, 0x62) = (u16) M2C_FIELD(packet, s16 *, 0xA);
        quad_end = first_quad + 32;
        strip_bottom = (u16) M2C_FIELD(packet, s16 *, 0xA) + M2C_FIELD(sprite_base, u16 *, 0x64);
        M2C_FIELD(packet, s16 *, 0x22) = strip_bottom;
        M2C_FIELD(packet, s16 *, 0x1A) = strip_bottom;
        first_addr = (s32) packet & addr_mask;
        M2C_FIELD(packet, s32 *, 0) = (M2C_FIELD(packet, s32 *, 0) & length_mask) | (*M2C_FIELD(scratch, s32 **, 0x020) & addr_mask);
        first_link = M2C_FIELD(scratch, s32 **, 0x020);
        packet += 40;
        *first_link = (*first_link & length_mask) | first_addr;
        M2C_FIELD(packet, s8 *, 3) = quad_words;

        *(Blk40 *)packet = *(Blk40 *)first_quad;
        row_index = 1;
        wrapped_v_offset = -0x30;
        row_heights = sprite_base + 2;
        second_addr = (s32) packet & addr_mask;
        M2C_FIELD(packet, u16 *, 8) = (u16) (M2C_FIELD(packet, u16 *, 8) + 0x40);
        M2C_FIELD(packet, u16 *, 0x10) = (u16) (M2C_FIELD(packet, u16 *, 0x10) + 0x40);
        M2C_FIELD(packet, u16 *, 0x18) = (u16) (M2C_FIELD(packet, u16 *, 0x18) + 0x40);
        M2C_FIELD(packet, u16 *, 0x20) = (u16) (M2C_FIELD(packet, u16 *, 0x20) + 0x40);
        M2C_FIELD(packet, s32 *, 0) = (M2C_FIELD(packet, s32 *, 0) & length_mask) | (*M2C_FIELD(scratch, s32 **, 0x020) & addr_mask);
        second_link = M2C_FIELD(scratch, s32 **, 0x020);
        packet += 40;
        quad_end = packet + 32;
        *second_link = (*second_link & length_mask) | second_addr;
    next_row:
        M2C_FIELD(quad_end, s8 *, -0x1D) = quad_words;
        *(Blk40 *)packet = *(Blk40 *)first_quad;
        M2C_FIELD(quad_end, s16 *, -0x16) = (s16) (M2C_FIELD(sprite_base, u16 *, 0x62) + M2C_FIELD(row_heights, u16 *, 0x62));
        M2C_FIELD(quad_end, s16 *, -0xE) = (s16) (M2C_FIELD(sprite_base, u16 *, 0x62) + M2C_FIELD(row_heights, u16 *, 0x62));
        M2C_FIELD(quad_end, s16 *, -6) = (s16) (M2C_FIELD(sprite_base, u16 *, 0x62) + M2C_FIELD(row_heights, u16 *, 0x64));
        M2C_FIELD(quad_end, s16 *, 2) = (s16) (M2C_FIELD(sprite_base, u16 *, 0x62) + M2C_FIELD(row_heights, u16 *, 0x64));
        row_v_offset = row_index * 0x10;
        if (row_index < 4) {
            tail_value = M2C_FIELD(quad_end, u8 *, -0x13);
            tail_uv = M2C_FIELD(quad_end, u8 *, -0xB);
            tail_value = tail_value + row_v_offset;
            M2C_FIELD(quad_end, u8 *, -0x13) = (u8) tail_value;
            tail_value = M2C_FIELD(quad_end, u8 *, -3);
            tail_uv = tail_uv + row_v_offset;
            M2C_FIELD(quad_end, u8 *, -0xB) = (u8) tail_uv;
            tail_uv = M2C_FIELD(quad_end, u8 *, 5);
            tail_value = tail_value + row_v_offset;
            tail_uv = tail_uv + row_v_offset;
            ASM_KEEP(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN(tail_uv);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024958();
            return;
        }
        tail_value = M2C_FIELD(quad_end, u8 *, -0x13);
        tail_uv = M2C_FIELD(quad_end, u8 *, -0xB);
        tail_value = tail_value + wrapped_v_offset;
        M2C_FIELD(quad_end, u8 *, -0x13) = (u8) tail_value;
        tail_value = M2C_FIELD(quad_end, u8 *, -3);
        tail_uv = tail_uv + wrapped_v_offset;
        M2C_FIELD(quad_end, u8 *, -0xB) = (u8) tail_uv;
        tail_uv = M2C_FIELD(quad_end, u8 *, 5);
        tail_value = tail_value + wrapped_v_offset;
        tail_uv = tail_uv + wrapped_v_offset;
        M2C_FIELD(quad_end, u8 *, -3) = (u8) tail_value;
        M2C_FIELD(quad_end, u8 *, 5) = (u8) tail_uv;
        quad_end += 40;
        row_quad = packet;
        ASM_KEEP(row_quad);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        left_row_addr = (s32) packet & addr_mask;
        {
            register s32 packet_tag ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
            packet_tag = M2C_FIELD(packet, s32 *, 0);
            M2C_FIELD(packet, s32 *, 0) = (packet_tag & length_mask) | (*M2C_FIELD(scratch, s32 **, 0x020) & addr_mask);
        }
        left_row_link = M2C_FIELD(scratch, s32 **, 0x020);
        packet += 40;
        *left_row_link = (*left_row_link & length_mask) | left_row_addr;
        M2C_FIELD(quad_end, s8 *, -0x1D) = quad_words;
        *(Blk40 *)packet = *(Blk40 *)row_quad;
        wrapped_v_offset += 0x10;
        row_heights = (u8 *)row_heights + 2;
        row_index += 1;
        right_row_addr = (s32) packet & addr_mask;
        M2C_FIELD(quad_end, u16 *, -0x18) = (u16) (M2C_FIELD(quad_end, u16 *, -0x18) + 0x40);
        M2C_FIELD(quad_end, u16 *, -0x10) = (u16) (M2C_FIELD(quad_end, u16 *, -0x10) + 0x40);
        M2C_FIELD(quad_end, u16 *, -8) = (u16) (M2C_FIELD(quad_end, u16 *, -8) + 0x40);
        M2C_FIELD(quad_end, u16 *, 0) = (u16) (M2C_FIELD(quad_end, u16 *, 0) + 0x40);
        {
            register s32 packet_tag ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
            packet_tag = M2C_FIELD(packet, s32 *, 0);
            M2C_FIELD(packet, s32 *, 0) = (packet_tag & length_mask) | (*M2C_FIELD(scratch, s32 **, 0x020) & addr_mask);
        }
        right_row_link = M2C_FIELD(scratch, s32 **, 0x020);
        quad_end += 40;
        *right_row_link = (*right_row_link & length_mask) | right_row_addr;
        packet += 40;
        if (row_index < 8) {
            goto next_row;
        }
        func_80024AA0();
    }
    draw_callback = M2C_FIELD(frame_data, FnPtr *, 0);
    if (draw_callback != NULL) {
        callback_sprite = sprite_base;
        callback_frame = frame;
        callback_param = callback_arg;
        callback_data = frame_header;
        packet = draw_callback(callback_sprite, callback_param, callback_frame, callback_data, packet);
    }
    if ((s8) M2C_FIELD(frame_header, u8 *, 0) >= 0) {
        frame_data += 12;
        frame_header += 12;
        ASM_KEEP(frame_data);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(frame_header);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        func_80024390();
        return;
    }
    restore_mode = saved_draw_mode << 0x10;

    restore_packet = packet;
    if (restore_mode != 0) {
        func_80067EF4(restore_packet, 0, 1);
        M2C_FIELD(packet, s32 *, 0) = (M2C_FIELD(packet, s32 *, 0) & 0xFF000000) | (*M2C_FIELD(scratch, s32 **, 0x020) & 0xFFFFFF);
        restore_link = M2C_FIELD(scratch, s32 **, 0x020);
        restore_packet = (u8 *) ((s32) packet & 0xFFFFFF);
        packet += 12;
        *restore_link = (*restore_link & 0xFF000000) | (s32) restore_packet;
    }
    func_80064A40((s32) restore_packet);
    {
        u8 *state_slot = D_80083160;
        u64 state_bits = *(u64 *)state_slot;
        void *final_state = (void *)(u32)state_bits;
        M2C_FIELD(final_state, u8 **, 0x8D0) = packet;
    }
}
