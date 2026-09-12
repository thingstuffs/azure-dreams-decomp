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

typedef struct S_80DB9000_1 {
    u8 pad_00[0x4E];
    union {
        s16 s16;
        u16 u16;
    } unk_4E;
    u16 unk_50;
} S_80DB9000_1;

typedef struct S_80DB9000_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80DB9000_2;

typedef struct S_80DB9000_3 {
    u8 pad_00[0x8];
    void * unk_08;
    union {
        s32 s32;
        struct {
            u8 pad_0C[0x3];
            u8 unk_0F;
        } u8;
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
} S_80DB9000_3;

typedef struct S_80DB9000_4 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x2];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x8];
    u32 unk_24;
    u16 unk_28;
    u8 pad_2A[0xA];
    u32 unk_34;
    union {
        u16 u16;
        u32 u32;
    } unk_38;
    union {
        u16 u16;
        u32 u32;
    } unk_3C;
    u8 pad_40[0x48];
    u32 unk_88;
    u32 unk_8C;
    u32 unk_90;
    u16 unk_94;
    u16 unk_96;
    u16 unk_98;
    u16 unk_9A;
    u16 unk_9C;
    u16 unk_9E;
    u16 unk_A0;
    u16 unk_A2;
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x2];
    u16 unk_AC;
    u16 unk_AE;
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x2A];
    u16 unk_F8;
    u16 unk_FA;
    u8 pad_FC[0x4];
    u32 unk_100;
} S_80DB9000_4;

typedef struct S_80DB9000_5 {
    void * unk_00;
    u8 pad_04[0xB4];
    u16 unk_B8;
    u8 pad_BA[0xA];
    s16 unk_C4;
    s16 unk_C6;
    s16 unk_C8;
} S_80DB9000_5;

typedef struct S_80DB9000_6 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80DB9000_6;

typedef struct S_80DB9000_7 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x2];
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x14];
    s32 unk_1C;
} S_80DB9000_7;

typedef struct S_80DB9000_8 {
    union {
        struct {
            u8 unk_00;
            u8 unk_01;
            u8 unk_02;
            u8 unk_03;
        } u8;
        void * void_ptr;
    } unk_00;
} S_80DB9000_8;

