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

s32 func_818BC9CC(void *input0, void *input1)
{
    void *arg0 = input0;
    void *arg1 = input1;
    u8 *scratch;
    u8 *packet;
    register u8 *extra ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *ctx;
    u8 *base;
    u32 hiA;
    u32 hiB;
    s32 tp_x;
    register s32 tp_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 tp_w;
    u32 extentX;
    register u32 extentY ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u32 index;
    register u32 lowMask ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 i;
    u32 tail01;
    u32 tail2;
    s32 angle;
    u16 tile;
    u16 value;
    u8 color;
    volatile s16 rect1[4];
    volatile s16 rect0[4];

    base = D_80083160;
    scratch = (u8 *)0x1F800000;
    angle = FIELD(base, s16, 0xC8);
    ASM_USE(arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(angle);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    FIELD(scratch, u8 *, 0x18) = *(u8 **)D_80083160 + 0xB0;
    extentX = (u32)((func_80064584(angle) >> 4) * FIELD(arg0, s16, 8)) >> 8;
    extentY = (u32)((func_800644B8(angle) >> 4) * FIELD(arg0, s16, 8)) >> 8;
    tile = (FIELD(arg0, s16, 4) % 4) << 3;

    i = 0;
    lowMask = 0x00FFFFFF;
    do {
        ctx = *(u8 **)base;
        packet = FIELD(ctx, u8 *, 0x8D0);
        FIELD(ctx, u8 *, 0x8D0) = packet + 0x34;

        FIELD(packet, u8, 3) = 0x0C;
        FIELD(packet, u8, 7) = 0x3E;
        FIELD(packet, u16, 0x1A) = func_80066460(0, 1, 0x280, 0x100);
        FIELD(packet, u16, 0x0E) = FIELD(arg0, u16, 0x0C);
        FIELD(packet, u8, 0x0C) = 0;
        FIELD(packet, u8, 0x0D) = (u8)tile;
        FIELD(packet, u8, 0x18) = 0x3F;
        FIELD(packet, u8, 0x19) = (u8)tile;
        FIELD(packet, u8, 0x24) = 0x3F;
        FIELD(packet, u8, 0x25) = tile + 0x3F;
        FIELD(packet, u8, 0x31) = tile + 0x3F;
        FIELD(packet, u8, 0x30) = 0;
        FIELD(packet, u8, 4) = FIELD(arg0, u8, 0x0E);
        FIELD(packet, u8, 5) = FIELD(arg0, u8, 0x0E);
        color = FIELD(arg0, u8, 0x0E);
        FIELD(packet, u8, 0x10) = 0;
        FIELD(packet, u8, 0x11) = 0;
        FIELD(packet, u8, 0x12) = 0;
        FIELD(packet, u8, 0x1C) = 0;
        FIELD(packet, u8, 0x1D) = 0;
        FIELD(packet, u8, 0x1E) = 0;
        FIELD(packet, u8, 0x28) = 0;
        FIELD(packet, u8, 0x29) = 0;
        FIELD(packet, u8, 0x2A) = 0;
        FIELD(packet, u8, 6) = color;

        if (i == 1) {
            goto L_case1;
        }
        if (i < 2) {
            if (i == 0) {
                goto L_case0;
            }
            {
                void *fa0;
                register void *fa1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                void *fp0;
                void *fp1;

                fp0 = scratch + 0x64;
                fp1 = scratch + 0x6C;
                ASM_KEEP_NV(fp0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                fa0 = fp0;
                fa1 = fp1;
                ASM_TAILSLOT_PIN(fa1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                func_80024514(fa0, fa1);
            }
        } else {
            if (i == 2) {
                goto L_case2;
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            if (i == 3) {
                goto L_case3;
            }
            {
            {
                void *fa0;
                register void *fa1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                void *fp0;
                void *fp1;

                fp0 = scratch + 0x64;
                fp1 = scratch + 0x6C;
                ASM_KEEP_NV(fp0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                fa0 = fp0;
                fa1 = fp1;
                ASM_TAILSLOT_PIN(fa1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                func_80024514(fa0, fa1);
            }
            }
        }
    L_case0:
            value = FIELD(arg1, u16, 2);
            FIELD(scratch, u16, 0x74) = value;
            FIELD(scratch, u16, 0x64) = value;
            value = FIELD(arg1, u16, 2) + extentX;
            FIELD(scratch, u16, 0x7C) = value;
            FIELD(scratch, u16, 0x6C) = value;
            value = FIELD(arg1, u16, 6);
            FIELD(scratch, u16, 0x76) = value;
            FIELD(scratch, u16, 0x66) = value;
            value = FIELD(arg1, u16, 6) - extentY;
            FIELD(scratch, u16, 0x7E) = value;
            FIELD(scratch, u16, 0x6E) = value;
            value = FIELD(arg1, u16, 0xA);
            FIELD(scratch, u16, 0x70) = value;
            FIELD(scratch, u16, 0x68) = value;
            tail01 = FIELD(arg1, u16, 0xA);
            tail01 = tail01 + FIELD(arg0, u16, 8);
            ASM_TAILSLOT_PIN_TIED(tail01);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024504();
    L_case1:
            value = FIELD(arg1, u16, 2);
            FIELD(scratch, u16, 0x74) = value;
            FIELD(scratch, u16, 0x64) = value;
            value = FIELD(arg1, u16, 2) - extentX;
            FIELD(scratch, u16, 0x7C) = value;
            FIELD(scratch, u16, 0x6C) = value;
            value = FIELD(arg1, u16, 6);
            FIELD(scratch, u16, 0x76) = value;
            FIELD(scratch, u16, 0x66) = value;
            value = FIELD(arg1, u16, 6) + extentY;
            FIELD(scratch, u16, 0x7E) = value;
            FIELD(scratch, u16, 0x6E) = value;
            value = FIELD(arg1, u16, 0xA);
            FIELD(scratch, u16, 0x70) = value;
            FIELD(scratch, u16, 0x68) = value;
            tail01 = FIELD(arg1, u16, 0xA);
            tail01 = tail01 + FIELD(arg0, u16, 8);
            ASM_TAILSLOT_PIN_TIED(tail01);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80024504();
    L_case2:
            value = FIELD(arg1, u16, 2);
            FIELD(scratch, u16, 0x74) = value;
            FIELD(scratch, u16, 0x64) = value;
            value = FIELD(arg1, u16, 2) + extentX;
            FIELD(scratch, u16, 0x7C) = value;
            FIELD(scratch, u16, 0x6C) = value;
            value = FIELD(arg1, u16, 6);
            FIELD(scratch, u16, 0x76) = value;
            FIELD(scratch, u16, 0x66) = value;
            tail2 = (u32)FIELD(arg1, u16, 6) - extentY;
            ASM_TAILSLOT_PIN_TIED(tail2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_800244DC();
    L_case3:
            value = FIELD(arg1, u16, 2);
            FIELD(scratch, u16, 0x74) = value;
            FIELD(scratch, u16, 0x64) = value;
            value = FIELD(arg1, u16, 2) - extentX;
            FIELD(scratch, u16, 0x7C) = value;
            FIELD(scratch, u16, 0x6C) = value;
            value = FIELD(arg1, u16, 6);
            FIELD(scratch, u16, 0x76) = value;
            FIELD(scratch, u16, 0x66) = value;
            value = FIELD(arg1, u16, 6) + extentY;
            FIELD(scratch, u16, 0x7E) = value;
            FIELD(scratch, u16, 0x6E) = value;
            value = FIELD(arg1, u16, 0xA);
            FIELD(scratch, u16, 0x70) = value;
            FIELD(scratch, u16, 0x68) = value;
            tail01 = FIELD(arg1, u16, 0xA);
            tail01 -= FIELD(arg0, u16, 8);
            FIELD(scratch, u16, 0x80) = tail01;
            FIELD(scratch, u16, 0x78) = tail01;

        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        {
            void *ca0 = scratch + 0x64;
            void *ca1 = scratch + 0x6C;
            void *ca2 = scratch + 0x74;
            void *ca3 = scratch + 0x7C;

            index = func_80065590(ca0, ca1, ca2, ca3,
                              scratch + 0xD8, scratch + 0xDC,
                              scratch + 0xE0, scratch + 0xE4,
                              scratch + 0x84, scratch + 0x88);
        }
        FIELD(scratch, volatile u32, 0xB4) = index;
        FIELD(packet, u16, 8) = FIELD(scratch, u16, 0xD8);
        FIELD(packet, u16, 0xA) = FIELD(scratch, u16, 0xDA);
        FIELD(packet, u16, 0x14) = FIELD(scratch, u16, 0xDC);
        FIELD(packet, u16, 0x16) = FIELD(scratch, u16, 0xDE);
        FIELD(packet, u16, 0x20) = FIELD(scratch, u16, 0xE0);
        FIELD(packet, u16, 0x22) = FIELD(scratch, u16, 0xE2);
        FIELD(packet, u16, 0x2C) = FIELD(scratch, u16, 0xE4);
        FIELD(packet, u16, 0x2E) = FIELD(scratch, u16, 0xE6);

        if (FIELD(scratch, u32, 0xB4) < 0x1E0U) {
            rect0[1] = 0;
            rect0[0] = 0;
            ctx = *(u8 *volatile *)base;
            rect0[3] = 0xFF;
            rect0[2] = 0xFF;
            extra = FIELD(ctx, u8 *, 0x8D0);
            FIELD(ctx, u8 *, 0x8D0) = extra + 0x0C;
            func_80067F20(extra, 0, 0, func_80066460(0, 1, 0x280, 0x100), rect0);
            tp_x = 0;
            hiA = 0xFF000000;
            ASM_USE(hiA);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            tp_y = 1;
            tp_w = 0x280;
            ASM_KEEP(tp_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP(tp_w);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

            {
                u32 *ot;
                u32 prim_tag;
                u32 ot_tag;

                ot = OT_ADDR(scratch);
                prim_tag = *(u32 *)extra;
                ot_tag = *ot;
                *(u32 *)extra = (prim_tag & hiA) | (ot_tag & lowMask);
            }
            {
                u32 *ot;

                ot = OT_ADDR(scratch);
                *ot = (*ot & hiA) | ((u32)extra & lowMask);
            }
            {
                u32 *ot;
                u32 prim_tag;
                u32 ot_tag;

                ot = OT_ADDR(scratch);
                prim_tag = *(u32 *)packet;
                ot_tag = *ot;
                *(u32 *)packet = (prim_tag & hiA) | (ot_tag & lowMask);
            }
            {
                u32 *ot;
                register u32 pv ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                ot = OT_ADDR(scratch);
                ASM_KEEP(ot);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                pv = (u32)packet & lowMask;
                *ot = (*ot & hiA) | pv;
            }

            rect1[0] = 0;
            rect1[1] = 0x80;
            ctx = *(u8 *volatile *)base;
            rect1[3] = 0x40;
            rect1[2] = 0x40;
            extra = FIELD(ctx, u8 *, 0x8D0);
            FIELD(ctx, u8 *, 0x8D0) = extra + 0x0C;
            func_80067F20(extra, 0, 0, func_80066460(tp_x, tp_y, tp_w, 0x100), rect1);
            hiB = 0xFF000000;

            {
                u32 *ot;
                u32 prim_tag;
                u32 ot_tag;

                ot = OT_ADDR(scratch);
                prim_tag = *(u32 *)extra;
                ot_tag = *ot;
                *(u32 *)extra = (prim_tag & hiB) | (ot_tag & lowMask);
            }
            {
                u32 *ot;

                ot = OT_ADDR(scratch);
                *ot = (*ot & hiB) | ((u32)extra & lowMask);
            }
        }
        ASM_KEEP_NV(i);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        i++;
    } while (i < 4);

    return 0;
}
