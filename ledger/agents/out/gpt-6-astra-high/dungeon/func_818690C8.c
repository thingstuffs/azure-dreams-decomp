#include "common.h"

typedef struct S_800248C8_0 {
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
} S_800248C8_0;   /* scratch in func_800248C8 */

typedef struct S_800248C8_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800248C8_1;   /* ctx in func_800248C8 */

typedef struct S_800248C8_2 {
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
} S_800248C8_2;   /* packet in func_800248C8 */

typedef struct S_800248C8_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x8];
    u16 unk_1A;
    u8 pad_1C[0x2];
    u16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0xE];
    u16 unk_32;
    u8 pad_34[0x2];
    u16 unk_36;
    u8 pad_38[0x2];
    u16 unk_3A;
} S_800248C8_3;   /* arg in func_800248C8 */



extern u8 D_80083160[];
extern s32 func_80065420(void *, void *, void *, void *);

typedef union {
    s32 word;
    struct {
        u16 low;
        s16 high;
    } half;
} PackedDelta;

/* Interpolate and shade a line, project its endpoints, and add it to the ordering table. */
s32 func_800248C8(void *line_data)
{
#ifdef __mips__
    u8 *line;
#else
    u8 *line;
#endif
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    void *projection_work_a;
    void *projection_work_b;
#ifdef __mips__
    PackedDelta coord_delta;
#else
    PackedDelta coord_delta;
#endif
#ifdef __mips__
    register s32 bit_mask ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
#else
    s32 bit_mask;
#endif
    s32 index;
#ifdef __mips__
    register s32 coord_xz ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 multiplier;
    u8 *line_bytes = line_data;
#else
    s32 coord_xz;
    s32 multiplier;
    u8 *line_bytes = line_data;
#endif
#ifdef __mips__
    register s32 coord_y ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 coord_step ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    s32 end_coord;
#else
    s32 coord_y;
    s32 coord_step;
    s32 end_coord;
#endif
    s32 first_z;
    s32 second_z;
#ifdef __mips__
    s32 depth;
    s32 depth_sum;
    s32 result;
#else
    s32 depth;
    s32 depth_sum;
    s32 result;
#endif
    u32 *ordering_table;
    u8 *render_ctx = *(u8 **)D_80083160;

    ((S_800248C8_0 *)scratch)->unk_18 = (u32 *)(render_ctx + 0xB0);
    packet = ((S_800248C8_1 *)render_ctx)->unk_8D0;
    line = line_bytes;
    ((S_800248C8_1 *)render_ctx)->unk_8D0 = packet + 0x14;

    ((S_800248C8_2 *)packet)->unk_00.at03.v = 4;
    ((S_800248C8_2 *)packet)->unk_07 = 0x50;

    ((S_800248C8_0 *)scratch)->unk_64 = ((S_800248C8_3 *)line)->unk_1A;
    ((S_800248C8_0 *)scratch)->unk_66 = ((S_800248C8_3 *)line)->unk_1E;
    ((S_800248C8_0 *)scratch)->unk_68 = ((S_800248C8_3 *)line)->unk_22;
    ((S_800248C8_0 *)scratch)->unk_6C = ((S_800248C8_3 *)line)->unk_32;
    ((S_800248C8_0 *)scratch)->unk_6E = ((S_800248C8_3 *)line)->unk_36;
    ((S_800248C8_0 *)scratch)->unk_70 = ((S_800248C8_3 *)line)->unk_3A;

    index = ((S_800248C8_3 *)line)->unk_10 - 1;
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
    end_coord = ((S_800248C8_0 *)scratch)->unk_6C;
#ifdef __mips__
    ASM_KEEP(end_coord);   /* MATCH pin: retail schedule: same instructions, different order without it */
#endif
    coord_xz = ((S_800248C8_0 *)scratch)->unk_64;
    end_coord -= coord_xz;
    coord_delta.word = end_coord << 16;
    coord_delta.word >>= 3;
    coord_delta.word *= ((S_800248C8_3 *)line)->unk_10 + 1;

    coord_y = ((S_800248C8_0 *)scratch)->unk_66;
    bit_mask = 0xFFFF0000;
    coord_step = coord_delta.half.high;
    coord_delta.half.high = ((S_800248C8_0 *)scratch)->unk_6E - coord_y;
    coord_delta.word &= bit_mask;
    ((S_800248C8_0 *)scratch)->unk_6C = coord_xz + coord_step;
    coord_delta.word >>= 3;
    coord_delta.word *= ((S_800248C8_3 *)line)->unk_10 + 1;

    end_coord = ((S_800248C8_0 *)scratch)->unk_70;
    coord_xz = ((S_800248C8_0 *)scratch)->unk_68;
    coord_step = coord_delta.half.high;
    coord_delta.half.high = end_coord - coord_xz;
    coord_delta.word &= bit_mask;
    ((S_800248C8_0 *)scratch)->unk_6E = coord_y + coord_step;
    coord_delta.word >>= 3;
    coord_delta.word *= ((S_800248C8_3 *)line)->unk_10 + 1;
    coord_xz += coord_delta.half.high;
    ((S_800248C8_0 *)scratch)->unk_70 = coord_xz;

    bit_mask = ((S_800248C8_3 *)line)->unk_10;
    multiplier = 15;
    coord_xz = bit_mask + 1;
    line = (u8 *)(coord_xz * multiplier);
    multiplier = 23;
    coord_y = coord_xz * multiplier;
    coord_xz = 0x40;
    ((S_800248C8_2 *)packet)->unk_04 = coord_xz;
    ((S_800248C8_2 *)packet)->unk_05 = coord_xz;
    ((S_800248C8_2 *)packet)->unk_06 = coord_xz;
    coord_xz -= (7 - bit_mask) * 8;
    multiplier = (s32)line + 0x40;
    ((S_800248C8_2 *)packet)->unk_0D = coord_xz;
    ((S_800248C8_2 *)packet)->unk_0C = multiplier;
    multiplier = coord_y + 0x40;
    ((S_800248C8_2 *)packet)->unk_0E = multiplier;
    goto shared;

case_middle:
    ((S_800248C8_2 *)packet)->unk_04 = 0x40;
    ((S_800248C8_2 *)packet)->unk_05 = 0x40;
    ((S_800248C8_2 *)packet)->unk_06 = 0x40;
    ((S_800248C8_2 *)packet)->unk_0C = 0x7F;
    ((S_800248C8_2 *)packet)->unk_0D = 0;
    ((S_800248C8_2 *)packet)->unk_0E = 0xFF;
    goto shared;

case_late:
    end_coord = ((S_800248C8_0 *)scratch)->unk_6C;
#ifdef __mips__
    ASM_KEEP(end_coord);   /* MATCH pin: retail schedule: same instructions, different order without it */
#endif
    coord_xz = ((S_800248C8_0 *)scratch)->unk_64;
    end_coord -= coord_xz;
    coord_delta.word = end_coord << 16;
    coord_delta.word >>= 3;
    coord_delta.word *= ((S_800248C8_3 *)line)->unk_10 - 7;

    coord_y = ((S_800248C8_0 *)scratch)->unk_66;
    bit_mask = 0xFFFF0000;
    coord_step = coord_delta.half.high;
    coord_delta.half.high = ((S_800248C8_0 *)scratch)->unk_6E - coord_y;
    coord_delta.word &= bit_mask;
    ((S_800248C8_0 *)scratch)->unk_64 = coord_xz + coord_step;
    coord_delta.word >>= 3;
    coord_delta.word *= ((S_800248C8_3 *)line)->unk_10 - 7;

    end_coord = ((S_800248C8_0 *)scratch)->unk_70;
    coord_xz = ((S_800248C8_0 *)scratch)->unk_68;
    coord_step = coord_delta.half.high;
    coord_delta.half.high = end_coord - coord_xz;
    coord_delta.word &= bit_mask;
    ((S_800248C8_0 *)scratch)->unk_66 = coord_y + coord_step;
    coord_delta.word >>= 3;
    coord_delta.word *= ((S_800248C8_3 *)line)->unk_10 - 7;
    coord_xz += coord_delta.half.high;
    ((S_800248C8_0 *)scratch)->unk_68 = coord_xz;

    coord_y = ((S_800248C8_3 *)line)->unk_10;
    coord_xz = 15;
    bit_mask = coord_y - 7;
    line = (u8 *)(bit_mask * coord_xz);
    multiplier = 23;
#ifdef __mips__
    ASM_KEEP(multiplier);   /* MATCH pin: retail basic-block layout depends on it */
#endif
    bit_mask *= multiplier;
    ((S_800248C8_2 *)packet)->unk_0D = 0;
#ifdef __mips__
    ASM_KEEP_NV(packet);   /* MATCH pin: retail schedule: same instructions, different order without it */
#endif
    ((S_800248C8_2 *)packet)->unk_05 = (coord_xz - coord_y) * 8;
#ifdef __mips__
    ASM_KEEP_NV(packet);   /* MATCH pin: retail schedule: same instructions, different order without it */
#endif
    multiplier = 0x7F;
    ((S_800248C8_2 *)packet)->unk_0C = multiplier;
    multiplier = 0xFF;
    ((S_800248C8_2 *)packet)->unk_0E = multiplier;
    multiplier = (s32)line + 0x40;
    ((S_800248C8_2 *)packet)->unk_04 = multiplier;
    multiplier = bit_mask + 0x40;
    ((S_800248C8_2 *)packet)->unk_06 = multiplier;

shared:
    projection_work_a = scratch + 0x84;
    projection_work_b = scratch + 0x88;
    first_z = func_80065420((void *)((u32)scratch | 0x64),
                            (void *)((u32)scratch | 0xD8), projection_work_a, projection_work_b);
    ((S_800248C8_0 *)scratch)->unk_F4 = first_z;
    second_z = func_80065420((void *)((u32)scratch | 0x6C),
                             (void *)((u32)scratch | 0xDC), projection_work_a, projection_work_b);
    ((S_800248C8_0 *)scratch)->unk_F8 = second_z;

    ((S_800248C8_2 *)packet)->unk_08 = ((S_800248C8_0 *)scratch)->unk_D8;
    ((S_800248C8_2 *)packet)->unk_0A = ((S_800248C8_0 *)scratch)->unk_DA;
    ((S_800248C8_2 *)packet)->unk_10 = ((S_800248C8_0 *)scratch)->unk_DC;
    ((S_800248C8_2 *)packet)->unk_12 = ((S_800248C8_0 *)scratch)->unk_DE;

    depth_sum = ((S_800248C8_0 *)scratch)->unk_F4;
    depth_sum += ((S_800248C8_0 *)scratch)->unk_F8;
    depth = (s32)(depth_sum + ((u32)depth_sum >> 31)) >> 1;
    ((S_800248C8_0 *)scratch)->unk_B4 = depth;
    if ((u32)depth < 0x1E0U) {
#ifdef __mips__
        u32 entry_addr;
#else
        u32 entry_addr;
#endif
        u32 *ot_base;
        bit_mask = 0x00FFFFFF;
        entry_addr = depth << 2;
#ifdef __mips__
           /* MATCH pin: load-bearing for the whole function shape */
#endif
        ot_base = ((S_800248C8_0 *)scratch)->unk_18;
        depth = 0xFF000000;
        entry_addr += (u32)ot_base;
        ((S_800248C8_2 *)packet)->unk_00.at00.v =
            (((S_800248C8_2 *)packet)->unk_00.at00.v & depth) |
            (*(u32 *)entry_addr & bit_mask);

        index = ((S_800248C8_0 *)scratch)->unk_B4;
        ordering_table = ((S_800248C8_0 *)scratch)->unk_18;
        ordering_table[index] =
            (ordering_table[index] & depth) |
            ((u32)packet & bit_mask);
    }

    result = 0;
    return result;
}

/* MECHANISM: The 0x28 frame holds s3=scratchpad, s2=packet, and s1/s0 call bases.
   Guarded temporary pins reproduce the packed-coord_delta, color, and return lifetimes.
   Residue is the pooled D_80024008 switch base plus late mflo/OT coloring. */
