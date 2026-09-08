#include "common.h"

typedef struct S_80174424_0_pre {
    u16 unk_00;
} S_80174424_0_pre;   /* the 0x2 bytes before arg0 in func_80174424, addressed as arg0[-1] */

typedef struct S_80174424_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    u8 pad_A0[0x8];
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
} S_80174424_0;   /* arg0 in func_80174424 */

typedef struct S_80174424_1 {
    u8 pad_00[0x208];
    s16 unk_208;
    u8 pad_20A[0x6];
    s16 unk_210;
    u8 pad_212[0x6];
    s16 unk_218;
} S_80174424_1;   /* out in func_80174424 */



extern void func_80067014(s32 arg0);
extern void func_800672D8(void *arg0, void *arg1);
extern void func_8006733C(void *arg0, void *arg1);
extern void func_801744DC(void) __attribute__((noreturn));

void func_80174424(void *arg0)
{
    s16 stack[270];
    register s16 *base ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 *pixel;
    register s16 *out;
    register s16 delta;
    register s32 scale;
    s32 row;
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

    next = ((S_80174424_0 *)arg0)->unk_96 + 1;
    ((S_80174424_0 *)arg0)->unk_96 = next;
    if (((S_80174424_0 *)arg0)->unk_A8.s < (s16)next) {
        global_page = (s32 *)(u32)0x80080000;
        ((S_80174424_0_pre *)arg0)[-1].unk_00 = ((S_80174424_0_pre *)arg0)[-1].unk_00 | 0x8000;
        global_page[0x14A0 / 4] |= 0x8000;
        return;
    }

    global_page = (s32 *)(u32)0x80080000;
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    func_8006733C((s8 *)arg0 + 0xA0, &stack[4]);
    stack[0] = 0x340;
    stack[2] = 0x80;
    stack[3] = 2;
    if (((S_80174424_0 *)arg0)->unk_9E == 0) {
        stack[1] = 0x100;
        delta = ((S_80174424_0 *)arg0)->unk_96;
        ASM_KEEP(delta);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_801744DC();
        return;
    }

    stack[1] = 0x102;
    high = ((S_80174424_0 *)arg0)->unk_A8.u;
    low = ((S_80174424_0 *)arg0)->unk_96;
    delta = high - low;
    ASM_KEEP(delta);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    func_80067014(0);

    row = 12;
    base = stack;
    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    scale = delta;
    ASM_KEEP(scale);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    inner = 15;
    do {
        index = (row << 4) + 15;
loop_inner:
        count = 0;
        out = base;
        color = index;
loop_pair:
        shifted = color << 1;
        color += 0x30;
        packed = *(u16 *)(u32)(shifted + (u32)(s8 *)base + 8);
        count++;
        ((S_80174424_1 *)out)->unk_208 = packed & 0x1F;
        ((S_80174424_1 *)out)->unk_210 = ((packed << 16) >> 21) & 0x1F;
        ((S_80174424_1 *)out)->unk_218 = ((packed << 16) >> 26) & 0x1F;
        out++;
        if (count < 2) {
            goto loop_pair;
        }

        stack[0x104] = (u16)stack[0x104] +
            ((stack[0x105] - stack[0x104]) * scale) / ((S_80174424_0 *)arg0)->unk_A8.s;
        stack[0x108] = (u16)stack[0x108] +
            ((stack[0x109] - stack[0x108]) * scale) / ((S_80174424_0 *)arg0)->unk_A8.s;
        {
            s32 step;
            s32 pixel_offset;

            step = ((stack[0x10D] - stack[0x10C]) * scale) /
                ((S_80174424_0 *)arg0)->unk_A8.s;
            pixel_offset = index << 1;
            index--;
            stack[0x10C] = (u16)stack[0x10C] + step;
            pixel = (s16 *)(u32)(pixel_offset + (u32)(s8 *)base);
            preserve = *(u16 *)((s8 *)pixel + 8);
            inner--;
            preserve &= 0x8000;
            *(u16 *)((s8 *)pixel + 8) = preserve;
            {
                s32 red;
                register s32 green ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                s32 blue;

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
