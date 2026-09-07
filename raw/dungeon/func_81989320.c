#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_800644B8();

void func_80024B20(void *arg0) {
    register u16 state ASM_REG("$2");
    {
        register s32 i ASM_REG("$5") = 0;
        s32 scaled;
        do {
            register s32 next ASM_REG("$2");
            s32 index, src_offset, dst_offset;
            u8 *src;
            u8 *dst;
            scaled = i * 2;
            index = scaled + i;
            ASM_SCHED_BARRIER();
            next = i + 1;
            ASM_KEEP(next);
            i = next;
            dst_offset = index * 2;
            src_offset = i * 6;
            src = arg0;
            dst = arg0;
            src += src_offset;
            dst += dst_offset;
            FIELD(dst, u16, 0x10) = FIELD(src, u16, 0x10);
        } while (i < 7);
        ASM_KEEP(i);
    }

    {
        s32 i = 7;
        volatile u16 *p = (volatile u16 *)((u8 *)arg0 + 0x2A);
        do {
            i--;
            p[9] = p[9] + p[10];
            p -= 3;
        } while (i >= 0);
    }

    FIELD(arg0, u16, 0x42)--;
    switch (FIELD(arg0, s16, 0x40)) {
    case 0:
        goto mode_zero;
    case 1:
        goto mode_one;
    case 2:
        goto mode_two;
    case 3:
        goto mode_three;
    default:
        goto tail_default;
    }

tail_default:
    goto tail_return;

mode_zero:
    FIELD(arg0, u16, 0x42) = 0;
    FIELD(arg0, s32, 0x0C) = 0;
    FIELD(arg0, s16, 0x40) = FIELD(arg0, u16, 0x40) + 1;

mode_one:
    {
        s32 accum = FIELD(arg0, s32, 0x0C);
        s32 call_arg = FIELD(arg0, s16, 0x42);
        accum += 0xC0C0C;
        FIELD(arg0, s32, 0x0C) = accum;
        FIELD(arg0, s16, 0x3A) = func_800644B8(call_arg << 9) >> 7;
        if (FIELD(arg0, s32, 0x0C) > 0x60605F) {
            register u16 timer ASM_REG("$3");
            state = FIELD(arg0, u16, 0x40);
            ASM_KEEP(state);
            timer = 0x38;
            ASM_KEEP(timer);
            FIELD(arg0, u16, 0x42) = timer;
            goto increment_state;
        }
        return;
    }

mode_two:
    {
        s32 i = 7;
        s32 y = 0xD0;
        u8 *p = (u8 *)arg0 + 0x2A;
        do {
            register s32 square ASM_REG("$8") = i * i;
            s32 value;
            i--;
            value = y - FIELD(arg0, u16, 0x42);
            y -= 0x18;
            FIELD(p, s16, 0x14) = value + ((square >> 2) * 0x14);
            ASM_KEEP(square);
            p -= 6;
        } while (i >= 0);
    }
    {
        register s32 i ASM_REG("$5") = 6;
        register s32 limit ASM_REG("$4") = 0x160;
        register u8 *p ASM_REG("$6") = (u8 *)arg0 + 0x24;
        register s32 offset ASM_REG("$7") = 0x2A;
        ASM_KEEP(i);
        ASM_KEEP(limit);
        ASM_KEEP(p);
        ASM_KEEP(offset);
        do {
            u16 current = FIELD(p, volatile u16, 0x12);
            if (limit < (FIELD((u8 *)arg0 + offset, s16, 0x12) - FIELD(p, s16, 0x12))) {
                FIELD(p, s16, 0x12) = current + (limit + (limit >> 1));
            }
            limit -= 0x10;
            p -= 6;
            i--;
            offset -= 6;
        } while (i >= 0);
    }
    if (FIELD(arg0, s16, 0x42) < 8) {
        FIELD(arg0, s32, 0x0C) += (s32)0xFFF3F3F4;
    }
    if (FIELD(arg0, s16, 0x42) <= 0) {
        state = FIELD(arg0, u16, 0x40);
increment_state:
        state++;
        FIELD(arg0, u16, 0x40) = state;
        goto tail_return;
    }
    goto tail_return;

mode_three:
    {
        register u32 page ASM_REG("$3") = 0x80080000;
        ASM_KEEP(page);
        FIELD(arg0, u16, -2) |= 0x8000;
        FIELD(page, u32, 0x14A0) |= 0x8000;
    }
tail_return:
    return;
}
