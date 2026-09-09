/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
typedef u8 *(*FnPtr)(void *, s32, void *, void *, u8 *);
typedef struct { s32 w0, w1, w2, w3; } Blk16;
typedef struct { s32 w0, w1; } Blk8;
typedef struct { s32 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9; } Blk40;
typedef struct S_func_81904990_1 {
    s32 unk_00;
    void * unk_04;
    u8 pad_08[0x72];
    u16 unk_7A;
    u16 unk_7C;
} S_func_81904990_1;

typedef struct S_func_81904990_2 {
    u8 pad_00[0x8];
    void * unk_08;
    union {
        s32 as_s32_0C;
        struct {
            u8 pad_0C[0x3];
            u8 unk_0F;
        } as_u8_0F;
    } unk_0C;
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
} S_func_81904990_2;

typedef struct S_func_81904990_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    union {
        FnPtr as_FnPtr_08;
        u8 as_u8_08;
        struct {
            u8 pad_08[0x1];
            u8 unk_09;
        } as_u8_09;
        struct {
            u8 pad_08[0x2];
            u8 unk_0A;
        } as_u8_0A;
        struct {
            u8 pad_08[0x3];
            u8 unk_0B;
        } as_u8_0B;
    } unk_08;
} S_func_81904990_3;

typedef struct S_func_81904990_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    union {
        s32 as_s32_10;
        u16 as_u16_10;
    } unk_10;
    union {
        s32 as_s32_14;
        u16 as_u16_14;
    } unk_14;
    u8 pad_18[0x8];
    s32 * unk_20;
    u16 unk_24;
    u8 pad_26[0xA];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x34];
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
    s32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
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
} S_func_81904990_4;

typedef struct S_func_81904990_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_func_81904990_5;

typedef struct S_func_81904990_6 {
    u16 unk_00;
    u16 unk_02;
} S_func_81904990_6;

typedef struct S_func_81904990_7 {
    union {
        s32 as_s32_00;
        struct {
            u8 pad_00[0x3];
            s8 unk_03;
        } as_s8_03;
    } unk_00;
    s32 unk_04;
    union {
        s16 as_s16_08;
        u16 as_u16_08;
    } unk_08;
    s16 unk_0A;
    union {
        s16 as_s16_0C;
        struct {
            u8 pad_0C[0x1];
            u8 unk_0D;
        } as_u8_0D;
    } unk_0C;
    u16 unk_0E;
    union {
        s16 as_s16_10;
        u16 as_u16_10;
    } unk_10;
    s16 unk_12;
    union {
        s16 as_s16_14;
        u8 as_u8_14;
        struct {
            u8 pad_14[0x1];
            u8 unk_15;
        } as_u8_15;
    } unk_14;
    u16 unk_16;
    union {
        s16 as_s16_18;
        u16 as_u16_18;
    } unk_18;
    s16 unk_1A;
    union {
        s16 as_s16_1C;
        struct {
            u8 pad_1C[0x1];
            u8 unk_1D;
        } as_u8_1D;
    } unk_1C;
    u8 pad_1E[0x2];
    union {
        s16 as_s16_20;
        u16 as_u16_20;
    } unk_20;
    s16 unk_22;
    union {
        s16 as_s16_24;
        u8 as_u8_24;
        struct {
            u8 pad_24[0x1];
            u8 unk_25;
        } as_u8_25;
    } unk_24;
} S_func_81904990_7;

typedef struct S_func_81904990_8 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_func_81904990_8;

