#include "common.h"

struct OtCtxS { void *cur; };

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern u8 D_80083160[];
extern void func_800244AC(void) __attribute__((noreturn));
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065530(void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

s32 func_81892C5C(void *arg0, void *arg1)
{
    u8 *scratch = (u8 *)0x1F800000;
    register u32 mask ASM_REG("$23");
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
    FIELD(scratch, void *, 0x18) = (u8 *)initial_context + 0xB0;
    base_height = FIELD(arg0, s16, 4);
    FIELD(scratch, u16, 0x68) = FIELD(scratch, u16, 0x70) =
        FIELD(scratch, u16, 0x78) = FIELD(arg1, u16, 0xA);
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
        register s32 prim_mode ASM_REG("$2");
        s32 trig_result;
        register s32 last_prod ASM_REG("$9");

        context = *ot_ctx;
        prim = FIELD(context, void *, 0x8D0);
        prim_mode = (s32)((u8 *)prim + 0x18);
        FIELD(context, void *, 0x8D0) = (void *)prim_mode;
        prim_mode = 5;
        FIELD(prim, u8, 3) = prim_mode;
        prim_mode = 0x48;
        FIELD(prim, u8, 7) = prim_mode;
        ASM_KEEP_NV(prim_mode);
        FIELD(prim, u32, 0x14) = 0x55555555;
        prim_mode |= 2;
        FIELD(prim, u8, 7) = prim_mode;
        angle_base = step << 1;
        angle0 = i * angle_base;
        height = FIELD(arg0, s16, 4);
        FIELD(prim, u8, 5) = 0;
        FIELD(prim, u8, 6) = 0;
        FIELD(prim, u8, 4) =
            (s8)(-0x80 - (height << 4));

        trig_result = func_800644B8(angle0);
        ASM_SCHED_BARRIER();

        angle_base = i * 2;
        angle1 = angle_base + 1;
        angle1 *= step;
        FIELD(scratch, s16, 0x64) = (s16)(FIELD(arg1, u16, 2) +
            (((trig_result >> 4) * scale) >> 8));
        trig_result = func_800644B8(angle1);
        ASM_SCHED_BARRIER();

        angle2 = angle_base + 2;
        angle2 *= step;
        FIELD(scratch, s16, 0x6C) = (s16)(FIELD(arg1, u16, 2) +
            (((trig_result >> 4) * scale) >> 8));
        FIELD(scratch, s16, 0x74) = (s16)(FIELD(arg1, u16, 2) +
            (((func_800644B8(angle2) >> 4) * scale) >> 8));
        FIELD(scratch, s16, 0x66) = (s16)(FIELD(arg1, u16, 6) +
            (((func_80064584(angle0) >> 4) * scale) >> 8));
        FIELD(scratch, s16, 0x6E) = (s16)(FIELD(arg1, u16, 6) +
            (((func_80064584(angle1) >> 4) * scale) >> 8));
        {
            register s32 last_sh ASM_REG("$2");

            last_prod = (func_80064584(angle2) >> 4) * scale;
            last_sh = last_prod >> 8;
            FIELD(scratch, s16, 0x76) = (s16)(FIELD(arg1, u16, 6) + last_sh);
        }

        {
            u8 *p0 = scratch + 0x64;
            u8 *p1 = scratch + 0x6C;
            u8 *p2 = scratch + 0x74;
            u8 *p3 = scratch + 0xD8;
            ASM_KEEP_DEP_NV(p2, last_prod);
            ASM_KEEP4_NV(p0, p1, p2, p3);
            FIELD(scratch, s32, 0xB4) = func_80065530(
                p0, p1, p2, p3, scratch + 0xDC, scratch + 0xE0,
                scratch + 0x84, scratch + 0x88);
        }

        FIELD(prim, u16, 8) = FIELD(scratch, u16, 0xD8);
        FIELD(prim, u16, 0xA) = FIELD(scratch, u16, 0xDA);
        FIELD(prim, u16, 0xC) = FIELD(scratch, u16, 0xDC);
        FIELD(prim, u16, 0xE) = FIELD(scratch, u16, 0xDE);
        FIELD(prim, u16, 0x10) = FIELD(scratch, u16, 0xE0);
        FIELD(prim, u16, 0x12) = FIELD(scratch, u16, 0xE2);

        {
            u32 otz = FIELD(scratch, u32, 0xB4);

            if (otz < 0x1E0) {
                void *tpage;

                {
                    u32 newv;
                    register u32 pv ASM_REG("$2");
                    u32 *otb = FIELD(scratch, u32 *, 0x18);
                    pv = FIELD(prim, u32, 0) & high_mask;
                    FIELD(prim, u32, 0) = pv | (otb[otz] & mask);
                    newv = (FIELD(scratch, u32 *, 0x18)[FIELD(scratch, u32, 0xB4)] & high_mask) | ((u32)prim & mask);
                    FIELD(scratch, u32 *, 0x18)[FIELD(scratch, u32, 0xB4)] = newv;
                }

                {
                    void *context2;

                    context2 = ((struct OtCtxS *)ot_ctx)->cur;
                    tpage = FIELD(context2, void *, 0x8D0);
                    FIELD(context2, void *, 0x8D0) = (u8 *)tpage + 0xC;
                }
                func_80067F20(tpage, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);

                FIELD(tpage, u32, 0) = (FIELD(tpage, u32, 0) & high_mask) |
                    (FIELD(scratch, u32 *, 0x18)[FIELD(scratch, u32, 0xB4)] &
                        mask);
                FIELD(scratch, u32 *, 0x18)[FIELD(scratch, u32, 0xB4)] =
                    (FIELD(scratch, u32 *, 0x18)[FIELD(scratch, u32, 0xB4)] &
                        high_mask) | ((u32)tpage & mask);
            }
        }

        i++;
    }
    if (i < 8) {
        goto loop;
    }

    {
        void *next = FIELD(arg0, void *, -8);
        if (next != 0) {
            arg0 = (u8 *)next + 0x20;
            ASM_USE(arg0);
            arg1 = FIELD(next, void *, 8);
            ASM_KEEP(arg1);
            func_800244AC();
        }
    }
    ASM_SCHED_BARRIER();
    {
        register s32 rv ASM_REG("$2") = 0;
        ASM_KEEP(rv);
        return rv;
    }
}
