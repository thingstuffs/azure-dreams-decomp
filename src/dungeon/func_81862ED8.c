#include "common.h"

typedef struct S_800246D8_0 {
    u8 pad_00[0x18];
    u32 * unk_18;
    u8 pad_1C[0x48];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u8 pad_6A[0x2];
    u16 unk_6C;
    u16 unk_6E;
    u16 unk_70;
    u8 pad_72[0x42];
    s32 unk_B4;
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u8 pad_E0[0x14];
    s32 unk_F4;
    s32 unk_F8;
} S_800246D8_0;   /* scratch in func_800246D8 */

typedef struct S_800246D8_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800246D8_1;   /* ctx in func_800246D8 */

typedef struct S_800246D8_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
} S_800246D8_2;   /* packet in func_800246D8 */

typedef struct S_800246D8_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x10];
    u16 unk_22;
    u8 pad_24[0x2];
    u16 unk_26;
    u8 pad_28[0x2];
    u16 unk_2A;
    u8 pad_2C[0xE];
    u16 unk_3A;
    u8 pad_3C[0x2];
    u16 unk_3E;
    u8 pad_40[0x2];
    u16 unk_42;
} S_800246D8_3;   /* arg in func_800246D8 */



extern u8 D_80083160[];
extern s32 func_80065420(void *, void *, void *, void *);

typedef union {
    s32 word;
    struct {
        u16 low;
        s16 high;
    } half;
} PackedDelta;

