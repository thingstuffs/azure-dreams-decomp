#include "common.h"

typedef struct S_func_818BC9CC_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    union {
        s16 as_s16;
        u16 as_u16;
    } unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
    u8 unk_0E;
} S_func_818BC9CC_0;

typedef struct S_func_818BC9CC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_func_818BC9CC_1;

typedef struct S_func_818BC9CC_2 {
    u8 pad_00[0x18];
    void *unk_18;
    u8 pad_1C[0x48];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u8 pad_6A[0x2];
    u16 unk_6C;
    u16 unk_6E;
    u16 unk_70;
    u8 pad_72[0x2];
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u8 pad_7A[0x2];
    u16 unk_7C;
    u16 unk_7E;
    u16 unk_80;
    u8 pad_82[0x32];
    u32 unk_B4;
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u16 unk_E0;
    u16 unk_E2;
    u16 unk_E4;
    u16 unk_E6;
} S_func_818BC9CC_2;

typedef struct S_func_818BC9CC_3 {
    union {
        u32 as_u32;
        struct {
            u8 pad_00[3];
            u8 unk_03;
        } as_bytes;
    } unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x1];
    u16 unk_14;
    u16 unk_16;
    u8 unk_18;
    u8 unk_19;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x1];
    u16 unk_20;
    u16 unk_22;
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    u8 unk_28;
    u8 unk_29;
    u8 unk_2A;
    u8 pad_2B[0x1];
    u16 unk_2C;
    u16 unk_2E;
    u8 unk_30;
    u8 unk_31;
} S_func_818BC9CC_3;

typedef struct S_func_818BC9CC_4 {
    u32 unk_00;
} S_func_818BC9CC_4;

typedef struct S_func_818BC9CC_5 {
    u8 pad_00[0x8D0];
    void *unk_8D0;
} S_func_818BC9CC_5;

typedef struct S_func_818BC9CC_6 {
    void *unk_00;
    u8 pad_04[0xC4];
    s16 unk_C8;
} S_func_818BC9CC_6;

#define OT_ADDR(sc) ((u32 *)((((volatile S_func_818BC9CC_2 *)(sc))->unk_B4 << 2) + (u32)(sc)->unk_18))

extern void func_800244DC() __attribute__((noreturn));
extern void func_80024504() __attribute__((noreturn));
extern s32 func_80024514() __attribute__((noreturn));
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern u32 func_80065590(void *, void *, void *, void *, void *, void *,
                         void *, void *, void *, void *);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, void *);
extern u8 D_80083160[];

