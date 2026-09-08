#include "common.h"

typedef struct S_80024B20_0 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_80024B20_0;   /* dst in func_80024B20 */

typedef struct S_80024B20_1 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_80024B20_1;   /* src in func_80024B20 */

typedef struct S_80024B20_2_pre {
    u16 unk_00;
} S_80024B20_2_pre;   /* the 0x2 bytes before arg0 in func_80024B20, addressed as arg0[-1] */

typedef struct S_80024B20_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2A];
    s16 unk_3A;
    u8 pad_3C[0x4];
    union { s16 s; u16 u; } unk_40;   /* accessed as both */
    union { u16 u; s16 s; } unk_42;   /* accessed as both */
} S_80024B20_2;   /* arg0 in func_80024B20 */

typedef struct S_80024B20_3 {
    u8 pad_00[0x12];
    union { volatile u16 v; s16 n; } unk_12;   /* accessed as both */
    s16 unk_14;
} S_80024B20_3;   /* p in func_80024B20 */

typedef struct S_80024B20_4 {
    u8 pad_00[0x12];
    s16 unk_12;
} S_80024B20_4;   /* (u8 *)arg0 + offset in func_80024B20 */

typedef struct S_80024B20_5 {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} S_80024B20_5;   /* page in func_80024B20 */



extern s32 func_800644B8();

/* Updates an eight-segment effect's samples, motion, color, and lifetime. */
void func_80024B20(void *effect) {
    u16 state;
    {
        register s32 segment_index ASM_REG("$5") = 0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 doubled_index;
        do {
            register s32 next_index ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            s32 word_offset, src_offset, dst_offset;
            u8 *src_segment;
            u8 *dst_segment;
            doubled_index = segment_index * 2;
            word_offset = doubled_index + segment_index;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            next_index = segment_index + 1;
            ASM_KEEP(next_index);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            segment_index = next_index;
            dst_offset = word_offset * 2;
            src_offset = segment_index * 6;
            src_segment = effect;
            dst_segment = effect;
            src_segment += src_offset;
            dst_segment += dst_offset;
            ((S_80024B20_0 *)dst_segment)->unk_10 = ((S_80024B20_1 *)src_segment)->unk_10;
        } while (segment_index < 7);
    }

    {
        s32 segment_index = 7;
        volatile u16 *segment = (volatile u16 *)((u8 *)effect + 0x2A);
        do {
            segment_index--;
            segment[9] = segment[9] + segment[10];
            segment -= 3;
        } while (segment_index >= 0);
    }

    ((S_80024B20_2 *)effect)->unk_42.u--;
    switch (((S_80024B20_2 *)effect)->unk_40.s) {
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
    ((S_80024B20_2 *)effect)->unk_42.u = 0;
    ((S_80024B20_2 *)effect)->unk_0C = 0;
    ((S_80024B20_2 *)effect)->unk_40.s = ((S_80024B20_2 *)effect)->unk_40.u + 1;

mode_one:
    {
        s32 color = ((S_80024B20_2 *)effect)->unk_0C;
        s32 phase = ((S_80024B20_2 *)effect)->unk_42.s;
        color += 0xC0C0C;
        ((S_80024B20_2 *)effect)->unk_0C = color;
        ((S_80024B20_2 *)effect)->unk_3A = func_800644B8(phase << 9) >> 7;
        if (((S_80024B20_2 *)effect)->unk_0C > 0x60605F) {
            register u16 timer ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            state = ((S_80024B20_2 *)effect)->unk_40.u;
            timer = 0x38;
            ((S_80024B20_2 *)effect)->unk_42.u = timer;
            goto increment_state;
        }
        return;
    }

mode_two:
    {
        s32 segment_index = 7;
        s32 base_speed = 0xD0;
        u8 *segment = (u8 *)effect + 0x2A;
        do {
            register s32 index_squared ASM_REG("$8") = segment_index * segment_index;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 speed_bias;
            segment_index--;
            speed_bias = base_speed - ((S_80024B20_2 *)effect)->unk_42.u;
            base_speed -= 0x18;
            ((S_80024B20_3 *)segment)->unk_14 = speed_bias + ((index_squared >> 2) * 0x14);
            ASM_KEEP(index_squared);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            segment -= 6;
        } while (segment_index >= 0);
    }
    {
        s32 segment_index = 6;
        register s32 gap_limit ASM_REG("$4") = 0x160;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        register u8 *segment ASM_REG("$6") = (u8 *)effect + 0x24;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        register s32 next_offset ASM_REG("$7") = 0x2A;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        do {
            u16 position = ((S_80024B20_3 *)segment)->unk_12.v;
            if (gap_limit < (((S_80024B20_4 *)((u8 *)effect + next_offset))->unk_12 - ((S_80024B20_3 *)segment)->unk_12.n)) {
                ((S_80024B20_3 *)segment)->unk_12.n = position + (gap_limit + (gap_limit >> 1));
            }
            gap_limit -= 0x10;
            segment -= 6;
            segment_index--;
            next_offset -= 6;
        } while (segment_index >= 0);
    }
    if (((S_80024B20_2 *)effect)->unk_42.s < 8) {
        ((S_80024B20_2 *)effect)->unk_0C += (s32)0xFFF3F3F4;
    }
    if (((S_80024B20_2 *)effect)->unk_42.s <= 0) {
        state = ((S_80024B20_2 *)effect)->unk_40.u;
increment_state:
        state++;
        ((S_80024B20_2 *)effect)->unk_40.u = state;
        goto tail_return;
    }
    goto tail_return;

mode_three:
    {
        register u32 globals_base ASM_REG("$3") = 0x80080000;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(globals_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((S_80024B20_2_pre *)effect)[-1].unk_00 |= 0x8000;
        ((S_80024B20_5 *)globals_base)->unk_14A0 |= 0x8000;
    }
tail_return:
    return;
}
