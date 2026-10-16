#include "modules/dungeon_ovl_188898c.h"

static __inline__ s32 first_delta_s32_s32(s32 end, s32 start)
{
    return end - start;
}

/* Interpolate and shade a line, project its endpoints, and add it to the ordering table. */
s32 interpolateShadeAndQueueLine(void *line_data, void *unused_render_context)
{
    u8 *line;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    void *projection_work_a;
    void *projection_work_b;
    ovl_188898c_818690C8_PackedDelta coord_delta;
    s32 bit_mask;
    s32 index;
    s32 multiplier;
    u8 *line_bytes = line_data;
    s32 coord_y;
    s32 first_z;
    s32 second_z;
    s32 depth;
    s32 depth_sum;
    s32 result;
    u32 *ordering_table;
    u8 *render_ctx = *(u8 **)((u8 *)(&gameWork));

    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_18 = (u32 *)(render_ctx + 0xB0);
    packet = ((GpuContext *)render_ctx)->packetCursor;
    line = line_bytes;
    ((GpuContext *)render_ctx)->packetCursor = packet + 0x14;

    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_00.at03.v = 4;
    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_07 = 0x50;

    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_64 = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_1A;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_66 = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_1E;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_68 = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_22;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6C = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_32;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6E = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_36;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_70 = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_3A;

    index = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 - 1;
    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:

    {
        s32 x0;
        s32 mask;
        s32 y0;
        s32 z0;
        s32 step_x;
        s32 step_y;
        s32 end_z;

        coord_delta.word = first_delta_s32_s32(((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6C,
            (x0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_64)) << 16;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 + 1;

        y0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_66;
        mask = 0xFFFF0000;
        step_x = (coord_delta.word & mask) >> 16;
        coord_delta.half.high = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6E - y0;
        coord_delta.word &= mask;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6C = x0 + step_x;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 + 1;

        end_z = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_70;
        z0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_68;
        step_y = coord_delta.half.high;
        coord_delta.half.high = end_z - z0;
        coord_delta.word &= mask;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6E = y0 + step_y;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 + 1;
        z0 += coord_delta.half.high;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_70 = z0;
    }
        {
            s32 level;

            bit_mask = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10;
            multiplier = 15;
            level = bit_mask + 1;
            line = (u8 *)(level * multiplier);
            multiplier = 23;
            coord_y = level * multiplier;
            level = 0x40;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_04 = level;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_05 = level;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_06 = level;
            level -= (7 - bit_mask) * 8;
            multiplier = (s32)line + 0x40;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0D = level;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0C = multiplier;
            multiplier = coord_y + 0x40;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0E = multiplier;
        }
        break;
    case 7:

        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_04 = 0x40;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_05 = 0x40;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_06 = 0x40;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0C = 0x7F;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0D = 0;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0E = 0xFF;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:

    {
        s32 x0;
        s32 mask;
        s32 y0;
        s32 z0;
        s32 step_x;
        s32 step_y;
        s32 end_z;

        coord_delta.word = first_delta_s32_s32(((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6C,
            (x0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_64)) << 16;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 - 7;

        y0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_66;
        mask = 0xFFFF0000;
        step_x = (coord_delta.word & mask) >> 16;
        coord_delta.half.high = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_6E - y0;
        coord_delta.word &= mask;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_64 = x0 + step_x;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 - 7;

        end_z = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_70;
        z0 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_68;
        step_y = coord_delta.half.high;
        coord_delta.half.high = end_z - z0;
        coord_delta.word &= mask;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_66 = y0 + step_y;
        coord_delta.word >>= 3;
        coord_delta.word *= ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10 - 7;
        z0 += coord_delta.half.high;
        ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_68 = z0;
    }
        {
            s32 k;
            s32 k23;

            coord_y = ((ovl_188898c_818690C8_S_800248C8_3 *)line)->unk_10;
            k = 15;
            bit_mask = coord_y - 7;
            line = (u8 *)(bit_mask * k);
            k23 = 23;
            bit_mask *= k23;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0D = 0;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_05 = (k - coord_y) * 8;
            multiplier = 0x7F;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0C = multiplier;
            multiplier = 0xFF;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0E = multiplier;
            multiplier = (s32)line + 0x40;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_04 = multiplier;
            multiplier = bit_mask + 0x40;
            ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_06 = multiplier;
        }
        break;
    }

    projection_work_a = scratch + 0x84;
    projection_work_b = scratch + 0x88;
    first_z = func_80065420((void *)((u32)scratch | 0x64),
                            (void *)((u32)scratch | 0xD8), projection_work_a, projection_work_b);
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_F4 = first_z;
    second_z = func_80065420((void *)((u32)scratch | 0x6C),
                             (void *)((u32)scratch | 0xDC), projection_work_a, projection_work_b);
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_F8 = second_z;

    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_08 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_D8;
    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_0A = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_DA;
    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_10 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_DC;
    ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_12 = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_DE;

    depth_sum = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_F4;
    depth_sum += ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_F8;
    depth = (s32)(depth_sum + ((u32)depth_sum >> 31)) >> 1;
    ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_B4 = depth;
    if ((u32)depth < 0x1E0U) {
        u32 entry_addr;
        u32 *ot_base;
        s32 low_mask;
        low_mask = 0x00FFFFFF;
        entry_addr = depth << 2;
        ot_base = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_18;
        depth = 0xFF000000;
        entry_addr += (u32)ot_base;
        ((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_00.at00.v =
            (((ovl_188898c_818690C8_S_800248C8_2 *)packet)->unk_00.at00.v & depth) |
            (*(u32 *)entry_addr & low_mask);

        index = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_B4;
        ordering_table = ((ovl_188898c_818690C8_S_800248C8_0 *)scratch)->unk_18;
        ordering_table[index] =
            (ordering_table[index] & depth) |
            ((u32)packet & low_mask);
    }

    result = 0;
    return result;
}

/* MECHANISM: The 0x28 frame holds s3=scratchpad, s2=packet, and s1/s0 call bases.
   Each interpolation arm keeps its coordinates, steps and mask in arm-local variables
   (single-lifetime quantities for local-alloc), while coord_delta and line stay function-wide;
   the masked step_x read gives the mask the extra reference that orders it ahead of y0. */
