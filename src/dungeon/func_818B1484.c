#include "modules/dungeon_ovl_18d0850.h"

s32 func_80024C84(ovl_18d0850_818B1484_S_818B1484_1 *effect, ovl_18d0850_818B1484_S_818B1484_3 *target, void *context) {
    void *effect_arg;
    s32 wave_table[34];
    s32 *table_ptr;
    s32 *sample_ptr;
    s16 entry_scale;
    s32 entry_arg;
    s32 sample_angle;
    s32 phase;
    s32 phase_rounded;
    s32 index_rounded;
    s32 sample_index;
    s32 entry_index;
    u16 entry_offset;
    void *entry_ptr;

    table_ptr = wave_table;
    sample_index = 0x10;
    sample_ptr = &wave_table[16];
    do {
        index_rounded = sample_index;
        sample_angle = (sample_index - ((index_rounded / 16) * 0x10)) << 8;
        ((ovl_18d0850_818B1484_S_818B1484_0 *)sample_ptr)->unk_00 = (u32) (func_800644B8(sample_angle) >> 4);
        ((ovl_18d0850_818B1484_S_818B1484_0 *)sample_ptr)->unk_44 = (s32) (func_80064584(sample_angle) >> 4);
        sample_ptr--;
    } while (--sample_index >= 0);
    entry_index = ((s32) (effect->unk_16 << 0x10) >> 0x12) + 1;
    if (entry_index < 8) {
        entry_ptr = (void *) ((entry_index << 1) + (u32) effect);
        do {
            phase = effect->unk_10 - entry_index;
            phase_rounded = phase;
            entry_scale = (func_800644B8((phase - ((phase_rounded / 16) * 0x10)) << 9) >> 9) + 0x20;
            func_80064584(entry_index << 9);
            effect_arg = effect;
            entry_offset = ((ovl_18d0850_818B1484_S_818B1484_2 *)entry_ptr)->unk_1A;
            entry_arg = entry_index << 0x11;
            func_80024610(effect_arg, target, context, entry_scale,
                         (s32) (s16) (target->unk_0A - entry_offset),
                         table_ptr, 0xFF, entry_arg >> 0x10);
            entry_ptr += 2;
            entry_index += 1;
        } while (entry_index < 8);
    }
    return 0;
}