typedef struct S_80DB9000_9 {
    union {
        s32 s32;
        struct {
            u8 pad_00[0x3];
            s8 unk_03;
        } s8;
    } unk_00;
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    union {
        s16 s16;
        u8 u8;
    } unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    union {
        s16 s16;
        struct {
            u8 pad_1C[0x1];
            u8 unk_1D;
        } u8;
    } unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
    s16 unk_22;
    union {
        s16 s16;
        struct {
            u8 unk_24;
            u8 unk_25;
        } u8;
    } unk_24;
} S_80DB9000_9;

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
void BODY_NAME(void *size_arg, void *position_arg, void *sprite_arg, s32 depth_bias_arg) {
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
    s32 blend_code;
    void *(*draw_callback)(void *, void *, void *, void *, void *);
    S_80DB9000_8 *entry_uv;
    S_80DB9000_7 *render_data;
    register S_80DB9000_5 *render_state ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u32 address_mask;
    register S_80DB9000_6 *render_buffer ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 load_dependency;
    S_80DB9000_9 *packet;
    S_80DB9000_1 *sprite_size = size_arg;
    register S_80DB9000_2 *position = position_arg;
    register S_80DB9000_3 *sprite ASM_REG("$20") = sprite_arg;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 depth_bias = depth_bias_arg;
    register u8 *work_src ASM_REG("$4") = (u8 *)0x1F800004;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *work_dst ASM_REG("$5") = (u8 *)0x1F8000F8;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register u8 *work_aux ASM_REG("$6") = (u8 *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register u8 *state_page ASM_REG("$8") = (u8 *)0x80080000;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register S_80DB9000_4 *scratch_page;
    register u8 *projection_flags;
    ASM_KEEP_MEMDEP_NV(position, load_dependency, ((S_80DB9000_5 *)&D_80083160)->unk_00);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    scratch_page = (S_80DB9000_4 *)0x1F800000;
    ASM_KEEP_NV(work_aux);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(sprite_size);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(sprite);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(depth_bias);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    work_aux = (u8 *)((u32)work_aux | 0xD0);
    render_buffer = ((S_80DB9000_5 *)&D_80083160)->unk_00;
    scratch_page->unk_90 = 0;
    scratch_page->unk_CC = 0;
    scratch_page->unk_C4 = 0;
    scratch_page->unk_BC = 0;
    scratch_page->unk_B4 = 0;
    scratch_page->unk_24 = (u8 *)render_buffer + 0xB0;
    scratch_page->unk_04 = position->unk_02;
    projection_flags = (u8 *)scratch_page;
    ASM_KEEP_MEMDEP_NV(scratch_page, load_dependency, ((S_80DB9000_5 *)&D_80083160)->unk_00);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    ASM_SET(state_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(projection_flags);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    scratch_page->unk_06 = position->unk_06;
    scratch_page->unk_08 = position->unk_0A;
    projection_flags = (u8 *)((u32)projection_flags | 0xD4);
    packet = render_buffer->unk_8D0;
    render_state = (S_80DB9000_5 *)(state_page + 0x3160);
    scratch_page->unk_100 = func_80065420(work_src, work_dst, work_aux, projection_flags);
    sprite->unk_14 = (u16)(sprite->unk_14 | 0x8000);
    depth = scratch_page->unk_100;
    depth_scaled = depth * 4;
    depth -= 0xA;
    ot_index = depth - depth_bias;
    render_data = (S_80DB9000_7 *)&D_8006CD30;
    render_data->unk_1C = (s32)depth_scaled;
    scratch_page->unk_100 = ot_index;
    if (ot_index < 0x1D6U) {
        address_mask = 0x00FF0000;
        func_800649A0();
        work_src = (u8 *)scratch_page;
        ASM_KEEP_NV(work_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_src = (u8 *)((u32)work_src | 0xA4);
        screen_offset = scratch_page->unk_F8;
        work_dst = (u8 *)scratch_page;
        screen_offset -= 0xA0;
        scratch_page->unk_F8 = screen_offset;
        screen_offset = scratch_page->unk_FA;
        view_rot_x = render_state->unk_C4;
        view_rot_y = render_state->unk_C6;
        view_rot_z = render_state->unk_C8;
        screen_offset -= 0x78;
        scratch_page->unk_FA = screen_offset;
        scratch_page->unk_34 = view_rot_x;
        scratch_page->unk_38.u32 = view_rot_y;
        scratch_page->unk_3C.u32 = view_rot_z;
        ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        field_value = sprite->unk_16;
        view_y_angle = scratch_page->unk_38.u16;
        work_dst = (u8 *)((u32)work_dst | 0x74);
        ASM_KEEP_NV(work_dst);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        scratch_page->unk_A4 = field_value;
        coord_offset = sprite->unk_1A;
        coord_value = render_state->unk_B8;
        coord_offset -= view_y_angle;
        coord_value += coord_offset;
        scratch_page->unk_A8 = coord_value;
        coord_offset = sprite->unk_18;
        coord_value = scratch_page->unk_3C.u16;
        coord_offset -= 0x100;
        coord_value = (coord_value + 0x100) & 0x1FF;
        coord_offset += coord_value;
        scratch_page->unk_A6 = coord_offset;
        field_value = sprite->unk_20;
        scratch_page->unk_88 = field_value;
        scratch_page->unk_AC = field_value;
        coord_value = sprite->unk_22;
        ASM_KEEP_DEP_NV(address_mask, coord_value);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        address_mask |= 0xFFFF;
        ASM_KEEP_NV(address_mask);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        scratch_page->unk_8C = coord_value;
        scratch_page->unk_AE = coord_value;
        func_80065820(work_src, work_dst, view_y_angle, view_rot_z);
        work_src = (u8 *)scratch_page;
        ASM_KEEP_NV(work_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_src = (u8 *)((u32)work_src | 0x74);
        work_dst = (u8 *)scratch_page;
        ASM_KEEP_NV(work_dst);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_dst = (u8 *)((u32)work_dst | 0x34);
        scratch_page->unk_34 = sprite->unk_1C;
        scale_y = sprite->unk_1E;
        scratch_page->unk_3C.u32 = 0x1000;
        scratch_page->unk_38.u32 = scale_y;
        func_80064BC0(work_src, work_dst);
        work_src = (u8 *)render_data;
        ASM_KEEP_NV(work_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_dst = (u8 *)scratch_page;
        ASM_KEEP_NV(work_dst);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_dst = (u8 *)((u32)work_dst | 0x74);
        work_aux = (u8 *)scratch_page;
        ASM_KEEP_NV(work_aux);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        work_aux = (u8 *)((u32)work_aux | 0x54);
        func_80064840(work_src, work_dst, work_aux);
        work_src = (u8 *)scratch_page;
        ASM_KEEP_NV(work_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_src = (u8 *)((u32)work_src | 0x54);
        func_80064D80(work_src);
        work_src = (u8 *)scratch_page;
        ASM_KEEP_NV(work_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work_src = (u8 *)((u32)work_src | 0x54);
        func_80064CF0(work_src);
        render_data = sprite->unk_08;
        entry_uv = (S_80DB9000_8 *)((u8 *)render_data + 8);
        scratch_page->unk_28 = sprite->unk_14;
next_entry:
        if (!(render_data->unk_00 & 0x20)) {
            scratch_page->unk_0C = entry_uv->unk_00.u8.unk_00;
            scratch_page->unk_10 = entry_uv->unk_00.u8.unk_01;
            scratch_page->unk_14 = entry_uv->unk_00.u8.unk_02;
            scratch_page->unk_18 = entry_uv->unk_00.u8.unk_03;
            if ((render_data->unk_00 ^ scratch_page->unk_28) & 1) {
                flipped_left_x = (0 - ((s32)(0 - sprite_size->unk_4E.s16) / 2)) - scratch_page->unk_AC;
                scratch_page->unk_C0 = flipped_left_x;
                scratch_page->unk_B0 = flipped_left_x;
                right_x = flipped_left_x - sprite_size->unk_4E.u16;
            } else {
                neg_width = 0 - sprite_size->unk_4E.s16;
                left_x = ((s32)(neg_width + (neg_width >> 0x1F)) >> 1) - scratch_page->unk_AC;
                scratch_page->unk_C0 = left_x;
                scratch_page->unk_B0 = left_x;
                coord_offset = (u16)sprite_size->unk_4E.s16;
                right_x = left_x + coord_offset;
            }
            scratch_page->unk_C8 = right_x;
            scratch_page->unk_B8 = right_x;
            if ((render_data->unk_00 ^ scratch_page->unk_28) & 2) {
                flipped_top_y = sprite_size->unk_50 - scratch_page->unk_AE;
                scratch_page->unk_BA = flipped_top_y;
                scratch_page->unk_B2 = flipped_top_y;
                bottom_y = flipped_top_y - sprite_size->unk_50;
            } else {
                top_y = (0 - sprite_size->unk_50) - scratch_page->unk_AE;
                scratch_page->unk_BA = top_y;
                scratch_page->unk_B2 = top_y;
                coord_offset = sprite_size->unk_50;
                bottom_y = top_y + coord_offset;
            }
            scratch_page->unk_CA = bottom_y;
            scratch_page->unk_C2 = bottom_y;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            func_800654B0((u8 *)scratch_page + 0xB0, (u8 *)scratch_page + 0xB8, (u8 *)scratch_page + 0xC0, (u8 *)scratch_page + 0xC8, (u8 *)scratch_page + 0x94, (u8 *)scratch_page + 0x98, (u8 *)scratch_page + 0x9C, (u8 *)scratch_page + 0xA0, (u8 *)scratch_page + 0xD0, (u8 *)scratch_page + 0xD4);
            packet->unk_08 = scratch_page->unk_94 + scratch_page->unk_F8;
            packet->unk_0A = scratch_page->unk_96 + scratch_page->unk_FA;
            packet->unk_10 = scratch_page->unk_98 + scratch_page->unk_F8;
            packet->unk_12 = scratch_page->unk_9A + scratch_page->unk_FA;
            packet->unk_18 = scratch_page->unk_9C + scratch_page->unk_F8;
            packet->unk_1A = scratch_page->unk_9E + scratch_page->unk_FA;
            corner0_visible = 0;
            packet->unk_20 = scratch_page->unk_A0 + scratch_page->unk_F8;
            screen_y3 = scratch_page->unk_A2 + scratch_page->unk_FA;
            packet->unk_22 = screen_y3;
            if ((u32)((packet->unk_08 + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((packet->unk_0A + 0x20) & 0xFFFF);
                corner0_visible = y_bound < 0x121U;
            }
            corner1_visible = 0;
            if ((u32)((packet->unk_10 + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((packet->unk_12 + 0x20) & 0xFFFF);
                corner1_visible = y_bound < 0x121U;
            }
            corner2_visible = 0;
            first_two_visible = corner0_visible | corner1_visible;
            if ((u32)((packet->unk_18 + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((packet->unk_1A + 0x20) & 0xFFFF);
                corner2_visible = y_bound < 0x121U;
            }
            corner3_visible = 0;
            first_three_visible = first_two_visible | corner2_visible;
            if ((u32)((packet->unk_20 + 0x20) & 0xFFFF) < 0x181U) {
                u32 y_bound = (u32)((screen_y3 + 0x20) & 0xFFFF);
                corner3_visible = y_bound < 0x121U;
            }
            if ((first_three_visible | corner3_visible) != 0) {
                packet->unk_00.s8.unk_03 = 9;
                sprite->unk_14 = (u16)(sprite->unk_14 & 0x7FFF);
                {
                    u32 texel_count = scratch_page->unk_14;
                    uv_right = scratch_page->unk_0C;
                    texel_count -= 1;
                    uv_right = texel_count + uv_right;
                }
                scratch_page->unk_14 = uv_right;
                if (uv_right & 0x100) {
                    register u32 uv_adjusted ASM_REG("$2") = uv_right - 1;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    scratch_page->unk_14 = uv_adjusted;
                }
                {
                    u32 texel_count = scratch_page->unk_18;
                    uv_bottom = scratch_page->unk_10;
                    texel_count -= 1;
                    uv_bottom = texel_count + uv_bottom;
                }
                scratch_page->unk_18 = uv_bottom;
                if (uv_bottom & 0x100) {
                    register u32 uv_adjusted ASM_REG("$2") = uv_bottom - 1;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    scratch_page->unk_18 = uv_adjusted;
                }
                scratch_page->unk_18 <<= 8;
                scratch_page->unk_10 <<= 8;
                if (scratch_page->unk_28 & 0x100) {
                    packet->unk_0E = sprite->unk_12;
                } else {
                    packet->unk_0E = (s16)(sprite->unk_12 + ((S_80DB9000_7 *)((u8 *)entry_uv - 8))->unk_06);
                }
                packet->unk_0C = (s16)((u16)scratch_page->unk_10 + (u16)scratch_page->unk_0C);
                packet->unk_14.s16 = (s16)((u16)scratch_page->unk_10 + (u16)scratch_page->unk_14);
                if (sprite->unk_10 != 0) {
                    field_value = (((S_80DB9000_7 *)((u8 *)entry_uv - 8))->unk_04 & 0xFF9F) + sprite->unk_10;
                } else {
                    field_value = ((S_80DB9000_7 *)((u8 *)entry_uv - 8))->unk_04;
                }
                packet->unk_16 = field_value;
                packet->unk_1C.s16 = (s16)((u16)scratch_page->unk_18 | (u16)scratch_page->unk_0C);
                uv_right = (u16)scratch_page->unk_18;
                uv_right |= (u16)scratch_page->unk_14;
                packet->unk_24.s16 = uv_right;
                if ((s16)packet->unk_20 < (s16)packet->unk_08) {
                    right_u = packet->unk_24.u8.unk_24;
                    packet->unk_24.u8.unk_24 = (u8)(right_u + 0xFF);
                    packet->unk_14.u8 = right_u;
                }
                if ((s16)packet->unk_0A > packet->unk_22) {
                    bottom_v = packet->unk_24.u8.unk_25;
                    packet->unk_24.u8.unk_25 = (u8)(bottom_v + 0xFF);
                    packet->unk_1C.u8.unk_1D = bottom_v;
                }
                packet_code = ((S_80DB9000_7 *)((u8 *)entry_uv - 8))->unk_01;
                sprite->unk_0C.u8.unk_0F = packet_code;
                sprite_flags = scratch_page->unk_28;
                if (sprite_flags & 8) {
                    blend_code = sprite_flags & 4;
                    if (blend_code) {
                        blend_code = packet_code | 2;
                    } else {
                        blend_code = packet_code & 0xFD;
                    }
                    sprite->unk_0C.u8.unk_0F = blend_code;
                }
                packet->unk_04 = (s32)sprite->unk_0C.s32;
                packet_addr = (u32)packet & address_mask;
                packet->unk_00.s32 = (s32)((packet->unk_00.s32 & 0xFF000000) | (*((u32 *)((scratch_page->unk_100 * 4) + scratch_page->unk_24)) & address_mask));
                ot_entry = (s32 *)((scratch_page->unk_100 * 4) + scratch_page->unk_24);
                packet = (S_80DB9000_9 *)((u8 *)packet + 0x28);
                *ot_entry = (*ot_entry & 0xFF000000) | packet_addr;
            }
        } else {
            draw_callback = (void *(*)(void *, void *, void *, void *, void *))entry_uv->unk_00.void_ptr;
            if (draw_callback != NULL) {
                packet = draw_callback(sprite_size, position, sprite, render_data, packet);
            }
        }
        if ((s8)render_data->unk_00 >= 0) {
            entry_uv = (S_80DB9000_8 *)((u8 *)entry_uv + 0xC);
            render_data = (S_80DB9000_7 *)((u8 *)render_data + 0xC);
            goto next_entry;
        }
        func_80064A40();
    }
    ((S_80DB9000_6 *)render_state->unk_00)->unk_8D0 = packet;
}
