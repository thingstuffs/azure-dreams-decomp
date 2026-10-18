#include "modules/dungeon_ovl_1936800.h"

void *create_radial_effect_from_source(void *source, Row_81917004_Copy24 *origin, s16 size_step)
{
    s16 saved_step = size_step;
    void *effect;
    Row_81917004_S_80024804_2 *part;
    Row_81917004_Copy24 *position;
    u8 *effect_state;
    s32 scale_step;
    s32 direction_factor;
    s32 direction_factor_2;
    s32 scaled_factor;
    s32 random_value;
    s16 part_scale;
    s32 alloc_kind;
    void *alloc_source;
    s32 step_word;

    alloc_kind = 0x212;
    alloc_source = (u8 *)source - 0x20;
    effect = func_8003FD64(alloc_kind, alloc_source);
    if (effect != NULL) {
        ((Row_81917004_S_80024804_0 *)effect)->unk_10 = &D_80024710;
        ((Row_81917004_S_80024804_0 *)effect)->unk_20 = ((Row_81917004_S_80024804_1 *)source)->unk_00;

        step_word = (s32)saved_step << 16;
        part = ((Row_81917004_S_80024804_0 *)effect)->unk_0C;
        part->unk_0D = -0x60 - ((step_word >> 16) << 6);
        part->unk_0C = -0x60 - ((step_word >> 16) << 6);
        part->unk_0E = 0xC0;
        part->unk_12 = 0x7DCF;
        part->unk_08 = &D_80025B10;

        part->unk_14 |= 0x000C;
        part->unk_10 |= 0x0020;
        part->unk_14 |= 0x0100;

        random_value = func_80069EF8();
        effect_state = (u8 *)effect + 0x20;
        part->unk_1A = random_value % 0x1000;

        part_scale = ((step_word >> 16) << 8) + 0x500;
        part->unk_1E = part_scale;
        part->unk_1C = part_scale;
        func_8004491C(effect, func_80045340);

        position = ((Row_81917004_S_80024804_0 *)effect)->unk_08;
        *position = *origin;

        ((Row_81917004_S_80024804_3 *)effect_state)->unk_0E.u = ((Row_81917004_S_80024804_1 *)source)->unk_0E;
        ((Row_81917004_S_80024804_3 *)effect_state)->unk_10.u = ((Row_81917004_S_80024804_1 *)source)->unk_10;

        direction_factor = func_800644B8(((Row_81917004_S_80024804_3 *)effect_state)->unk_0E.s);
        position->word[0] -= (scaled_factor = direction_factor >> 4) *
            (func_800644B8(((Row_81917004_S_80024804_3 *)effect_state)->unk_10.s) >> 4) * ((step_word >> 16) + 2) * 8;

        direction_factor_2 = func_800644B8(((Row_81917004_S_80024804_3 *)effect_state)->unk_0E.s);
        position->word[1] -= (scaled_factor = direction_factor_2 >> 4) *
            (func_80064584(((Row_81917004_S_80024804_3 *)effect_state)->unk_10.s) >> 4) * ((step_word >> 16) + 2) * 8;

        position->word[2] -=
            ((func_80064584(((Row_81917004_S_80024804_3 *)effect_state)->unk_0E.s) >> 4) * ((step_word >> 16) + 2)) << 11;
        return effect;
    }

    return NULL;
}
