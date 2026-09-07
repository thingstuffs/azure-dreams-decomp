#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

extern void func_80067014(s32 arg0);
extern void func_800672D8(void *arg0, void *arg1);
extern void func_8006733C(void *arg0, void *arg1);
extern void func_801744DC(void) __attribute__((noreturn));
extern void func_80174650(void) __attribute__((noreturn));

void func_80174424(void *arg0)
{
    s16 stack[270];
    register s16 *base ASM_REG("$9");
    register s16 *pixel;
    register s16 *out;
    register s16 delta;
    register s32 scale;
    register s32 row ASM_REG("$11");
    register s32 index;
    register s32 count;
    register s32 inner;
    register s32 color;
    register s32 shifted;
    register u16 packed;
    register u16 preserve;
    register u16 next;
    register u16 high;
    register u16 low;
    register s32 *global_page;

    next = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = next;
    if (FIELD(arg0, s16, 0xA8) < (s16)next) {
        global_page = (s32 *)(u32)0x80080000;
        ASM_KEEP(global_page);
        FIELD(arg0, u16, -2) = FIELD(arg0, u16, -2) | 0x8000;
        global_page[0x14A0 / 4] |= 0x8000;
        return func_80174650();
    }

    global_page = (s32 *)(u32)0x80080000;
    ASM_KEEP(global_page);
    func_8006733C((s8 *)arg0 + 0xA0, &stack[4]);
    stack[0] = 0x340;
    stack[2] = 0x80;
    stack[3] = 2;
    if (FIELD(arg0, s16, 0x9E) == 0) {
        stack[1] = 0x100;
        delta = FIELD(arg0, u16, 0x96);
        ASM_KEEP(delta);
        func_801744DC();
        return;
    }

    stack[1] = 0x102;
    high = FIELD(arg0, u16, 0xA8);
    low = FIELD(arg0, u16, 0x96);
    delta = high - low;
    ASM_KEEP(delta);
    func_80067014(0);

    row = 12;
    base = stack;
    ASM_KEEP(base);
    scale = delta;
    ASM_KEEP(scale);
    inner = 15;
    do {
        index = (row << 4) + 15;
loop_inner:
        count = 0;
        out = base;
        ASM_KEEP(out);
        color = index;
loop_pair:
        shifted = color << 1;
        color += 0x30;
        packed = *(u16 *)(u32)(shifted + (u32)(s8 *)base + 8);
        count++;
        FIELD(out, s16, 0x208) = packed & 0x1F;
        FIELD(out, s16, 0x210) = ((packed << 16) >> 21) & 0x1F;
        FIELD(out, s16, 0x218) = ((packed << 16) >> 26) & 0x1F;
        out++;
        if (count < 2) {
            goto loop_pair;
        }

        stack[0x104] = (u16)stack[0x104] +
            ((stack[0x105] - stack[0x104]) * scale) / FIELD(arg0, s16, 0xA8);
        stack[0x108] = (u16)stack[0x108] +
            ((stack[0x109] - stack[0x108]) * scale) / FIELD(arg0, s16, 0xA8);
        {
            register s32 step ASM_REG("$3");
            register s32 pixel_offset ASM_REG("$6");

            step = ((stack[0x10D] - stack[0x10C]) * scale) /
                FIELD(arg0, s16, 0xA8);
            pixel_offset = index << 1;
            index--;
            ASM_KEEP(index);
            stack[0x10C] = (u16)stack[0x10C] + step;
            pixel = (s16 *)(u32)(pixel_offset + (u32)(s8 *)base);
            preserve = *(u16 *)((s8 *)pixel + 8);
            ASM_KEEP(preserve);
            inner--;
            preserve &= 0x8000;
            *(u16 *)((s8 *)pixel + 8) = preserve;
            {
                register s32 red ASM_REG("$3");
                register s32 green ASM_REG("$4");
                register s32 blue ASM_REG("$2");

                blue = (u16)stack[0x10C];
                green = (u16)stack[0x108];
                red = (u16)stack[0x104];
                blue <<= 10;
                green <<= 5;
                blue += green;
                red += blue;
                preserve += red;
                *(u16 *)((s8 *)pixel + 8) = preserve;
            }
        }
        if (inner >= 0) {
            goto loop_inner;
        }
        row -= 4;
        inner = 15;
    } while (row >= 0);

    func_800672D8(stack, &stack[4]);
    func_80067014(0);
}
