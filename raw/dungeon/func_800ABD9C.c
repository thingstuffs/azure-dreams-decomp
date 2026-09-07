#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 (*D_800DF030[])(void);
extern s32 D_800814A0;

extern void func_8004E994(void *arg0);
extern void func_800B16BC(void) __attribute__((noreturn));
extern void func_800B1750(void) __attribute__((noreturn));

void func_800B14FC(void *arg0, s32 arg1, void *arg2)
{
    register void *base ASM_REG("$17") = arg0;
    register void *render ASM_REG("$16");
    register s32 (**dispatch_table)(void) ASM_REG("$2");
    register s32 (**dispatch_entry)(void) ASM_REG("$3");
    s16 state;

    ASM_KEEP4_NV(base, render, arg1, arg2);
    render = arg2;
    dispatch_table = D_800DF030;
    dispatch_entry = &dispatch_table[FIELD(base, s16, 0x24)];
    ASM_KEEP_DEP_NV(dispatch_entry, dispatch_table);

    if ((*dispatch_entry)() != 0 &&
        FIELD(base, s16, 0x20) < 2) {
        FIELD(base, s16, 0x22) = 4;
        FIELD(base, s16, 0x20) = 2;
    }
    ASM_KEEP(base);

    state = FIELD(base, s16, 0x20);
    if (state == 1) {
        return;
    }

    if (state < 2) {
        if (state != 0) {
            func_800B1750();
            return;
        }
        goto state0;
    }

    ASM_SCHED_BARRIER();
    if (state != 2) {
        func_800B1750();
        return;
    }
    goto state2;

state0:
    {
        s16 steps;
        s16 countdown = FIELD(base, s16, 0x26);
        u16 countdown_value = FIELD(base, u16, 0x26);

        if (countdown != 0) {
            countdown_value -= 1;
            FIELD(base, u16, 0x26) = countdown_value;
            func_800B1750();
            return;
        }

        steps = FIELD(base, s16, 0x22);
        if (steps == 0) {
            return;
        }

        {
            u16 value16 = FIELD(render, u16, 0x1E);
            FIELD(render, u16, 0x1E) = value16 + (0x1000 - value16) / steps;
        }

        {
            u8 value8 = FIELD(render, u8, 0x0E);
            steps = FIELD(base, s16, 0x22);
            value8 += (0x80 - value8) / steps;
            FIELD(render, u8, 0x0E) = value8;
            FIELD(render, u8, 0x0D) = value8;
            FIELD(render, u8, 0x0C) = value8;
        }

        {
            s16 value16 = FIELD(base, u16, 0x22) - 1;
            FIELD(base, u16, 0x22) = value16;
            if ((s16)value16 != 0) {
                return;
            }
        }

        FIELD(render, u16, 0x1E) = 0x1000;
        FIELD(render, u32, 0x0C) = 0x00808080;
        FIELD(base, u16, 0x20) = FIELD(base, u16, 0x20) + 1;
        func_800B1750();
        return;
    }

state2:
    {
        s16 steps;
        steps = FIELD(base, s16, 0x22);
        if (steps != 0) {
            u16 value16 = FIELD(render, u16, 0x1E);
            FIELD(render, u16, 0x1E) = value16 + (-(s32)value16 / steps);

            {
                u8 value8 = FIELD(render, u8, 0x0E);
                steps = FIELD(base, s16, 0x22);
                value8 += (-(s32)value8 / steps);
                FIELD(render, u8, 0x0E) = value8;
                FIELD(render, u8, 0x0D) = value8;
                FIELD(render, u8, 0x0C) = value8;
            }
        }

        {
            u16 value16 = FIELD(base, u16, 0x22) - 1;
            FIELD(base, u16, 0x22) = value16;
            if ((s16)value16 > 0) {
                return;
            }
        }

        render = base;
        for (;;) {
            void *object = FIELD(render, void *, 0x50);

            if ((s32)object > 0) {
                render = (u8 *)render + 4;
                func_8004E994(object);
                ASM_USE_NV(render);
                func_800B16BC();
                return;
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
                void *object = FIELD(slot, void *, 0x28);

                if (object != (void *)0) {
                    FIELD(object, u16, -2) |= 0x8000;
                    page[0x14A0 / 4] |= 0x8000;
                }
            }
        }
        FIELD(base, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
}
