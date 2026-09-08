#include "common.h"

typedef struct S_800247D4_0 {
    u8 pad_00[0x18];
    u32 * unk_18;
    u8 pad_1C[0x48];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u8 pad_6A[0x2];
    u16 unk_6C;
    u16 unk_6E;
    u16 unk_70;
    u8 pad_72[0x42];
    s32 unk_B4;
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u8 pad_E0[0x14];
    s32 unk_F4;
    s32 unk_F8;
} S_800247D4_0;   /* scratch in func_800247D4 */

typedef struct S_800247D4_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800247D4_1;   /* ctx in func_800247D4 */

typedef struct S_800247D4_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
} S_800247D4_2;   /* packet in func_800247D4 */

typedef struct S_800247D4_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x28];
    u16 unk_3A;
    u8 pad_3C[0x2];
    u16 unk_3E;
    u8 pad_40[0x2];
    u16 unk_42;
    u8 pad_44[0xE];
    u16 unk_52;
    u8 pad_54[0x2];
    u16 unk_56;
    u8 pad_58[0x2];
    u16 unk_5A;
} S_800247D4_3;   /* arg in func_800247D4 */

typedef struct S_800247D4_4 {
    u32 unk_00;
} S_800247D4_4;   /* (void *)scaled_index in func_800247D4 */



extern u8 D_80083160[];
extern void *D_80024008[];

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065420(void *, void *, void *, void *);

