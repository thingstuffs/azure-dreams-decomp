#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))
#define OT_ADDR(sc) ((u32 *)((FIELD((sc), volatile u32, 0xB4) << 2) + (u32)FIELD((sc), u32 *, 0x18)))

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
    void *effect = effect_data;
    void *position = position_data;
    u8 *scratch;
    u8 *packet;
    register u8 *draw_mode ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *render_ctx;
    u8 *render_state;
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

    render_state = D_80083160;
    scratch = (u8 *)0x1F800000;
    angle = FIELD(render_state, s16, 0xC8);
    ASM_USE(effect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(angle);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(position);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    FIELD(scratch, u8 *, 0x18) = *(u8 **)D_80083160 + 0xB0;
    x_extent = (u32)((func_80064584(angle) >> 4) * FIELD(effect, s16, 8)) >> 8;
    y_extent = (u32)((func_800644B8(angle) >> 4) * FIELD(effect, s16, 8)) >> 8;
    texture_v = (FIELD(effect, s16, 4) % 4) << 3;

    quad_index = 0;
    addr_mask = 0x00FFFFFF;
    do {
        render_ctx = *(u8 **)render_state;
        packet = FIELD(render_ctx, u8 *, 0x8D0);
        FIELD(render_ctx, u8 *, 0x8D0) = packet + 0x34;

        FIELD(packet, u8, 3) = 0x0C;
        FIELD(packet, u8, 7) = 0x3E;
        FIELD(packet, u16, 0x1A) = func_80066460(0, 1, 0x280, 0x100);
        FIELD(packet, u16, 0x0E) = FIELD(effect, u16, 0x0C);
        FIELD(packet, u8, 0x0C) = 0;
        FIELD(packet, u8, 0x0D) = (u8)texture_v;
        FIELD(packet, u8, 0x18) = 0x3F;
        FIELD(packet, u8, 0x19) = (u8)texture_v;
        FIELD(packet, u8, 0x24) = 0x3F;
        FIELD(packet, u8, 0x25) = texture_v + 0x3F;
        FIELD(packet, u8, 0x31) = texture_v + 0x3F;
        FIELD(packet, u8, 0x30) = 0;
        FIELD(packet, u8, 4) = FIELD(effect, u8, 0x0E);
        FIELD(packet, u8, 5) = FIELD(effect, u8, 0x0E);
        intensity = FIELD(effect, u8, 0x0E);
        FIELD(packet, u8, 0x10) = 0;
        FIELD(packet, u8, 0x11) = 0;
        FIELD(packet, u8, 0x12) = 0;
        FIELD(packet, u8, 0x1C) = 0;
        FIELD(packet, u8, 0x1D) = 0;
        FIELD(packet, u8, 0x1E) = 0;
        FIELD(packet, u8, 0x28) = 0;
        FIELD(packet, u8, 0x29) = 0;
        FIELD(packet, u8, 0x2A) = 0;
        FIELD(packet, u8, 6) = intensity;

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

                vertex0 = scratch + 0x64;
                vertex1 = scratch + 0x6C;
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

                vertex0 = scratch + 0x64;
                vertex1 = scratch + 0x6C;
                ASM_KEEP_NV(vertex0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                vertex_arg0 = vertex0;
                vertex_arg1 = vertex1;
                ASM_TAILSLOT_PIN(vertex_arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                func_80024514(vertex_arg0, vertex_arg1);
            }
        }
    L_case0:
        coord = FIELD(position, u16, 2);
        FIELD(scratch, u16, 0x74) = coord;
        FIELD(scratch, u16, 0x64) = coord;
        coord = FIELD(position, u16, 2) + x_extent;
        FIELD(scratch, u16, 0x7C) = coord;
        FIELD(scratch, u16, 0x6C) = coord;
        coord = FIELD(position, u16, 6);
        FIELD(scratch, u16, 0x76) = coord;
        FIELD(scratch, u16, 0x66) = coord;
        coord = FIELD(position, u16, 6) - y_extent;
        FIELD(scratch, u16, 0x7E) = coord;
        FIELD(scratch, u16, 0x6E) = coord;
        coord = FIELD(position, u16, 0xA);
        FIELD(scratch, u16, 0x70) = coord;
        FIELD(scratch, u16, 0x68) = coord;
        far_z = FIELD(position, u16, 0xA);
        far_z = far_z + FIELD(effect, u16, 8);
        ASM_TAILSLOT_PIN_TIED(far_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80024504();
    L_case1:
        coord = FIELD(position, u16, 2);
        FIELD(scratch, u16, 0x74) = coord;
        FIELD(scratch, u16, 0x64) = coord;
        coord = FIELD(position, u16, 2) - x_extent;
        FIELD(scratch, u16, 0x7C) = coord;
        FIELD(scratch, u16, 0x6C) = coord;
        coord = FIELD(position, u16, 6);
        FIELD(scratch, u16, 0x76) = coord;
        FIELD(scratch, u16, 0x66) = coord;
        coord = FIELD(position, u16, 6) + y_extent;
        FIELD(scratch, u16, 0x7E) = coord;
        FIELD(scratch, u16, 0x6E) = coord;
        coord = FIELD(position, u16, 0xA);
        FIELD(scratch, u16, 0x70) = coord;
        FIELD(scratch, u16, 0x68) = coord;
        far_z = FIELD(position, u16, 0xA);
        far_z = far_z + FIELD(effect, u16, 8);
        ASM_TAILSLOT_PIN_TIED(far_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80024504();
    L_case2:
        coord = FIELD(position, u16, 2);
        FIELD(scratch, u16, 0x74) = coord;
        FIELD(scratch, u16, 0x64) = coord;
        coord = FIELD(position, u16, 2) + x_extent;
        FIELD(scratch, u16, 0x7C) = coord;
        FIELD(scratch, u16, 0x6C) = coord;
        coord = FIELD(position, u16, 6);
        FIELD(scratch, u16, 0x76) = coord;
        FIELD(scratch, u16, 0x66) = coord;
        far_y = (u32)FIELD(position, u16, 6) - y_extent;
        ASM_TAILSLOT_PIN_TIED(far_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800244DC();
    L_case3:
        coord = FIELD(position, u16, 2);
        FIELD(scratch, u16, 0x74) = coord;
        FIELD(scratch, u16, 0x64) = coord;
        coord = FIELD(position, u16, 2) - x_extent;
        FIELD(scratch, u16, 0x7C) = coord;
        FIELD(scratch, u16, 0x6C) = coord;
        coord = FIELD(position, u16, 6);
        FIELD(scratch, u16, 0x76) = coord;
        FIELD(scratch, u16, 0x66) = coord;
        coord = FIELD(position, u16, 6) + y_extent;
        FIELD(scratch, u16, 0x7E) = coord;
        FIELD(scratch, u16, 0x6E) = coord;
        coord = FIELD(position, u16, 0xA);
        FIELD(scratch, u16, 0x70) = coord;
        FIELD(scratch, u16, 0x68) = coord;
        far_z = FIELD(position, u16, 0xA);
        far_z -= FIELD(effect, u16, 8);
        FIELD(scratch, u16, 0x80) = far_z;
        FIELD(scratch, u16, 0x78) = far_z;

        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        {
            void *vertex0 = scratch + 0x64;
            void *vertex1 = scratch + 0x6C;
            void *vertex2 = scratch + 0x74;
            void *vertex3 = scratch + 0x7C;

            depth = func_80065590(vertex0, vertex1, vertex2, vertex3,
                              scratch + 0xD8, scratch + 0xDC,
                              scratch + 0xE0, scratch + 0xE4,
                              scratch + 0x84, scratch + 0x88);
        }
        FIELD(scratch, volatile u32, 0xB4) = depth;
        FIELD(packet, u16, 8) = FIELD(scratch, u16, 0xD8);
        FIELD(packet, u16, 0xA) = FIELD(scratch, u16, 0xDA);
        FIELD(packet, u16, 0x14) = FIELD(scratch, u16, 0xDC);
        FIELD(packet, u16, 0x16) = FIELD(scratch, u16, 0xDE);
        FIELD(packet, u16, 0x20) = FIELD(scratch, u16, 0xE0);
        FIELD(packet, u16, 0x22) = FIELD(scratch, u16, 0xE2);
        FIELD(packet, u16, 0x2C) = FIELD(scratch, u16, 0xE4);
        FIELD(packet, u16, 0x2E) = FIELD(scratch, u16, 0xE6);

        if (FIELD(scratch, u32, 0xB4) < 0x1E0U) {
            full_window[1] = 0;
            full_window[0] = 0;
            render_ctx = *(u8 *volatile *)render_state;
            full_window[3] = 0xFF;
            full_window[2] = 0xFF;
            draw_mode = FIELD(render_ctx, u8 *, 0x8D0);
            FIELD(render_ctx, u8 *, 0x8D0) = draw_mode + 0x0C;
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
                prim_tag = *(u32 *)draw_mode;
                ot_tag = *ot;
                *(u32 *)draw_mode = (prim_tag & tag_mask) | (ot_tag & addr_mask);
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
                prim_tag = *(u32 *)packet;
                ot_tag = *ot;
                *(u32 *)packet = (prim_tag & tag_mask) | (ot_tag & addr_mask);
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
            render_ctx = *(u8 *volatile *)render_state;
            tile_window[3] = 0x40;
            tile_window[2] = 0x40;
            draw_mode = FIELD(render_ctx, u8 *, 0x8D0);
            FIELD(render_ctx, u8 *, 0x8D0) = draw_mode + 0x0C;
            func_80067F20(draw_mode, 0, 0, func_80066460(page_depth, page_blend, page_x, 0x100), tile_window);
            window_tag_mask = 0xFF000000;

            {
                u32 *ot;
                u32 prim_tag;
                u32 ot_tag;

                ot = OT_ADDR(scratch);
                prim_tag = *(u32 *)draw_mode;
                ot_tag = *ot;
                *(u32 *)draw_mode = (prim_tag & window_tag_mask) | (ot_tag & addr_mask);
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