/* Draw four shaded textured quads around the given position. */
s32 func_818BC9CC(void *effect_data, void *position_data)
{
    S_func_818BC9CC_0 *effect = effect_data;
    S_func_818BC9CC_1 *position = position_data;
    S_func_818BC9CC_2 *scratch;
    S_func_818BC9CC_3 *packet;
    register S_func_818BC9CC_4 *draw_mode ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_func_818BC9CC_5 *render_ctx;
    S_func_818BC9CC_6 *render_state;
    u32 tag_mask;
    u32 window_tag_mask;
    s32 page_depth;
    register s32 page_blend ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 page_x;
    u32 x_extent;
    register u32 y_extent ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u32 depth;
    register u32 addr_mask ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 quad_index;
    u32 far_z;
    u32 far_y;
    s32 angle;
    u16 texture_v;
    u16 coord;
    u8 intensity;
    volatile s16 tile_window[4];
    volatile s16 full_window[4];

    render_state = (S_func_818BC9CC_6 *)D_80083160;
    scratch = (S_func_818BC9CC_2 *)0x1F800000;
    angle = render_state->unk_C8;
    ASM_USE(effect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(angle);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(position);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    scratch->unk_18 = (u8 *)((S_func_818BC9CC_6 *)D_80083160)->unk_00 + 0xB0;
    x_extent = (u32)((func_80064584(angle) >> 4) * effect->unk_08.as_s16) >> 8;
    y_extent = (u32)((func_800644B8(angle) >> 4) * effect->unk_08.as_s16) >> 8;
    texture_v = (effect->unk_04 % 4) << 3;

    quad_index = 0;
    addr_mask = 0x00FFFFFF;
    do {
        render_ctx = render_state->unk_00;
        packet = render_ctx->unk_8D0;
        render_ctx->unk_8D0 = (u8 *)packet + 0x34;

        packet->unk_00.as_bytes.unk_03 = 0x0C;
        packet->unk_07 = 0x3E;
        packet->unk_1A = func_80066460(0, 1, 0x280, 0x100);
        packet->unk_0E = effect->unk_0C;
        packet->unk_0C = 0;
        packet->unk_0D = (u8)texture_v;
        packet->unk_18 = 0x3F;
        packet->unk_19 = (u8)texture_v;
        packet->unk_24 = 0x3F;
        packet->unk_25 = texture_v + 0x3F;
        packet->unk_31 = texture_v + 0x3F;
        packet->unk_30 = 0;
        packet->unk_04 = effect->unk_0E;
        packet->unk_05 = effect->unk_0E;
        intensity = effect->unk_0E;
        packet->unk_10 = 0;
        packet->unk_11 = 0;
        packet->unk_12 = 0;
        packet->unk_1C = 0;
        packet->unk_1D = 0;
        packet->unk_1E = 0;
        packet->unk_28 = 0;
        packet->unk_29 = 0;
        packet->unk_2A = 0;
        packet->unk_06 = intensity;

        if (quad_index == 1) {
            goto L_case1;
        }
        if (quad_index < 2) {
            if (quad_index == 0) {
                goto L_case0;
            }
            {
                void *vertex_arg0;
                register void *vertex_arg1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                void *vertex0;
                void *vertex1;

                vertex0 = (u8 *)scratch + 0x64;
                vertex1 = (u8 *)scratch + 0x6C;
                ASM_KEEP_NV(vertex0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                vertex_arg0 = vertex0;
                vertex_arg1 = vertex1;
                ASM_TAILSLOT_PIN(vertex_arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                func_80024514(vertex_arg0, vertex_arg1);
            }
        } else {
            if (quad_index == 2) {
                goto L_case2;
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            if (quad_index == 3) {
                goto L_case3;
            }
            {
                void *vertex_arg0;
                register void *vertex_arg1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                void *vertex0;
                void *vertex1;

                vertex0 = (u8 *)scratch + 0x64;
                vertex1 = (u8 *)scratch + 0x6C;
                ASM_KEEP_NV(vertex0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                vertex_arg0 = vertex0;
                vertex_arg1 = vertex1;
                ASM_TAILSLOT_PIN(vertex_arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                func_80024514(vertex_arg0, vertex_arg1);
            }
        }
    L_case0:
        coord = position->unk_02;
        scratch->unk_74 = coord;
        scratch->unk_64 = coord;
        coord = position->unk_02 + x_extent;
        scratch->unk_7C = coord;
        scratch->unk_6C = coord;
        coord = position->unk_06;
        scratch->unk_76 = coord;
        scratch->unk_66 = coord;
        coord = position->unk_06 - y_extent;
        scratch->unk_7E = coord;
        scratch->unk_6E = coord;
        coord = position->unk_0A;
        scratch->unk_70 = coord;
        scratch->unk_68 = coord;
        far_z = position->unk_0A;
        far_z = far_z + effect->unk_08.as_u16;
        ASM_TAILSLOT_PIN_TIED(far_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80024504();
    L_case1:
        coord = position->unk_02;
        scratch->unk_74 = coord;
        scratch->unk_64 = coord;
        coord = position->unk_02 - x_extent;
        scratch->unk_7C = coord;
        scratch->unk_6C = coord;
        coord = position->unk_06;
        scratch->unk_76 = coord;
        scratch->unk_66 = coord;
        coord = position->unk_06 + y_extent;
        scratch->unk_7E = coord;
        scratch->unk_6E = coord;
        coord = position->unk_0A;
        scratch->unk_70 = coord;
        scratch->unk_68 = coord;
        far_z = position->unk_0A;
        far_z = far_z + effect->unk_08.as_u16;
        ASM_TAILSLOT_PIN_TIED(far_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80024504();
    L_case2:
        coord = position->unk_02;
        scratch->unk_74 = coord;
        scratch->unk_64 = coord;
        coord = position->unk_02 + x_extent;
        scratch->unk_7C = coord;
        scratch->unk_6C = coord;
        coord = position->unk_06;
        scratch->unk_76 = coord;
        scratch->unk_66 = coord;
        far_y = (u32)position->unk_06 - y_extent;
        ASM_TAILSLOT_PIN_TIED(far_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800244DC();
    L_case3:
        coord = position->unk_02;
        scratch->unk_74 = coord;
        scratch->unk_64 = coord;
        coord = position->unk_02 - x_extent;
        scratch->unk_7C = coord;
        scratch->unk_6C = coord;
        coord = position->unk_06;
        scratch->unk_76 = coord;
        scratch->unk_66 = coord;
        coord = position->unk_06 + y_extent;
        scratch->unk_7E = coord;
        scratch->unk_6E = coord;
        coord = position->unk_0A;
        scratch->unk_70 = coord;
        scratch->unk_68 = coord;
        far_z = position->unk_0A;
        far_z -= effect->unk_08.as_u16;
        scratch->unk_80 = far_z;
        scratch->unk_78 = far_z;

        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        {
            void *vertex0 = (u8 *)scratch + 0x64;
            void *vertex1 = (u8 *)scratch + 0x6C;
            void *vertex2 = (u8 *)scratch + 0x74;
            void *vertex3 = (u8 *)scratch + 0x7C;

            depth = func_80065590(vertex0, vertex1, vertex2, vertex3,
                              (u8 *)scratch + 0xD8, (u8 *)scratch + 0xDC,
                              (u8 *)scratch + 0xE0, (u8 *)scratch + 0xE4,
                              (u8 *)scratch + 0x84, (u8 *)scratch + 0x88);
        }
        ((volatile S_func_818BC9CC_2 *)scratch)->unk_B4 = depth;
        packet->unk_08 = scratch->unk_D8;
        packet->unk_0A = scratch->unk_DA;
        packet->unk_14 = scratch->unk_DC;
        packet->unk_16 = scratch->unk_DE;
        packet->unk_20 = scratch->unk_E0;
        packet->unk_22 = scratch->unk_E2;
        packet->unk_2C = scratch->unk_E4;
        packet->unk_2E = scratch->unk_E6;

        if (scratch->unk_B4 < 0x1E0U) {
            full_window[1] = 0;
            full_window[0] = 0;
            render_ctx = ((volatile S_func_818BC9CC_6 *)render_state)->unk_00;
            full_window[3] = 0xFF;
            full_window[2] = 0xFF;
            draw_mode = render_ctx->unk_8D0;
            render_ctx->unk_8D0 = (u8 *)draw_mode + 0x0C;
            func_80067F20(draw_mode, 0, 0, func_80066460(0, 1, 0x280, 0x100), full_window);
            page_depth = 0;
            tag_mask = 0xFF000000;
            ASM_USE(tag_mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            page_blend = 1;
            page_x = 0x280;
            ASM_KEEP(page_depth);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP(page_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

            {
                u32 *ot;
                u32 prim_tag;
                u32 ot_tag;

                ot = OT_ADDR(scratch);
                prim_tag = draw_mode->unk_00;
                ot_tag = *ot;
                draw_mode->unk_00 = (prim_tag & tag_mask) | (ot_tag & addr_mask);
            }
            {
                u32 *ot;

                ot = OT_ADDR(scratch);
                *ot = (*ot & tag_mask) | ((u32)draw_mode & addr_mask);
            }
            {
                u32 *ot;
                u32 prim_tag;
                u32 ot_tag;

                ot = OT_ADDR(scratch);
                prim_tag = packet->unk_00.as_u32;
                ot_tag = *ot;
                packet->unk_00.as_u32 = (prim_tag & tag_mask) | (ot_tag & addr_mask);
            }
            {
                u32 *ot;
                register u32 packet_addr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                ot = OT_ADDR(scratch);
                ASM_KEEP(ot);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                packet_addr = (u32)packet & addr_mask;
                *ot = (*ot & tag_mask) | packet_addr;
            }

            tile_window[0] = 0;
            tile_window[1] = 0x80;
            render_ctx = ((volatile S_func_818BC9CC_6 *)render_state)->unk_00;
            tile_window[3] = 0x40;
            tile_window[2] = 0x40;
            draw_mode = render_ctx->unk_8D0;
            render_ctx->unk_8D0 = (u8 *)draw_mode + 0x0C;
            func_80067F20(draw_mode, 0, 0, func_80066460(page_depth, page_blend, page_x, 0x100), tile_window);
            window_tag_mask = 0xFF000000;

            {
                u32 *ot;
                u32 prim_tag;
                u32 ot_tag;

                ot = OT_ADDR(scratch);
                prim_tag = draw_mode->unk_00;
                ot_tag = *ot;
                draw_mode->unk_00 = (prim_tag & window_tag_mask) | (ot_tag & addr_mask);
            }
            {
                u32 *ot;

                ot = OT_ADDR(scratch);
                *ot = (*ot & window_tag_mask) | ((u32)draw_mode & addr_mask);
            }
        }
        ASM_KEEP_NV(quad_index);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        quad_index++;
    } while (quad_index < 4);

    return 0;
}