/* Interpolates and projects a shaded line, then links it into the depth ordering table. */
s32 func_800246D8(void *line)
{
#ifdef __mips__
    u8 *line_or_red;
#else
    u8 *line_or_red;
#endif
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    void *projection_out_a;
    void *projection_out_b;
#ifdef __mips__
    PackedDelta delta;
#else
    PackedDelta delta;
#endif
#ifdef __mips__
    register s32 mask_or_phase ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#else
    s32 mask_or_phase;
#endif
    s32 phase_or_depth;
#ifdef __mips__
    register s32 x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 multiplier;
    u8 *line_bytes = line;
#else
    s32 x;
    s32 multiplier;
    u8 *line_bytes = line;
#endif
#ifdef __mips__
    register s32 y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 increment ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 end_coord;
#else
    s32 y;
    s32 increment;
    s32 end_coord;
#endif
    s32 first_z;
    s32 second_z;
#ifdef __mips__
    s32 depth_or_tag;
    s32 depth_sum;
    s32 result;
#else
    s32 depth_or_tag;
    s32 depth_sum;
    s32 result;
#endif
    u32 *ordering_table;
    u8 *render_ctx = *(u8 **)D_80083160;

    ((S_800246D8_0 *)scratch)->unk_18 = (u32 *)(render_ctx + 0xB0);
    packet = ((S_800246D8_1 *)render_ctx)->unk_8D0;
#ifdef __mips__
#endif
    line_or_red = line_bytes;
    ((S_800246D8_1 *)render_ctx)->unk_8D0 = packet + 0x14;

    ((S_800246D8_2 *)packet)->unk_00.at03.v = 4;
    ((S_800246D8_2 *)packet)->unk_07 = 0x50;

    ((S_800246D8_0 *)scratch)->unk_64 = ((S_800246D8_3 *)line_or_red)->unk_22;
    ((S_800246D8_0 *)scratch)->unk_66 = ((S_800246D8_3 *)line_or_red)->unk_26;
    ((S_800246D8_0 *)scratch)->unk_68 = ((S_800246D8_3 *)line_or_red)->unk_2A;
    ((S_800246D8_0 *)scratch)->unk_6C = ((S_800246D8_3 *)line_or_red)->unk_3A;
    ((S_800246D8_0 *)scratch)->unk_6E = ((S_800246D8_3 *)line_or_red)->unk_3E;
    ((S_800246D8_0 *)scratch)->unk_70 = ((S_800246D8_3 *)line_or_red)->unk_42;

    phase_or_depth = ((S_800246D8_3 *)line_or_red)->unk_10 - 1;
    switch (phase_or_depth) {
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
    end_coord = ((S_800246D8_0 *)scratch)->unk_6C;
#ifdef __mips__
    ASM_KEEP(end_coord);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
#endif
    x = ((S_800246D8_0 *)scratch)->unk_64;
    end_coord -= x;
    delta.word = end_coord << 16;
    delta.word >>= 3;
    delta.word *= ((S_800246D8_3 *)line_or_red)->unk_10 + 1;

    y = ((S_800246D8_0 *)scratch)->unk_66;
    mask_or_phase = 0xFFFF0000;
    increment = delta.half.high;
    delta.half.high = ((S_800246D8_0 *)scratch)->unk_6E - y;
    delta.word &= mask_or_phase;
    ((S_800246D8_0 *)scratch)->unk_6C = x + increment;
    delta.word >>= 3;
    delta.word *= ((S_800246D8_3 *)line_or_red)->unk_10 + 1;

    end_coord = ((S_800246D8_0 *)scratch)->unk_70;
    x = ((S_800246D8_0 *)scratch)->unk_68;
    increment = delta.half.high;
    delta.half.high = end_coord - x;
    delta.word &= mask_or_phase;
#ifdef __mips__
#endif
    ((S_800246D8_0 *)scratch)->unk_6E = y + increment;
#ifdef __mips__
#endif
    delta.word >>= 3;
    delta.word *= ((S_800246D8_3 *)line_or_red)->unk_10 + 1;
    x += delta.half.high;
    ((S_800246D8_0 *)scratch)->unk_70 = x;
#ifdef __mips__
#endif

    mask_or_phase = ((S_800246D8_3 *)line_or_red)->unk_10;
    multiplier = 15;
    x = mask_or_phase + 1;
#ifdef __mips__
#endif
    line_or_red = (u8 *)(x * multiplier);
    multiplier = 23;
#ifdef __mips__
#endif
    y = x * multiplier;
    x = 0x40;
    ((S_800246D8_2 *)packet)->unk_04 = x;
    ((S_800246D8_2 *)packet)->unk_05 = x;
    ((S_800246D8_2 *)packet)->unk_06 = x;
    x -= (7 - mask_or_phase) * 8;
    multiplier = (s32)line_or_red + 0x40;
    ((S_800246D8_2 *)packet)->unk_0D = x;
    ((S_800246D8_2 *)packet)->unk_0C = multiplier;
    multiplier = y + 0x40;
    ((S_800246D8_2 *)packet)->unk_0E = multiplier;
    goto shared;

case_middle:
    ((S_800246D8_2 *)packet)->unk_04 = 0x40;
    ((S_800246D8_2 *)packet)->unk_05 = 0x40;
    ((S_800246D8_2 *)packet)->unk_06 = 0x40;
    ((S_800246D8_2 *)packet)->unk_0C = 0x7F;
    ((S_800246D8_2 *)packet)->unk_0D = 0;
    ((S_800246D8_2 *)packet)->unk_0E = 0xFF;
    goto shared;

case_late:
    end_coord = ((S_800246D8_0 *)scratch)->unk_6C;
#ifdef __mips__
    ASM_KEEP(end_coord);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
#endif
    x = ((S_800246D8_0 *)scratch)->unk_64;
    end_coord -= x;
    delta.word = end_coord << 16;
    delta.word >>= 3;
    delta.word *= ((S_800246D8_3 *)line_or_red)->unk_10 - 7;

    y = ((S_800246D8_0 *)scratch)->unk_66;
    mask_or_phase = 0xFFFF0000;
    increment = delta.half.high;
    delta.half.high = ((S_800246D8_0 *)scratch)->unk_6E - y;
    delta.word &= mask_or_phase;
    ((S_800246D8_0 *)scratch)->unk_64 = x + increment;
    delta.word >>= 3;
    delta.word *= ((S_800246D8_3 *)line_or_red)->unk_10 - 7;

    end_coord = ((S_800246D8_0 *)scratch)->unk_70;
    x = ((S_800246D8_0 *)scratch)->unk_68;
    increment = delta.half.high;
    delta.half.high = end_coord - x;
    delta.word &= mask_or_phase;
#ifdef __mips__
#endif
    ((S_800246D8_0 *)scratch)->unk_66 = y + increment;
#ifdef __mips__
#endif
    delta.word >>= 3;
    delta.word *= ((S_800246D8_3 *)line_or_red)->unk_10 - 7;
    x += delta.half.high;
    ((S_800246D8_0 *)scratch)->unk_68 = x;
#ifdef __mips__
#endif

    y = ((S_800246D8_3 *)line_or_red)->unk_10;
    x = 15;
    mask_or_phase = y - 7;
#ifdef __mips__
#endif
    line_or_red = (u8 *)(mask_or_phase * x);
    multiplier = 23;
#ifdef __mips__
    ASM_KEEP(multiplier);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
#endif
    mask_or_phase *= multiplier;
    ((S_800246D8_2 *)packet)->unk_0D = 0;
#ifdef __mips__
    ASM_KEEP_NV(packet);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
#endif
    ((S_800246D8_2 *)packet)->unk_05 = (x - y) * 8;
#ifdef __mips__
    ASM_KEEP_NV(packet);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
#endif
    multiplier = 0x7F;
    ((S_800246D8_2 *)packet)->unk_0C = multiplier;
    multiplier = 0xFF;
    ((S_800246D8_2 *)packet)->unk_0E = multiplier;
    multiplier = (s32)line_or_red + 0x40;
    ((S_800246D8_2 *)packet)->unk_04 = multiplier;
    multiplier = mask_or_phase + 0x40;
    ((S_800246D8_2 *)packet)->unk_06 = multiplier;

shared:
    projection_out_a = scratch + 0x84;
    projection_out_b = scratch + 0x88;
    first_z = func_80065420((void *)((u32)scratch | 0x64),
                            (void *)((u32)scratch | 0xD8), projection_out_a, projection_out_b);
    ((S_800246D8_0 *)scratch)->unk_F4 = first_z;
    second_z = func_80065420((void *)((u32)scratch | 0x6C),
                             (void *)((u32)scratch | 0xDC), projection_out_a, projection_out_b);
    ((S_800246D8_0 *)scratch)->unk_F8 = second_z;

    ((S_800246D8_2 *)packet)->unk_08 = ((S_800246D8_0 *)scratch)->unk_D8;
    ((S_800246D8_2 *)packet)->unk_0A = ((S_800246D8_0 *)scratch)->unk_DA;
    ((S_800246D8_2 *)packet)->unk_10 = ((S_800246D8_0 *)scratch)->unk_DC;
    ((S_800246D8_2 *)packet)->unk_12 = ((S_800246D8_0 *)scratch)->unk_DE;

    depth_sum = ((S_800246D8_0 *)scratch)->unk_F4;
    depth_sum += ((S_800246D8_0 *)scratch)->unk_F8;
    depth_or_tag = (s32)(depth_sum + ((u32)depth_sum >> 31)) >> 1;
#ifdef __mips__
#endif
    ((S_800246D8_0 *)scratch)->unk_B4 = depth_or_tag;
    if ((u32)depth_or_tag < 0x1E0U) {
#ifdef __mips__
        u32 entry_addr;
#else
        u32 entry_addr;
#endif
        u32 *ot_base;
        mask_or_phase = 0x00FFFFFF;
#ifdef __mips__
#endif
        entry_addr = depth_or_tag << 2;
#ifdef __mips__
   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#endif
        ot_base = ((S_800246D8_0 *)scratch)->unk_18;
#ifdef __mips__
#endif
        depth_or_tag = 0xFF000000;
#ifdef __mips__
#endif
        entry_addr += (u32)ot_base;
#ifdef __mips__
#endif
        ((S_800246D8_2 *)packet)->unk_00.at00.v =
            (((S_800246D8_2 *)packet)->unk_00.at00.v & depth_or_tag) |
            (*(u32 *)entry_addr & mask_or_phase);

        phase_or_depth = ((S_800246D8_0 *)scratch)->unk_B4;
        ordering_table = ((S_800246D8_0 *)scratch)->unk_18;
        ordering_table[phase_or_depth] =
            (ordering_table[phase_or_depth] & depth_or_tag) |
            ((u32)packet & mask_or_phase);
    }

    result = 0;
#ifdef __mips__
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
#endif
    return result;
}

/* MECHANISM: The 0x28 frame holds s3=scratchpad, s2=packet, and s1/s0 call bases.
   Guarded temporary pins reproduce the packed-delta, color, and return lifetimes.
   Residue is the pooled D_80024008 switch base plus late mflo/OT coloring. */
