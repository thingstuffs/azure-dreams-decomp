#include "modules/dungeon_ovl_7e6e1800.h"

void update_effect_values_and_expire(void *object, s32 unused, Row_819231FC_S_800249FC_0 *effect) {
    s32 ticks_left;
    s16 next_ticks;
    s16 check_result;
    u16 flags;
    u16 paired_value;

    effect->unk_1A += 0x2BC;
    ticks_left = ((Row_819231FC_S_800249FC_1 *)object)->unk_5A.s;
    ((s16 *)D_80025B60)[0] = 1;

    if (ticks_left >= 0x29) {
        paired_value = effect->unk_1E + 0xC8;
        effect->unk_1E = paired_value;
        effect->unk_1C = paired_value;
    } else {
        if (ticks_left < 0x15) {
            paired_value = effect->unk_1E - 0xBE;
            effect->unk_1E = paired_value;
            effect->unk_1C = paired_value;
        }
    }

    check_result = project_and_queue_visible_shaded_quad(3);
    flags = effect->unk_14;
    if ((flags & 0x80) || check_result != 0) {
        effect->unk_14 = flags & 0xFF7F;
    } else {
        effect->unk_14 = flags | 0x80;
    }

    next_ticks = ((Row_819231FC_S_800249FC_1 *)object)->unk_5A.s - 1;
    ((Row_819231FC_S_800249FC_1 *)object)->unk_5A.s = next_ticks;
    if (next_ticks <= 0) {
        ((Row_819231FC_S_800249FC_1_pre *)object)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
