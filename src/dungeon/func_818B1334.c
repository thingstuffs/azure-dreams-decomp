#include "modules/dungeon_ovl_18d0850.h"

s32 build_a_circular_lookup_table_submit_eight_phase_shifted_entries(ovl_18d0850_818B1334_S_818B1334_1 *source, ovl_18d0850_818B1334_S_818B1334_3 *target, void *context) {
    s32 circle_values[34];
    s32 *circle_entry;
    register s32 *circle_table;
    s16 radius;
    s32 entry_angle;
    s32 circle_angle;
    s32 phase;
    s32 phase_bias;
    s32 index_bias;
    s32 circle_index;
    s32 entry_index;
    u16 angle_offset;
    void *offset_cursor;
    void *source_arg;

    circle_table = circle_values;
    circle_index = 0x10;
    circle_entry = circle_table + 16;
    do {
        index_bias = circle_index;
        circle_angle = (circle_index - ((index_bias / 16) * 0x10)) << 8;
        ((ovl_18d0850_818B1334_S_818B1334_0 *)circle_entry)->unk_00 = (s32) (func_800644B8(circle_angle) >> 4);
        ((ovl_18d0850_818B1334_S_818B1334_0 *)circle_entry)->unk_44 = (s32) (func_80064584(circle_angle) >> 4);
        circle_entry -= 1;
    } while (--circle_index >= 0);
    entry_index = 0;
    offset_cursor = source;
    do {
        phase = source->unk_10 - entry_index;
        phase_bias = phase;
        radius = (func_800644B8((phase - ((phase_bias / 16) * 0x10)) << 9) >> 9) + 0x20;
        func_80064584(entry_index << 0xA);
        source_arg = source;
        angle_offset = ((ovl_18d0850_818B1334_S_818B1334_2 *)offset_cursor)->unk_1A;
        entry_angle = entry_index << 0x11;
        draw_n_16_shaded_line_segments_link_them_ordering_table_depth(source_arg, target, context, radius, (s32) (s16) (target->unk_0A - angle_offset), circle_table, 0xFF, entry_angle >> 0x10);
        offset_cursor += 2;
        entry_index += 1;
    } while (entry_index < 8);
    return 0;
}