typedef struct S_func_81904990_9 {
    u8 pad_00[0xA0];
    s32 unk_A0;
    u8 pad_A4[0x20];
    s16 unk_C4;
    s16 unk_C6;
    s16 unk_C8;
} S_func_81904990_9;

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
    S_func_81904990_5 *render_state;
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
    S_func_81904990_7 *packet;
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
    S_func_81904990_2 *frame;
    S_func_81904990_3 *frame_header;
    S_func_81904990_6 *setup_arg;
    void *row_heights;
    S_func_81904990_8 *view_matrix;
    s32 quad_words;
    s32 tail_value;
    s32 tail_uv;
    register s32 addr_mask ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 length_mask;
    register S_func_81904990_4 *scratch ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *sprite_base ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */

    setup_arg = screen_pos;
    sprite_base = sprite;
    frame = ((S_func_81904990_1 *)((u8 *)sprite_base - 0x18))->unk_04;
    {
        void **state_ptr;
        state_ptr = (void **)D_80083160;
        ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        callback_arg = ((S_func_81904990_1 *)((u8 *)sprite_base - 0x18))->unk_00;
        render_state = *state_ptr;
    }
    frame_header = frame->unk_08;
    scratch = (S_func_81904990_4 *)0x1F800000;
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    scratch->unk_EC = NULL;
    scratch->unk_8C = 0;
    scratch->unk_84 = 0;
    scratch->unk_7C = 0;
    scratch->unk_74 = 0;
    packet = (S_func_81904990_7 *)render_state->unk_8D0;
    scratch->unk_20 = ordering_table;
    scratch->unk_C0 = NULL;
    scratch->unk_B8 = (s16) (setup_arg->unk_00 - 0xA0);
    scratch->unk_BA = (u16) (setup_arg->unk_02 - 0x78);
    saved_draw_mode = (u16) draw_mode;
    mode_bits = draw_mode << 0x10;
    matrix_arg = 0;
    if (mode_bits != 0) {
        func_80067EF4(packet, 0, 0, mode_bits);
        {
            s32 link_mask = 0xFFFFFF;
            matrix_arg = 0xFF000000;
            packet->unk_00.as_s32_00 = (packet->unk_00.as_s32_00 & 0xFF000000) | (*scratch->unk_20 & link_mask);
        }
        mode_link = scratch->unk_20;
        setup_arg = (void *) ((s32) packet & 0xFFFFFF);
        packet = (S_func_81904990_7 *)((u8 *)packet + 12);
        *mode_link = (*mode_link & 0xFF000000) | (s32) setup_arg;
    }
    quad_words = 9;
    ASM_KEEP_NV(quad_words);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    addr_mask = 0xFFFFFF;
    length_mask = 0xFF000000;
    ASM_KEEP_NV(length_mask);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    view_matrix = (S_func_81904990_8 *)D_8006CD10;
    view_matrix->unk_1C = (s32) ((S_func_81904990_9 *)D_80083160)->unk_A0;
    func_800649A0((s32) setup_arg, matrix_arg);
    {
        s32 view_x;
        s32 view_y;
        s32 view_z;
        view_x = ((S_func_81904990_9 *)D_80083160)->unk_C4;
        view_y = ((S_func_81904990_9 *)D_80083160)->unk_C6;
        view_z = ((S_func_81904990_9 *)D_80083160)->unk_C8;
        scratch->unk_30 = view_x;
        scratch->unk_34 = view_y;
        scratch->unk_38 = view_z;
    }
    scratch->unk_100 = (u16) frame->unk_16;
    scratch->unk_104 = (s16) (frame->unk_1A - (u16) scratch->unk_34);
    angle_or_pivot = (((u16) scratch->unk_38 + 0x100) & 0x1FF);
    angle_bias = frame->unk_18 - 0x100;
    scratch->unk_102 = angle_or_pivot + angle_bias;
    angle_or_pivot = frame->unk_20;
    scratch->unk_E4 = (s32) angle_or_pivot;
    scratch->unk_108 = angle_or_pivot;
    pivot_y = frame->unk_22;
    scratch->unk_E8 = (s32) pivot_y;
    scratch->unk_10A = pivot_y;
    func_80065820((void *)0x1F800100, (void *)0x1F8000D0);
    {
        s32 scale_x;
        s32 scale_y;
        scale_x = frame->unk_1C;
        scratch->unk_30 = scale_x;
        scale_y = frame->unk_1E;
        scratch->unk_38 = (s32)0x1000;
        scratch->unk_34 = scale_y;
    }
    func_80064BC0((void *)0x1F8000D0, (void *)0x1F800030);
    func_80064840(view_matrix, (void *)0x1F8000D0, (void *)0x1F800050);
    func_80064D80((void *)0x1F800050);
    func_80064CF0((void *)0x1F800050);
    frame_data = (u8 *)frame_header + 8;
    ASM_KEEP_NV(frame_data);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    scratch->unk_24 = (u16) frame->unk_14;
    if (!(frame_header->unk_00 & 0x20)) {
        scratch->unk_08 = (s32) ((S_func_81904990_3 *)((u8 *)frame_data - 0x8))->unk_08.as_u8_08;
        scratch->unk_0C = (s32) ((S_func_81904990_3 *)((u8 *)frame_data - 0x8))->unk_08.as_u8_09.unk_09;
        scratch->unk_10.as_s32_10 = (s32) ((S_func_81904990_3 *)((u8 *)frame_data - 0x8))->unk_08.as_u8_0A.unk_0A;
        scratch->unk_14.as_s32_14 = (s32) ((S_func_81904990_3 *)((u8 *)frame_data - 0x8))->unk_08.as_u8_0B.unk_0B;
        if ((frame_header->unk_00 ^ scratch->unk_24) & 1) {
            origin_byte = ((volatile S_func_81904990_3 *)(frame_data - 8))->unk_02;
            tail_value = (0 - (s32)(s8) origin_byte) - scratch->unk_108;
            scratch->unk_80 = tail_value;
            scratch->unk_70 = tail_value;
            tail_value = tail_value - scratch->unk_10.as_u16_10;
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_8002443C((u16) scratch->unk_10.as_s32_10);
            return;
        }
        origin_byte = ((volatile S_func_81904990_3 *)(frame_data - 8))->unk_02;
        left_x = (s32)(s8) origin_byte - scratch->unk_108;
        scratch->unk_80 = left_x;
        scratch->unk_70 = left_x;
        right_x = left_x + (u16) scratch->unk_10.as_s32_10;
        scratch->unk_88 = right_x;
        scratch->unk_78 = right_x;
        if ((frame_header->unk_00 ^ scratch->unk_24) & 2) {
            origin_byte = ((volatile S_func_81904990_3 *)(frame_data - 8))->unk_03;
            tail_value = (0 - (s32)(s8) origin_byte) - scratch->unk_10A;
            scratch->unk_7A = tail_value;
            scratch->unk_72 = tail_value;
            tail_value = tail_value - scratch->unk_14.as_u16_14;
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_800244B0((u16) scratch->unk_14.as_s32_14);
            return;
        }
        origin_byte = ((volatile S_func_81904990_3 *)(frame_data - 8))->unk_03;
        top_y = (s32)(s8) origin_byte - scratch->unk_10A;
        scratch->unk_7A = top_y;
        scratch->unk_72 = top_y;
        bottom_y = top_y + (u16) scratch->unk_14.as_s32_14;
        scratch->unk_8A = bottom_y;
        scratch->unk_82 = bottom_y;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800654B0((u8 *)scratch + 0x70, (u8 *)scratch + 0x78, (u8 *)scratch + 0x80, (u8 *)scratch + 0x88, (u8 *)scratch + 0xF0, (u8 *)scratch + 0xF4, (u8 *)scratch + 0xF8, (u8 *)scratch + 0xFC, (u8 *)scratch + 0x90, (u8 *)scratch + 0x94);
        packet->unk_08.as_s16_08 = (s16) (scratch->unk_F0 + scratch->unk_B8);
        packet->unk_0A = (s16) (scratch->unk_F2 + scratch->unk_BA);
        packet->unk_10.as_s16_10 = (s16) (scratch->unk_F4 + scratch->unk_B8);
        packet->unk_12 = (s16) (scratch->unk_F6 + scratch->unk_BA);
        packet->unk_18.as_s16_18 = (s16) (scratch->unk_F8 + scratch->unk_B8);
        packet->unk_1A = (s16) (scratch->unk_FA + scratch->unk_BA);
        packet->unk_20.as_s16_20 = (s16) (scratch->unk_FC + scratch->unk_B8);
        packet->unk_22 = (s16) (scratch->unk_FE + scratch->unk_BA);
        packet->unk_00.as_s8_03.unk_03 = quad_words;
        ASM_USE2_NV(quad_words, quad_words);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        {
            s32 width = scratch->unk_10.as_s32_10;
            s32 u_start = scratch->unk_08;
            width = width - 1;
            {
                s32 last_u = width + u_start;
                u_end = last_u;
            }
        }
        scratch->unk_10.as_s32_10 = u_end;
        if (u_end & 0x100) {
            scratch->unk_10.as_s32_10 = u_end - 1;
        }
        {
            s32 height = scratch->unk_14.as_s32_14;
            s32 v_start = scratch->unk_0C;
            height = height - 1;
            {
                s32 last_v = height + v_start;
                v_end = last_v;
            }
        }
        scratch->unk_14.as_s32_14 = v_end;
        if (v_end & 0x100) {
            scratch->unk_14.as_s32_14 = v_end - 1;
        }
        scratch->unk_14.as_s32_14 <<= 8;
        scratch->unk_0C <<= 8;
        clut_override = frame->unk_12;
        if (clut_override != 0) {
            if (scratch->unk_24 & 0x100) {
                packet->unk_0E = clut_override;
                func_80024640();
                return;
            }
            tail_value = clut_override + ((S_func_81904990_3 *)((u8 *)frame_data - 0x8))->unk_06;
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024638();
            return;
        }
        packet->unk_0E = (u16) ((S_func_81904990_3 *)((u8 *)frame_data - 0x8))->unk_06;
        packet->unk_0C.as_s16_0C = (s16) ((u16) scratch->unk_0C + (u16) scratch->unk_08);
        packet->unk_14.as_s16_14 = (s16) ((u16) scratch->unk_0C + (u16) scratch->unk_10.as_s32_10);
        tpage_offset = frame->unk_10;
        if (tpage_offset != 0) {
            base_tpage = ((S_func_81904990_3 *)((u8 *)frame_data - 0x8))->unk_04 & 0xFF9F;
            tail_value = tpage_offset + base_tpage;
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024690();
            return;
        }
        packet->unk_16 = (u16) ((S_func_81904990_3 *)((u8 *)frame_data - 0x8))->unk_04;
        packet->unk_1C.as_s16_1C = (s16) ((u16) scratch->unk_14.as_s32_14 | (u16) scratch->unk_08);
        {
            register s32 packed_v ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            packed_v = (u16) scratch->unk_14.as_s32_14;
            packet->unk_24.as_s16_24 = (s16) (packed_v | (u16) scratch->unk_10.as_s32_10);
        }
        if (packet->unk_20.as_s16_20 < packet->unk_08.as_s16_08) {
            right_u = (u8) packet->unk_24.as_s16_24;
            packet->unk_24.as_u8_24 = (u8) (right_u + 0xFF);
            packet->unk_14.as_u8_14 = right_u;
        }
        if (packet->unk_0A > packet->unk_22) {
            bottom_v = packet->unk_24.as_u8_25.unk_25;
            packet->unk_24.as_u8_25.unk_25 = (u8) (bottom_v + 0xFF);
            packet->unk_1C.as_u8_1D.unk_1D = bottom_v;
        }
        prim_code = ((S_func_81904990_3 *)((u8 *)frame_data - 0x8))->unk_01;
        frame->unk_0C.as_u8_0F.unk_0F = prim_code;
        sprite_flags = scratch->unk_24;
        if (sprite_flags & 8) {
            blend_code = sprite_flags & 4;
            if (blend_code != 0) {
                blend_code = prim_code | 2;
            } else {
                blend_code = prim_code & 0xFD;
            }
            frame->unk_0C.as_u8_0F.unk_0F = blend_code;
        }
        first_quad = (u8 *)packet;
        packet->unk_04 = (s32) frame->unk_0C.as_s32_0C;
        ((S_func_81904990_1 *)((u8 *)sprite_base - 0x18))->unk_7A = (u16) packet->unk_0A;
        quad_end = first_quad + 32;
        strip_bottom = (u16) packet->unk_0A + ((S_func_81904990_1 *)((u8 *)sprite_base - 0x18))->unk_7C;
        packet->unk_22 = strip_bottom;
        packet->unk_1A = strip_bottom;
        first_addr = (s32) packet & addr_mask;
        packet->unk_00.as_s32_00 = (packet->unk_00.as_s32_00 & length_mask) | (*scratch->unk_20 & addr_mask);
        first_link = scratch->unk_20;
        packet = (S_func_81904990_7 *)((u8 *)packet + 40);
        *first_link = (*first_link & length_mask) | first_addr;
        packet->unk_00.as_s8_03.unk_03 = quad_words;

        *(Blk40 *)packet = *(Blk40 *)first_quad;
        row_index = 1;
        wrapped_v_offset = -0x30;
        row_heights = sprite_base + 2;
        second_addr = (s32) packet & addr_mask;
        packet->unk_08.as_u16_08 = (u16) (packet->unk_08.as_u16_08 + 0x40);
        packet->unk_10.as_u16_10 = (u16) (packet->unk_10.as_u16_10 + 0x40);
        packet->unk_18.as_u16_18 = (u16) (packet->unk_18.as_u16_18 + 0x40);
        packet->unk_20.as_u16_20 = (u16) (packet->unk_20.as_u16_20 + 0x40);
        packet->unk_00.as_s32_00 = (packet->unk_00.as_s32_00 & length_mask) | (*scratch->unk_20 & addr_mask);
        second_link = scratch->unk_20;
        packet = (S_func_81904990_7 *)((u8 *)packet + 40);
        quad_end = (u8 *)packet + 32;
        *second_link = (*second_link & length_mask) | second_addr;
    next_row:
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_00.as_s8_03.unk_03 = quad_words;
        *(Blk40 *)packet = *(Blk40 *)first_quad;
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_0A = (s16) (((S_func_81904990_1 *)((u8 *)sprite_base - 0x18))->unk_7A + ((S_func_81904990_1 *)((u8 *)row_heights - 0x18))->unk_7A);
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_12 = (s16) (((S_func_81904990_1 *)((u8 *)sprite_base - 0x18))->unk_7A + ((S_func_81904990_1 *)((u8 *)row_heights - 0x18))->unk_7A);
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_1A = (s16) (((S_func_81904990_1 *)((u8 *)sprite_base - 0x18))->unk_7A + ((S_func_81904990_1 *)((u8 *)row_heights - 0x18))->unk_7C);
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_22 = (s16) (((S_func_81904990_1 *)((u8 *)sprite_base - 0x18))->unk_7A + ((S_func_81904990_1 *)((u8 *)row_heights - 0x18))->unk_7C);
        row_v_offset = row_index * 0x10;
        if (row_index < 4) {
            tail_value = ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_0C.as_u8_0D.unk_0D;
            tail_uv = ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_14.as_u8_15.unk_15;
            tail_value = tail_value + row_v_offset;
            ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_0C.as_u8_0D.unk_0D = (u8) tail_value;
            tail_value = ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_1C.as_u8_1D.unk_1D;
            tail_uv = tail_uv + row_v_offset;
            ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_14.as_u8_15.unk_15 = (u8) tail_uv;
            tail_uv = ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_24.as_u8_25.unk_25;
            tail_value = tail_value + row_v_offset;
            tail_uv = tail_uv + row_v_offset;
            ASM_KEEP(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN(tail_uv);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024958();
            return;
        }
        tail_value = ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_0C.as_u8_0D.unk_0D;
        tail_uv = ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_14.as_u8_15.unk_15;
        tail_value = tail_value + wrapped_v_offset;
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_0C.as_u8_0D.unk_0D = (u8) tail_value;
        tail_value = ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_1C.as_u8_1D.unk_1D;
        tail_uv = tail_uv + wrapped_v_offset;
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_14.as_u8_15.unk_15 = (u8) tail_uv;
        tail_uv = ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_24.as_u8_25.unk_25;
        tail_value = tail_value + wrapped_v_offset;
        tail_uv = tail_uv + wrapped_v_offset;
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_1C.as_u8_1D.unk_1D = (u8) tail_value;
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_24.as_u8_25.unk_25 = (u8) tail_uv;
        quad_end += 40;
        row_quad = (u8 *)packet;
        ASM_KEEP(row_quad);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        left_row_addr = (s32) packet & addr_mask;
        {
            register s32 packet_tag ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
            packet_tag = packet->unk_00.as_s32_00;
            packet->unk_00.as_s32_00 = (packet_tag & length_mask) | (*scratch->unk_20 & addr_mask);
        }
        left_row_link = scratch->unk_20;
        packet = (S_func_81904990_7 *)((u8 *)packet + 40);
        *left_row_link = (*left_row_link & length_mask) | left_row_addr;
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_00.as_s8_03.unk_03 = quad_words;
        *(Blk40 *)packet = *(Blk40 *)row_quad;
        wrapped_v_offset += 0x10;
        row_heights = (u8 *)row_heights + 2;
        row_index += 1;
        right_row_addr = (s32) packet & addr_mask;
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_08.as_u16_08 = (u16) (((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_08.as_u16_08 + 0x40);
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_10.as_u16_10 = (u16) (((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_10.as_u16_10 + 0x40);
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_18.as_u16_18 = (u16) (((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_18.as_u16_18 + 0x40);
        ((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_20.as_u16_20 = (u16) (((S_func_81904990_7 *)((u8 *)quad_end - 0x20))->unk_20.as_u16_20 + 0x40);
        {
            register s32 packet_tag ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
            packet_tag = packet->unk_00.as_s32_00;
            packet->unk_00.as_s32_00 = (packet_tag & length_mask) | (*scratch->unk_20 & addr_mask);
        }
        right_row_link = scratch->unk_20;
        quad_end += 40;
        *right_row_link = (*right_row_link & length_mask) | right_row_addr;
        packet = (S_func_81904990_7 *)((u8 *)packet + 40);
        if (row_index < 8) {
            goto next_row;
        }
        func_80024AA0();
    }
    draw_callback = ((S_func_81904990_3 *)((u8 *)frame_data - 0x8))->unk_08.as_FnPtr_08;
    if (draw_callback != NULL) {
        callback_sprite = sprite_base;
        callback_frame = frame;
        callback_param = callback_arg;
        callback_data = frame_header;
        packet = (S_func_81904990_7 *)draw_callback(callback_sprite, callback_param, callback_frame, callback_data, (u8 *)packet);
    }
    if ((s8) frame_header->unk_00 >= 0) {
        frame_data += 12;
        frame_header = (S_func_81904990_3 *)((u8 *)frame_header + 12);
        ASM_KEEP(frame_data);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(frame_header);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        func_80024390();
        return;
    }
    restore_mode = saved_draw_mode << 0x10;

    restore_packet = (u8 *)packet;
    if (restore_mode != 0) {
        func_80067EF4(restore_packet, 0, 1);
        packet->unk_00.as_s32_00 = (packet->unk_00.as_s32_00 & 0xFF000000) | (*scratch->unk_20 & 0xFFFFFF);
        restore_link = scratch->unk_20;
        restore_packet = (u8 *) ((s32) packet & 0xFFFFFF);
        packet = (S_func_81904990_7 *)((u8 *)packet + 12);
        *restore_link = (*restore_link & 0xFF000000) | (s32) restore_packet;
    }
    func_80064A40((s32) restore_packet);
    {
        u8 *state_slot = D_80083160;
        u64 state_bits = *(u64 *)state_slot;
        S_func_81904990_5 *final_state = (S_func_81904990_5 *)(u32)state_bits;
        final_state->unk_8D0 = (u8 *)packet;
    }
}
