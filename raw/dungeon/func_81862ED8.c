#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern u8 D_80083160[];
extern s32 func_80065420(void *, void *, void *, void *);

typedef union {
    s32 word;
    struct {
        u16 low;
        s16 high;
    } half;
} PackedDelta;

s32 func_800246D8(void *arg0)
{
#ifdef __mips__
    register u8 *arg ASM_REG("$8");
#else
    u8 *arg;
#endif
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    void *work84;
    void *work88;
#ifdef __mips__
    register PackedDelta delta ASM_REG("$7");
#else
    PackedDelta delta;
#endif
#ifdef __mips__
    register s32 high_mask ASM_REG("$4");
#else
    s32 high_mask;
#endif
    s32 index;
#ifdef __mips__
    register s32 x ASM_REG("$3");
    register s32 multiplier ASM_REG("$2");
    register u8 *input ASM_REG("$4") = arg0;
#else
    s32 x;
    s32 multiplier;
    u8 *input = arg0;
#endif
#ifdef __mips__
    register s32 y ASM_REG("$5");
    register s32 increment ASM_REG("$6");
    register s32 end ASM_REG("$2");
#else
    s32 y;
    s32 increment;
    s32 end;
#endif
    s32 first_z;
    s32 second_z;
#ifdef __mips__
    register s32 average ASM_REG("$5");
    register s32 sum ASM_REG("$2");
    register s32 result ASM_REG("$2");
#else
    s32 average;
    s32 sum;
    s32 result;
#endif
    u32 *ordering_table;
    u8 *ctx = *(u8 **)D_80083160;

    FIELD(scratch, u32 *, 0x18) = (u32 *)(ctx + 0xB0);
    packet = FIELD(ctx, u8 *, 0x8D0);
#ifdef __mips__
    ASM_KEEP(input);
    ASM_KEEP(arg);
#endif
    arg = input;
    FIELD(ctx, u8 *, 0x8D0) = packet + 0x14;

    FIELD(packet, u8, 3) = 4;
    FIELD(packet, u8, 7) = 0x50;

    FIELD(scratch, u16, 0x64) = FIELD(arg, u16, 0x22);
    FIELD(scratch, u16, 0x66) = FIELD(arg, u16, 0x26);
    FIELD(scratch, u16, 0x68) = FIELD(arg, u16, 0x2A);
    FIELD(scratch, u16, 0x6C) = FIELD(arg, u16, 0x3A);
    FIELD(scratch, u16, 0x6E) = FIELD(arg, u16, 0x3E);
    FIELD(scratch, u16, 0x70) = FIELD(arg, u16, 0x42);

    index = FIELD(arg, s16, 0x10) - 1;
    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        goto case_early;
    case 6:
        goto case_middle;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        goto case_late;
    default:
        goto shared;
    }

case_early:
    end = FIELD(scratch, u16, 0x6C);
#ifdef __mips__
    ASM_KEEP(end);
#endif
    x = FIELD(scratch, u16, 0x64);
    end -= x;
    delta.word = end << 16;
    delta.word >>= 3;
    delta.word *= FIELD(arg, s16, 0x10) + 1;

    y = FIELD(scratch, u16, 0x66);
    high_mask = 0xFFFF0000;
    increment = delta.half.high;
    delta.half.high = FIELD(scratch, u16, 0x6E) - y;
    delta.word &= high_mask;
    FIELD(scratch, u16, 0x6C) = x + increment;
    delta.word >>= 3;
    delta.word *= FIELD(arg, s16, 0x10) + 1;

    end = FIELD(scratch, u16, 0x70);
    x = FIELD(scratch, u16, 0x68);
    increment = delta.half.high;
    delta.half.high = end - x;
    delta.word &= high_mask;
#ifdef __mips__
    ASM_KEEP(high_mask);
#endif
    FIELD(scratch, u16, 0x6E) = y + increment;
#ifdef __mips__
    ASM_KEEP(increment);
#endif
    delta.word >>= 3;
    delta.word *= FIELD(arg, s16, 0x10) + 1;
    x += delta.half.high;
    FIELD(scratch, u16, 0x70) = x;
#ifdef __mips__
    ASM_KEEP(delta.word);
    ASM_KEEP(x);
#endif

    high_mask = FIELD(arg, s16, 0x10);
    multiplier = 15;
    x = high_mask + 1;
#ifdef __mips__
    ASM_KEEP(multiplier);
#endif
    arg = (u8 *)(x * multiplier);
    multiplier = 23;
#ifdef __mips__
    ASM_KEEP(multiplier);
#endif
    y = x * multiplier;
    x = 0x40;
    FIELD(packet, u8, 4) = x;
    FIELD(packet, u8, 5) = x;
    FIELD(packet, u8, 6) = x;
    x -= (7 - high_mask) * 8;
    multiplier = (s32)arg + 0x40;
    FIELD(packet, u8, 0xD) = x;
    FIELD(packet, u8, 0xC) = multiplier;
    multiplier = y + 0x40;
    FIELD(packet, u8, 0xE) = multiplier;
    goto shared;

case_middle:
    FIELD(packet, u8, 4) = 0x40;
    FIELD(packet, u8, 5) = 0x40;
    FIELD(packet, u8, 6) = 0x40;
    FIELD(packet, u8, 0xC) = 0x7F;
    FIELD(packet, u8, 0xD) = 0;
    FIELD(packet, u8, 0xE) = 0xFF;
    goto shared;