/* Draw eight shaded lines with animated endpoints and insert them into the ordering table. */
s32 func_800247D4(void *effect_data)
{
    u8 *effect = effect_data;
    u8 *initial_render_ctx = *(u8 **)D_80083160;
    u8 *render_ctx;
    register u32 constant_or_count ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 color_base;
    s32 delta_mask;
    s32 radial_step;
    u8 *scratch;
    s32 lines_left;
    u8 *packet;
    void *project_work_a;
    void *project_work_b;
    s32 fixed_delta;
    s32 angle;
    s32 stage_index;
    register s32 start_or_fade ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 end_or_blue;
    s32 offset_or_depth;
    s32 y_or_blue;
    s32 start_depth;
    s32 end_depth;
    s32 mean_depth;

    static void *const stage_labels[] = {
        &&case_early,
        &&case_middle,
        &&case_late,
        &&shared,
    };

    (void)stage_labels;
    ASM_USE_NV(initial_render_ctx);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    constant_or_count = 7;
    delta_mask = 0xFFFF0000;
    color_base = 0x40;
    ASM_USE2_NV(delta_mask, color_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    radial_step = 0x15;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(constant_or_count);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    lines_left = (s32)constant_or_count;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_800247D4_0 *)scratch)->unk_18 = initial_render_ctx + 0xB0;

    do {
        constant_or_count = (u32)D_80083160;
        ASM_KEEP(constant_or_count);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        render_ctx = *(u8 **)constant_or_count;
        packet = ((S_800247D4_1 *)render_ctx)->unk_8D0;
        ((S_800247D4_1 *)render_ctx)->unk_8D0 = packet + 0x14;

        ((S_800247D4_2 *)packet)->unk_00.at03.v = 4;
        ((S_800247D4_2 *)packet)->unk_07 = 0x50;

        ((S_800247D4_0 *)scratch)->unk_64 = ((S_800247D4_3 *)effect)->unk_3A;
        ((S_800247D4_0 *)scratch)->unk_66 = ((S_800247D4_3 *)effect)->unk_3E;
        ((S_800247D4_0 *)scratch)->unk_68 = ((S_800247D4_3 *)effect)->unk_42;

        angle = (radial_step % 8) << 9;
        ((S_800247D4_0 *)scratch)->unk_6C =
            ((S_800247D4_3 *)effect)->unk_52 + ((func_800644B8(angle) * 2) >> 8);
        ((S_800247D4_0 *)scratch)->unk_6E =
            ((S_800247D4_3 *)effect)->unk_56 + ((func_80064584(angle) * 2) >> 8);
        ((S_800247D4_0 *)scratch)->unk_70 = ((S_800247D4_3 *)effect)->unk_5A;

        stage_index = ((S_800247D4_3 *)effect)->unk_10 - 1;
        if ((u32)stage_index >= 15U) {
            goto shared;
        }
        goto *D_80024008[stage_index];

case_early:
    {
        end_or_blue = ((S_800247D4_0 *)scratch)->unk_6C;
        ASM_KEEP(end_or_blue);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        start_or_fade = ((S_800247D4_0 *)scratch)->unk_64;
        fixed_delta &= 0xFFFF;
        fixed_delta |= (end_or_blue - start_or_fade) << 16;
        fixed_delta &= delta_mask;
        fixed_delta >>= 3;
        fixed_delta *= ((S_800247D4_3 *)effect)->unk_10 + 1;

        offset_or_depth = fixed_delta >> 16;
        end_or_blue = ((S_800247D4_0 *)scratch)->unk_6E;
        y_or_blue = ((S_800247D4_0 *)scratch)->unk_66;
        fixed_delta &= 0xFFFF;
        fixed_delta |= (end_or_blue - y_or_blue) << 16;
        fixed_delta &= delta_mask;
        ((S_800247D4_0 *)scratch)->unk_6C = start_or_fade + offset_or_depth;
        fixed_delta >>= 3;
        fixed_delta *= ((S_800247D4_3 *)effect)->unk_10 + 1;

        offset_or_depth = fixed_delta >> 16;
        end_or_blue = ((S_800247D4_0 *)scratch)->unk_70;
        start_or_fade = ((S_800247D4_0 *)scratch)->unk_68;
        fixed_delta &= 0xFFFF;
        fixed_delta |= (end_or_blue - start_or_fade) << 16;
        fixed_delta &= delta_mask;
        y_or_blue += offset_or_depth;
        ((S_800247D4_0 *)scratch)->unk_6E = y_or_blue;
        fixed_delta >>= 3;
        fixed_delta *= ((S_800247D4_3 *)effect)->unk_10 + 1;
        ((S_800247D4_0 *)scratch)->unk_70 = start_or_fade + (fixed_delta >> 16);

        start_or_fade = ((S_800247D4_3 *)effect)->unk_10;
        constant_or_count = 15;
        {
            register s32 red_offset ASM_REG("$9") =
                (start_or_fade + 1) * (s32)constant_or_count;

            constant_or_count = 23;
            y_or_blue = (start_or_fade + 1) * (s32)constant_or_count;
            ((S_800247D4_2 *)packet)->unk_04 = color_base;
            ((S_800247D4_2 *)packet)->unk_05 = color_base;
            ((S_800247D4_2 *)packet)->unk_06 = color_base;
            ((S_800247D4_2 *)packet)->unk_0D = color_base - ((7 - start_or_fade) * 8);
            {
                register s32 red ASM_REG("$2") = 0x40 + red_offset;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                ((S_800247D4_2 *)packet)->unk_0C = red;
            }
            ((S_800247D4_2 *)packet)->unk_0E = 0x40 + y_or_blue;
            goto shared;
        }
    }

case_middle:
        constant_or_count = 0x7F;
        end_or_blue = 0xFF;
        ((S_800247D4_2 *)packet)->unk_04 = color_base;
        ((S_800247D4_2 *)packet)->unk_05 = color_base;
        ((S_800247D4_2 *)packet)->unk_06 = color_base;
        ((S_800247D4_2 *)packet)->unk_0C = (u8)constant_or_count;
        ((S_800247D4_2 *)packet)->unk_0D = 0;
        ((S_800247D4_2 *)packet)->unk_0E = (u8)end_or_blue;
        goto shared;

case_late:
    {
        s32 color_step;

        end_or_blue = ((S_800247D4_0 *)scratch)->unk_6C;
        ASM_KEEP(end_or_blue);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        start_or_fade = ((S_800247D4_0 *)scratch)->unk_64;
        fixed_delta &= 0xFFFF;
        fixed_delta |= (end_or_blue - start_or_fade) << 16;
        fixed_delta &= delta_mask;
        fixed_delta >>= 3;
        fixed_delta *= ((S_800247D4_3 *)effect)->unk_10 - 7;

        offset_or_depth = fixed_delta >> 16;
        end_or_blue = ((S_800247D4_0 *)scratch)->unk_6E;
        y_or_blue = ((S_800247D4_0 *)scratch)->unk_66;
        fixed_delta &= 0xFFFF;
        fixed_delta |= (end_or_blue - y_or_blue) << 16;
        fixed_delta &= delta_mask;
        ((S_800247D4_0 *)scratch)->unk_64 = start_or_fade + offset_or_depth;
        fixed_delta >>= 3;
        fixed_delta *= ((S_800247D4_3 *)effect)->unk_10 - 7;

        offset_or_depth = fixed_delta >> 16;
        end_or_blue = ((S_800247D4_0 *)scratch)->unk_70;
        start_or_fade = ((S_800247D4_0 *)scratch)->unk_68;
        fixed_delta &= 0xFFFF;
        fixed_delta |= (end_or_blue - start_or_fade) << 16;
        fixed_delta &= delta_mask;
        y_or_blue += offset_or_depth;
        ((S_800247D4_0 *)scratch)->unk_66 = y_or_blue;
        fixed_delta >>= 3;
        fixed_delta *= ((S_800247D4_3 *)effect)->unk_10 - 7;
        ((S_800247D4_0 *)scratch)->unk_68 = start_or_fade + (fixed_delta >> 16);

        start_or_fade = ((S_800247D4_3 *)effect)->unk_10;
        color_step = start_or_fade - 7;
        constant_or_count = 15;
        {
            register s32 red_offset ASM_REG("$9") =
                color_step * (s32)constant_or_count;

            constant_or_count = 23;
            y_or_blue = color_step * (s32)constant_or_count;
            ((S_800247D4_2 *)packet)->unk_0D = 0;
            constant_or_count = 0x7F;
            color_step = 0xFF;
            ((S_800247D4_2 *)packet)->unk_0C = (u8)constant_or_count;
            constant_or_count = 15;
            start_or_fade = (constant_or_count - start_or_fade) * 8;
            ((S_800247D4_2 *)packet)->unk_0E = (u8)color_step;
            {
                register s32 red ASM_REG("$2") = 0x40 + red_offset;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                ((S_800247D4_2 *)packet)->unk_04 = red;
            }
            ((S_800247D4_2 *)packet)->unk_05 = (u8)start_or_fade;
            ((S_800247D4_2 *)packet)->unk_06 = 0x40 + y_or_blue;
        }
    }

shared:
        project_work_a = scratch + 0x84;
        project_work_b = scratch + 0x88;
        {
            u8 *start_pos = scratch + 0x64;
            u8 *start_screen = scratch + 0xD8;
            ASM_USE2_NV(start_pos, start_screen);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            start_depth = func_80065420(start_pos, start_screen, project_work_a, project_work_b);
        }
        ((S_800247D4_0 *)scratch)->unk_F4 = start_depth;
        {
            u8 *end_pos = scratch + 0x6C;
            u8 *end_screen = scratch + 0xDC;
            ASM_USE2_NV(end_pos, end_screen);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            end_depth = func_80065420(end_pos, end_screen, project_work_a, project_work_b);
        }
        ((S_800247D4_0 *)scratch)->unk_F8 = end_depth;

        ((S_800247D4_2 *)packet)->unk_08 = ((S_800247D4_0 *)scratch)->unk_D8;
        ((S_800247D4_2 *)packet)->unk_0A = ((S_800247D4_0 *)scratch)->unk_DA;
        ((S_800247D4_2 *)packet)->unk_10 = ((S_800247D4_0 *)scratch)->unk_DC;
        ((S_800247D4_2 *)packet)->unk_12 = ((S_800247D4_0 *)scratch)->unk_DE;

        {
            s32 depth_sum = ((S_800247D4_0 *)scratch)->unk_F4;
            s32 depth_or_sign = ((S_800247D4_0 *)scratch)->unk_F8;

            depth_sum += depth_or_sign;
            depth_or_sign = (u32)depth_sum >> 31;
            depth_sum += depth_or_sign;
            offset_or_depth = depth_sum >> 1;
        }
        ((S_800247D4_0 *)scratch)->unk_B4 = offset_or_depth;
        if ((u32)offset_or_depth < 0x1E0U) {
            u32 address_mask = 0x00FFFFFF;
            u32 *ordering_table;

            {
                u32 bucket_addr =
                    (u32)offset_or_depth << 2;
                u32 *table_base =
                    ((S_800247D4_0 *)scratch)->unk_18;

                {
                    u32 tag_mask = 0xFF000000;

                    bucket_addr += (u32)table_base;
                    ((S_800247D4_2 *)packet)->unk_00.at00.v =
                        (((S_800247D4_2 *)packet)->unk_00.at00.v & tag_mask) |
                        (((S_800247D4_4 *)((void *)bucket_addr))->unk_00 & address_mask);
                    ordering_table = ((S_800247D4_0 *)scratch)->unk_18;
                    ordering_table[((S_800247D4_0 *)scratch)->unk_B4] =
                        (ordering_table[((S_800247D4_0 *)scratch)->unk_B4] & tag_mask) |
                        ((u32)packet & address_mask);
                }
            }
        }

        constant_or_count = (u32)lines_left;
        ASM_KEEP(constant_or_count);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        radial_step -= 3;
        constant_or_count -= 1;
        lines_left = (s32)constant_or_count;
    } while ((s32)constant_or_count >= 0);

    return 0;
}
