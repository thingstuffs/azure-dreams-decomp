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

s32 func_81892C5C(void *arg0, S_81892C5C_2 *arg1)
{
    u8 *scratch = (u8 *)0x1F800000;
    register u32 mask ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    void *initial_context;
    s32 base_height;
    s32 scale;
    s32 i;
    u32 high_mask;
    s32 step;
    void **ot_ctx;

    ot_ctx = (void **)D_80083160;
    initial_context = *ot_ctx;
    mask = 0x00FF0000;
    mask |= 0xFFFF;
    ((S_81892C5C_0 *)scratch)->unk_18.s = (u8 *)initial_context + 0xB0;
    base_height = ((S_81892C5C_1 *)arg0)->unk_04;
    ((S_81892C5C_0 *)scratch)->unk_68 = ((S_81892C5C_0 *)scratch)->unk_70 =
        ((S_81892C5C_0 *)scratch)->unk_78 = arg1->unk_0A;
    scale = (s16)((base_height + 1) << 5);

    high_mask = 0xFF000000;
    step = 0x100;

    i = 0;
loop:
    {
        void *context;
        void *prim;
        s32 angle0;
        s32 angle_base;
        s32 angle1;
        s32 angle2;
        s32 height;
        register s32 prim_mode ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 trig_result;
        register s32 last_prod ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        context = *ot_ctx;
        prim = ((S_81892C5C_3 *)context)->unk_8D0;
        prim_mode = (s32)((u8 *)prim + 0x18);
        ((S_81892C5C_3 *)context)->unk_8D0 = (void *)prim_mode;
        prim_mode = 5;
        ((S_81892C5C_4 *)prim)->unk_00.at03.v = prim_mode;
        prim_mode = 0x48;
        ((S_81892C5C_4 *)prim)->unk_07 = prim_mode;
        ASM_KEEP_NV(prim_mode);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_81892C5C_4 *)prim)->unk_14 = 0x55555555;
        prim_mode |= 2;
        ((S_81892C5C_4 *)prim)->unk_07 = prim_mode;
        angle_base = step << 1;
        angle0 = i * angle_base;
        height = ((S_81892C5C_1 *)arg0)->unk_04;
        ((S_81892C5C_4 *)prim)->unk_05 = 0;
        ((S_81892C5C_4 *)prim)->unk_06 = 0;
        ((S_81892C5C_4 *)prim)->unk_04 =
            (s8)(-0x80 - (height << 4));

        trig_result = func_800644B8(angle0);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        angle_base = i * 2;
        angle1 = angle_base + 1;
        angle1 *= step;
        ((S_81892C5C_0 *)scratch)->unk_64 = (s16)(arg1->unk_02 +
            (((trig_result >> 4) * scale) >> 8));
        trig_result = func_800644B8(angle1);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        angle2 = angle_base + 2;
        angle2 *= step;
        ((S_81892C5C_0 *)scratch)->unk_6C = (s16)(arg1->unk_02 +
            (((trig_result >> 4) * scale) >> 8));
        ((S_81892C5C_0 *)scratch)->unk_74 = (s16)(arg1->unk_02 +
            (((func_800644B8(angle2) >> 4) * scale) >> 8));
        ((S_81892C5C_0 *)scratch)->unk_66 = (s16)(arg1->unk_06 +
            (((func_80064584(angle0) >> 4) * scale) >> 8));
        ((S_81892C5C_0 *)scratch)->unk_6E = (s16)(arg1->unk_06 +
            (((func_80064584(angle1) >> 4) * scale) >> 8));
        {
            register s32 last_sh ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            last_prod = (func_80064584(angle2) >> 4) * scale;
            last_sh = last_prod >> 8;
            ((S_81892C5C_0 *)scratch)->unk_76 = (s16)(arg1->unk_06 + last_sh);
        }

        {
            u8 *p0 = scratch + 0x64;
            u8 *p1 = scratch + 0x6C;
            u8 *p2 = scratch + 0x74;
            u8 *p3 = scratch + 0xD8;
            ASM_KEEP_DEP_NV(p2, last_prod);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP4_NV(p0, p1, p2, p3);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ((S_81892C5C_0 *)scratch)->unk_B4.s = func_80065530(
                p0, p1, p2, p3, scratch + 0xDC, scratch + 0xE0,
                scratch + 0x84, scratch + 0x88);
        }

        ((S_81892C5C_4 *)prim)->unk_08 = ((S_81892C5C_0 *)scratch)->unk_D8;
        ((S_81892C5C_4 *)prim)->unk_0A = ((S_81892C5C_0 *)scratch)->unk_DA;
        ((S_81892C5C_4 *)prim)->unk_0C = ((S_81892C5C_0 *)scratch)->unk_DC;
        ((S_81892C5C_4 *)prim)->unk_0E = ((S_81892C5C_0 *)scratch)->unk_DE;
        ((S_81892C5C_4 *)prim)->unk_10 = ((S_81892C5C_0 *)scratch)->unk_E0;
        ((S_81892C5C_4 *)prim)->unk_12 = ((S_81892C5C_0 *)scratch)->unk_E2;

        {
            u32 otz = ((S_81892C5C_0 *)scratch)->unk_B4.u;

            if (otz < 0x1E0) {
                void *tpage;

                {
                    u32 newv;
                    register u32 pv ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    u32 *otb = ((S_81892C5C_0 *)scratch)->unk_18.u;
                    pv = ((S_81892C5C_4 *)prim)->unk_00.at00.v & high_mask;
                    ((S_81892C5C_4 *)prim)->unk_00.at00.v = pv | (otb[otz] & mask);
                    newv = (((S_81892C5C_0 *)scratch)->unk_18.u[((S_81892C5C_0 *)scratch)->unk_B4.u] & high_mask) | ((u32)prim & mask);
                    ((S_81892C5C_0 *)scratch)->unk_18.u[((S_81892C5C_0 *)scratch)->unk_B4.u] = newv;
                }

                {
                    S_81892C5C_5 *context2;

                    context2 = ((struct OtCtxS *)ot_ctx)->cur;
                    tpage = context2->unk_8D0;
                    context2->unk_8D0 = (u8 *)tpage + 0xC;
                }
                func_80067F20(tpage, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);

                ((S_81892C5C_6 *)tpage)->unk_00 = (((S_81892C5C_6 *)tpage)->unk_00 & high_mask) |
                    (((S_81892C5C_0 *)scratch)->unk_18.u[((S_81892C5C_0 *)scratch)->unk_B4.u] &
                        mask);
                ((S_81892C5C_0 *)scratch)->unk_18.u[((S_81892C5C_0 *)scratch)->unk_B4.u] =
                    (((S_81892C5C_0 *)scratch)->unk_18.u[((S_81892C5C_0 *)scratch)->unk_B4.u] &
                        high_mask) | ((u32)tpage & mask);
            }
        }

        i++;
    }
    if (i < 8) {
        goto loop;
    }

    {
        void *next = ((S_81892C5C_1_pre *)arg0)[-1].unk_00;
        if (next != 0) {
            arg0 = (u8 *)next + 0x20;
            ASM_USE(arg0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            arg1 = ((S_81892C5C_7 *)next)->unk_08;
            ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            func_800244AC();
        }
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    {
        register s32 rv ASM_REG("$2") = 0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(rv);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        return rv;
    }
}
