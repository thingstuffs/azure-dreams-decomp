#include "common.h"

typedef struct S_81892C5C_0 {
    u8 pad_00[0x18];
    union { void * s; u32 * u; } unk_18;   /* accessed as both */
    u8 pad_1C[0x48];
    s16 unk_64;
    s16 unk_66;
    u16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    s16 unk_6E;
    u16 unk_70;
    u8 pad_72[0x2];
    s16 unk_74;
    s16 unk_76;
    u16 unk_78;
    u8 pad_7A[0x3A];
    union { s32 s; u32 u; } unk_B4;   /* accessed as both */
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u16 unk_E0;
    u16 unk_E2;
} S_81892C5C_0;   /* scratch in func_81892C5C */

typedef struct S_81892C5C_1_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_81892C5C_1_pre;   /* the 0x8 bytes before arg0 in func_81892C5C, addressed as arg0[-1] */

typedef struct S_81892C5C_1 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_81892C5C_1;   /* arg0 in func_81892C5C */

typedef struct S_81892C5C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81892C5C_2;   /* arg1 in func_81892C5C */

typedef struct S_81892C5C_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_81892C5C_3;   /* context in func_81892C5C */

typedef struct S_81892C5C_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u32 unk_14;
} S_81892C5C_4;   /* prim in func_81892C5C */

typedef struct S_81892C5C_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_81892C5C_5;   /* context2 in func_81892C5C */

typedef struct S_81892C5C_6 {
    u32 unk_00;
} S_81892C5C_6;   /* tpage in func_81892C5C */

typedef struct S_81892C5C_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81892C5C_7;   /* next in func_81892C5C */


struct OtCtxS { void *cur; };


