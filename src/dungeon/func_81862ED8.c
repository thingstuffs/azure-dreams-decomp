#include "modules/dungeon_ovl_188298c.h"

static __inline__ s32 first_delta_s32_s32(s32 end, s32 start)
{
    return end - start;
}

/* Interpolates and projects a shaded line, then links it into the depth ordering table. */
s32 dungeonProjectAndQueueShadedLine(void *line, void *unused_render_context)
{
    u8 *line_or_red;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    void *projection_out_a;
    void *projection_out_b;
    ovl_188298c_81862ED8_PackedDelta delta;
    s32 mask_or_phase;
    s32 phase_or_depth;
    s32 multiplier;
    u8 *line_bytes = line;
    s32 y;
    s32 first_z;
    s32 second_z;
    s32 depth_or_tag;
    s32 depth_sum;
    u32 *ordering_table;
    u8 *render_ctx = *(u8 **)((u8 *)(&gameWork));

    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_18 = (u32 *)(render_ctx + 0xB0);
    packet = ((GpuContext *)render_ctx)->packetCursor;
    line_or_red = line_bytes;
    ((GpuContext *)render_ctx)->packetCursor = packet + 0x14;

    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_00.at03.v = 4;
    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_07 = 0x50;

    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_64 = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_22;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_66 = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_26;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_68 = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_2A;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6C = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_3A;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6E = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_3E;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_70 = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_42;

    phase_or_depth = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 - 1;
    switch (phase_or_depth) {
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

        delta.word = first_delta_s32_s32(((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6C, (x0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_64))
        << 16;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 + 1;

        y0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_66;
        mask = 0xFFFF0000;
        step_x = (delta.word & mask) >> 16;
        delta.half.high = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6E - y0;
        delta.word &= mask;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6C = x0 + step_x;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 + 1;

        end_z = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_70;
        z0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_68;
        step_y = delta.half.high;
        delta.half.high = end_z - z0;
        delta.word &= mask;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6E = y0 + step_y;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 + 1;
        z0 += delta.half.high;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_70 = z0;
    }
        {
            s32 level;

            mask_or_phase = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10;
            multiplier = 15;
            level = mask_or_phase + 1;
            line_or_red = (u8 *)(level * multiplier);
            multiplier = 23;
            y = level * multiplier;
            level = 0x40;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_04 = level;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_05 = level;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_06 = level;
            level -= (7 - mask_or_phase) * 8;
            multiplier = (s32)line_or_red + 0x40;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0D = level;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0C = multiplier;
            multiplier = y + 0x40;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0E = multiplier;
        }
        break;
    case 7:
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_04 = 0x40;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_05 = 0x40;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_06 = 0x40;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0C = 0x7F;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0D = 0;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0E = 0xFF;
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

        delta.word = first_delta_s32_s32(((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6C, (x0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_64))
        << 16;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 - 7;

        y0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_66;
        mask = 0xFFFF0000;
        step_x = (delta.word & mask) >> 16;
        delta.half.high = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6E - y0;
        delta.word &= mask;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_64 = x0 + step_x;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 - 7;

        end_z = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_70;
        z0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_68;
        step_y = delta.half.high;
        delta.half.high = end_z - z0;
        delta.word &= mask;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_66 = y0 + step_y;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 - 7;
        z0 += delta.half.high;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_68 = z0;
    }
        {
            s32 k;
            s32 k23;

            y = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10;
            k = 15;
            mask_or_phase = y - 7;
            line_or_red = (u8 *)(mask_or_phase * k);
            k23 = 23;
            mask_or_phase *= k23;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0D = 0;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_05 = (k - y) * 8;
            multiplier = 0x7F;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0C = multiplier;
            multiplier = 0xFF;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0E = multiplier;
            multiplier = (s32)line_or_red + 0x40;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_04 = multiplier;
            multiplier = mask_or_phase + 0x40;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_06 = multiplier;
        }
        break;
    }

    projection_out_a = scratch + 0x84;
    projection_out_b = scratch + 0x88;
    first_z = func_80065420((void *)((u32)scratch | 0x64),
                            (void *)((u32)scratch | 0xD8), projection_out_a, projection_out_b);
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_F4 = first_z;
    second_z = func_80065420((void *)((u32)scratch | 0x6C),
                             (void *)((u32)scratch | 0xDC), projection_out_a, projection_out_b);
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_F8 = second_z;

    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_08 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_D8;
    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0A = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_DA;
    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_10 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_DC;
    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_12 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_DE;

    depth_sum = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_F4;
    depth_sum += ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_F8;
    depth_or_tag = (s32)(depth_sum + ((u32)depth_sum >> 31)) >> 1;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_B4 = depth_or_tag;
    if ((u32)depth_or_tag < 0x1E0U) {
        u32 entry_addr;
        u32 *ot_base;
        s32 low_mask;
        low_mask = 0x00FFFFFF;
        entry_addr = depth_or_tag << 2;
        ot_base = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_18;
        depth_or_tag = 0xFF000000;
        entry_addr += (u32)ot_base;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_00.at00.v =
            (((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_00.at00.v & depth_or_tag) |
            (*(u32 *)entry_addr & low_mask);

        phase_or_depth = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_B4;
        ordering_table = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_18;
        ordering_table[phase_or_depth] =
            (ordering_table[phase_or_depth] & depth_or_tag) |
            ((u32)packet & low_mask);
    }

    return 0;
}

/* MECHANISM: The 0x28 frame holds s3=scratchpad, s2=packet, and s1/s0 call bases.
   Each interpolation arm keeps its coordinates, steps and mask in arm-local variables
   (single-lifetime quantities for local-alloc), while delta and line_or_red stay function-wide;
   the masked step_x read gives the mask the extra reference that orders it ahead of y0. */