case_late:
    end = FIELD(scratch, u16, 0x6C);
#ifdef __mips__
    ASM_KEEP(end);
#endif
    x = FIELD(scratch, u16, 0x64);
    end -= x;
    delta.word = end << 16;
    delta.word >>= 3;
    delta.word *= FIELD(arg, s16, 0x10) - 7;

    y = FIELD(scratch, u16, 0x66);
    high_mask = 0xFFFF0000;
    increment = delta.half.high;
    delta.half.high = FIELD(scratch, u16, 0x6E) - y;
    delta.word &= high_mask;
    FIELD(scratch, u16, 0x64) = x + increment;
    delta.word >>= 3;
    delta.word *= FIELD(arg, s16, 0x10) - 7;

    end = FIELD(scratch, u16, 0x70);
    x = FIELD(scratch, u16, 0x68);
    increment = delta.half.high;
    delta.half.high = end - x;
    delta.word &= high_mask;
#ifdef __mips__
    ASM_KEEP(high_mask);
#endif
    FIELD(scratch, u16, 0x66) = y + increment;
#ifdef __mips__
    ASM_KEEP(increment);
#endif
    delta.word >>= 3;
    delta.word *= FIELD(arg, s16, 0x10) - 7;
    x += delta.half.high;
    FIELD(scratch, u16, 0x68) = x;
#ifdef __mips__
    ASM_KEEP(delta.word);
    ASM_KEEP(x);
#endif

    y = FIELD(arg, s16, 0x10);
    x = 15;
    high_mask = y - 7;
#ifdef __mips__
    ASM_KEEP(x);
#endif
    arg = (u8 *)(high_mask * x);
    multiplier = 23;
#ifdef __mips__
    ASM_KEEP(multiplier);
#endif
    high_mask *= multiplier;
    FIELD(packet, u8, 0xD) = 0;
#ifdef __mips__
    ASM_KEEP_NV(packet);
#endif
    FIELD(packet, u8, 5) = (x - y) * 8;
#ifdef __mips__
    ASM_KEEP_NV(packet);
#endif
    multiplier = 0x7F;
    FIELD(packet, u8, 0xC) = multiplier;
    multiplier = 0xFF;
    FIELD(packet, u8, 0xE) = multiplier;
    multiplier = (s32)arg + 0x40;
    FIELD(packet, u8, 4) = multiplier;
    multiplier = high_mask + 0x40;
    FIELD(packet, u8, 6) = multiplier;

shared:
    work84 = scratch + 0x84;
    work88 = scratch + 0x88;
    first_z = func_80065420((void *)((u32)scratch | 0x64),
                            (void *)((u32)scratch | 0xD8), work84, work88);
    FIELD(scratch, s32, 0xF4) = first_z;
    second_z = func_80065420((void *)((u32)scratch | 0x6C),
                             (void *)((u32)scratch | 0xDC), work84, work88);
    FIELD(scratch, s32, 0xF8) = second_z;

    FIELD(packet, u16, 8) = FIELD(scratch, u16, 0xD8);
    FIELD(packet, u16, 0xA) = FIELD(scratch, u16, 0xDA);
    FIELD(packet, u16, 0x10) = FIELD(scratch, u16, 0xDC);
    FIELD(packet, u16, 0x12) = FIELD(scratch, u16, 0xDE);

    sum = FIELD(scratch, s32, 0xF4);
    sum += FIELD(scratch, s32, 0xF8);
    average = (s32)(sum + ((u32)sum >> 31)) >> 1;
#ifdef __mips__
    ASM_KEEP(average);
#endif
    FIELD(scratch, s32, 0xB4) = average;
    if ((u32)average < 0x1E0U) {
#ifdef __mips__
        register u32 entry_word ASM_REG("$2");
#else
        u32 entry_word;
#endif
        u32 *table_base;
        high_mask = 0x00FFFFFF;
#ifdef __mips__
        ASM_KEEP(high_mask);
#endif
        entry_word = average << 2;
#ifdef __mips__
        ASM_KEEP(entry_word);
#endif
        table_base = FIELD(scratch, u32 *, 0x18);
#ifdef __mips__
        ASM_KEEP(table_base);
#endif
        average = 0xFF000000;
#ifdef __mips__
        ASM_KEEP(average);
#endif
        entry_word += (u32)table_base;
#ifdef __mips__
        ASM_KEEP(entry_word);
#endif
        FIELD(packet, u32, 0) =
            (FIELD(packet, u32, 0) & average) |
            (*(u32 *)entry_word & high_mask);

        index = FIELD(scratch, s32, 0xB4);
        ordering_table = FIELD(scratch, u32 *, 0x18);
        ordering_table[index] =
            (ordering_table[index] & average) |
            ((u32)packet & high_mask);
    }

    result = 0;
#ifdef __mips__
    ASM_KEEP(result);
#endif
    return result;
}

/* MECHANISM: The 0x28 frame holds s3=scratchpad, s2=packet, and s1/s0 call bases.
   Guarded temporary pins reproduce the packed-delta, color, and return lifetimes.
   Residue is the pooled D_80024008 switch base plus late mflo/OT coloring. */
