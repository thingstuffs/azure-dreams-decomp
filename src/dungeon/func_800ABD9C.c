#include "common.h"

typedef struct S_800B14FC_0 {
    u8 pad_00[0x20];
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    union { s16 s; u16 u; } unk_22;   /* accessed as both */
    s16 unk_24;
    union { s16 s; u16 u; } unk_26;   /* accessed as both */
} S_800B14FC_0;   /* base in func_800B14FC */

typedef struct S_800B14FC_1 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { u32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xE];
    u16 unk_1E;
    u8 pad_20[0x30];
    void * unk_50;
} S_800B14FC_1;   /* render in func_800B14FC */

typedef struct S_800B14FC_2 {
    u8 pad_00[0x28];
    void * unk_28;
} S_800B14FC_2;   /* slot in func_800B14FC */

typedef struct S_800B14FC_3_pre {
    u16 unk_00;
} S_800B14FC_3_pre;   /* the 0x2 bytes before object in func_800B14FC, addressed as object[-1] */



extern s32 (*D_800DF030[])(void);
extern s32 D_800814A0;

extern void func_8004E994(void *arg0);

void func_800B14FC(void *arg0, s32 arg1, void *arg2)
{
    void *base = arg0;
    void *render;
    s32 (**dispatch_table)(void);
    register s32 (**dispatch_entry)(void) ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 state;

    ASM_KEEP4_NV(base, render, arg1, arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    render = arg2;
    dispatch_table = D_800DF030;
    dispatch_entry = &dispatch_table[((S_800B14FC_0 *)base)->unk_24];
    ASM_KEEP_DEP_NV(dispatch_entry, dispatch_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    if ((*dispatch_entry)() != 0 &&
        ((S_800B14FC_0 *)base)->unk_20.s < 2) {
        ((S_800B14FC_0 *)base)->unk_22.s = 4;
        ((S_800B14FC_0 *)base)->unk_20.s = 2;
    }

    state = ((S_800B14FC_0 *)base)->unk_20.s;
    if (state == 1) {
        return;
    }

    if (state < 2) {
        if (state != 0) {
            ASM_SCHED_BARRIER(); /* MATCH: retain the separate jump to the shared epilogue. */
            return;
        }
        goto state0;
    }

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state != 2) {
        return;
    }
    goto state2;

state0:
    {
        s16 steps;
        s16 countdown = ((S_800B14FC_0 *)base)->unk_26.s;
        u16 countdown_value = ((S_800B14FC_0 *)base)->unk_26.u;

        if (countdown != 0) {
            countdown_value -= 1;
            ((S_800B14FC_0 *)base)->unk_26.u = countdown_value;
            return;
        }

        steps = ((S_800B14FC_0 *)base)->unk_22.s;
        if (steps == 0) {
            return;
        }

        {
            u16 value16 = ((S_800B14FC_1 *)render)->unk_1E;
            ((S_800B14FC_1 *)render)->unk_1E = value16 + (0x1000 - value16) / steps;
        }

        {
            u8 value8 = ((S_800B14FC_1 *)render)->unk_0C.at02.v;
            steps = ((S_800B14FC_0 *)base)->unk_22.s;
            value8 += (0x80 - value8) / steps;
            ((S_800B14FC_1 *)render)->unk_0C.at02.v = value8;
            ((S_800B14FC_1 *)render)->unk_0C.at01.v = value8;
            ((S_800B14FC_1 *)render)->unk_0C.at00.v = value8;
        }

        {
            s16 value16 = ((S_800B14FC_0 *)base)->unk_22.u - 1;
            ((S_800B14FC_0 *)base)->unk_22.u = value16;
            if ((s16)value16 != 0) {
                return;
            }
        }

        ((S_800B14FC_1 *)render)->unk_1E = 0x1000;
        ((S_800B14FC_1 *)render)->unk_0C.at00u.v = 0x00808080;
        ((S_800B14FC_0 *)base)->unk_20.u = ((S_800B14FC_0 *)base)->unk_20.u + 1;
        return;
    }

state2:
    {
        s16 steps;
        steps = ((S_800B14FC_0 *)base)->unk_22.s;
        if (steps != 0) {
            u16 value16 = ((S_800B14FC_1 *)render)->unk_1E;
            ((S_800B14FC_1 *)render)->unk_1E = value16 + (-(s32)value16 / steps);

            {
                u8 value8 = ((S_800B14FC_1 *)render)->unk_0C.at02.v;
                steps = ((S_800B14FC_0 *)base)->unk_22.s;
                value8 += (-(s32)value8 / steps);
                ((S_800B14FC_1 *)render)->unk_0C.at02.v = value8;
                ((S_800B14FC_1 *)render)->unk_0C.at01.v = value8;
                ((S_800B14FC_1 *)render)->unk_0C.at00.v = value8;
            }
        }

        {
            u16 value16 = ((S_800B14FC_0 *)base)->unk_22.u - 1;
            ((S_800B14FC_0 *)base)->unk_22.u = value16;
            if ((s16)value16 > 0) {
                return;
            }
        }

        render = base;
        for (;;) {
            void *object = ((S_800B14FC_1 *)render)->unk_50;

            if ((s32)object > 0) {
                render = (u8 *)render + 4;
                func_8004E994(object);
                ASM_USE_NV(render);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                continue;
            }
            render = (u8 *)render + 4;
            if (object == (void *)0) {
                break;
            }
        }

        {
            s32 j = 0;
            u32 *page = (u32 *)0x80080000;
            void *slot = base;
            for (; j < 4; j++, slot = (u8 *)slot + 4) {
                void *object = ((S_800B14FC_2 *)slot)->unk_28;

                if (object != (void *)0) {
                    ((S_800B14FC_3_pre *)object)[-1].unk_00 |= 0x8000;
                    page[0x14A0 / 4] |= 0x8000;
                }
            }
        }
        (*(u16 *)((u8 *)base + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
}