extern u8 D_80083160[];
extern void func_800244AC(void) __attribute__((noreturn));
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065530(void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Draw a red ring around the effect center using eight projected polylines. */
s32 func_81892C5C(void *effect, S_81892C5C_2 *center)
{
    u8 *scratch = (u8 *)0x1F800000;
    register u32 addr_mask ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    void *initial_context;
    s32 base_height;
    s32 radius;
    s32 segment;
    u32 length_mask;
    s32 angle_step;
    void **ot_ctx;

    ot_ctx = (void **)D_80083160;
    initial_context = *ot_ctx;
    addr_mask = 0x00FF0000;
    addr_mask |= 0xFFFF;
    ((S_81892C5C_0 *)scratch)->unk_18.s = (u8 *)initial_context + 0xB0;
    base_height = ((S_81892C5C_1 *)effect)->unk_04;
    ((S_81892C5C_0 *)scratch)->unk_68 = ((S_81892C5C_0 *)scratch)->unk_70 =
        ((S_81892C5C_0 *)scratch)->unk_78 = center->unk_0A;
    radius = (s16)((base_height + 1) << 5);

    length_mask = 0xFF000000;
    angle_step = 0x100;

    segment = 0;
loop:
    {
        void *context;
        void *polyline;
        s32 start_angle;
        s32 angle_base;
        s32 mid_angle;
        s32 end_angle;
        s32 height;
        register s32 prim_mode ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 x_trig;
        register s32 end_y_scaled ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        context = *ot_ctx;
        polyline = ((S_81892C5C_3 *)context)->unk_8D0;
        prim_mode = (s32)((u8 *)polyline + 0x18);
        ((S_81892C5C_3 *)context)->unk_8D0 = (void *)prim_mode;
        prim_mode = 5;
        ((S_81892C5C_4 *)polyline)->unk_00.at03.v = prim_mode;
        prim_mode = 0x48;
        ((S_81892C5C_4 *)polyline)->unk_07 = prim_mode;
        ASM_KEEP_NV(prim_mode);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_81892C5C_4 *)polyline)->unk_14 = 0x55555555;
        prim_mode |= 2;
        ((S_81892C5C_4 *)polyline)->unk_07 = prim_mode;
        angle_base = angle_step << 1;
        start_angle = segment * angle_base;
        height = ((S_81892C5C_1 *)effect)->unk_04;
        ((S_81892C5C_4 *)polyline)->unk_05 = 0;
        ((S_81892C5C_4 *)polyline)->unk_06 = 0;
        ((S_81892C5C_4 *)polyline)->unk_04 =
            (s8)(-0x80 - (height << 4));

        x_trig = func_800644B8(start_angle);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        angle_base = segment * 2;
        mid_angle = angle_base + 1;
        mid_angle *= angle_step;
        ((S_81892C5C_0 *)scratch)->unk_64 = (s16)(center->unk_02 +
            (((x_trig >> 4) * radius) >> 8));
        x_trig = func_800644B8(mid_angle);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        end_angle = angle_base + 2;
        end_angle *= angle_step;
        ((S_81892C5C_0 *)scratch)->unk_6C = (s16)(center->unk_02 +
            (((x_trig >> 4) * radius) >> 8));
        ((S_81892C5C_0 *)scratch)->unk_74 = (s16)(center->unk_02 +
            (((func_800644B8(end_angle) >> 4) * radius) >> 8));
        ((S_81892C5C_0 *)scratch)->unk_66 = (s16)(center->unk_06 +
            (((func_80064584(start_angle) >> 4) * radius) >> 8));
        ((S_81892C5C_0 *)scratch)->unk_6E = (s16)(center->unk_06 +
            (((func_80064584(mid_angle) >> 4) * radius) >> 8));
        {

            end_y_scaled = (func_80064584(end_angle) >> 4) * radius;
            base_height = end_y_scaled >> 8;
            ((S_81892C5C_0 *)scratch)->unk_76 = (s16)(center->unk_06 + base_height);
        }

        {
            u8 *start_vertex = scratch + 0x64;
            u8 *mid_vertex = scratch + 0x6C;
            u8 *end_vertex = scratch + 0x74;
            u8 *screen_start = scratch + 0xD8;
            ASM_KEEP_DEP_NV(end_vertex, end_y_scaled);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP4_NV(start_vertex, mid_vertex, end_vertex, screen_start);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ((S_81892C5C_0 *)scratch)->unk_B4.s = func_80065530(
                start_vertex, mid_vertex, end_vertex, screen_start, scratch + 0xDC, scratch + 0xE0,
                scratch + 0x84, scratch + 0x88);
        }

        ((S_81892C5C_4 *)polyline)->unk_08 = ((S_81892C5C_0 *)scratch)->unk_D8;
        ((S_81892C5C_4 *)polyline)->unk_0A = ((S_81892C5C_0 *)scratch)->unk_DA;
        ((S_81892C5C_4 *)polyline)->unk_0C = ((S_81892C5C_0 *)scratch)->unk_DC;
        ((S_81892C5C_4 *)polyline)->unk_0E = ((S_81892C5C_0 *)scratch)->unk_DE;
        ((S_81892C5C_4 *)polyline)->unk_10 = ((S_81892C5C_0 *)scratch)->unk_E0;
        ((S_81892C5C_4 *)polyline)->unk_12 = ((S_81892C5C_0 *)scratch)->unk_E2;

        {
            u32 otz = ((S_81892C5C_0 *)scratch)->unk_B4.u;

            if (otz < 0x1E0) {
                void *tpage;

                {
                    u32 ot_link;
                    register u32 packet_length ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    u32 *ordering_table = ((S_81892C5C_0 *)scratch)->unk_18.u;
                    packet_length = ((S_81892C5C_4 *)polyline)->unk_00.at00.v & length_mask;
                    ((S_81892C5C_4 *)polyline)->unk_00.at00.v = packet_length | (ordering_table[otz] & addr_mask);
                    ot_link = (((S_81892C5C_0 *)scratch)->unk_18.u[((S_81892C5C_0 *)scratch)->unk_B4.u] & length_mask) | ((u32)polyline & addr_mask);
                    ((S_81892C5C_0 *)scratch)->unk_18.u[((S_81892C5C_0 *)scratch)->unk_B4.u] = ot_link;
                }

                {
                    S_81892C5C_5 *draw_context;

                    draw_context = ((struct OtCtxS *)ot_ctx)->cur;
                    tpage = draw_context->unk_8D0;
                    draw_context->unk_8D0 = (u8 *)tpage + 0xC;
                }
                func_80067F20(tpage, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);

                ((S_81892C5C_6 *)tpage)->unk_00 = (((S_81892C5C_6 *)tpage)->unk_00 & length_mask) |
                    (((S_81892C5C_0 *)scratch)->unk_18.u[((S_81892C5C_0 *)scratch)->unk_B4.u] &
                        addr_mask);
                ((S_81892C5C_0 *)scratch)->unk_18.u[((S_81892C5C_0 *)scratch)->unk_B4.u] =
                    (((S_81892C5C_0 *)scratch)->unk_18.u[((S_81892C5C_0 *)scratch)->unk_B4.u] &
                        length_mask) | ((u32)tpage & addr_mask);
            }
        }

        segment++;
    }
    if (segment < 8) {
        goto loop;
    }

    {
        void *next_effect = ((S_81892C5C_1_pre *)effect)[-1].unk_00;
        if (next_effect != 0) {
            effect = (u8 *)next_effect + 0x20;
            ASM_USE(effect);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            center = ((S_81892C5C_7 *)next_effect)->unk_08;
            ASM_KEEP(center);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            func_800244AC();
        }
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    {
        s32 result = 0;
        return result;
    }
}
