#include "modules/dungeon_ovl_19c088c.h"

void dungeonUpdateEffectCountdownFields(void *object_data)
{
    s32 phase_index;
    s32 pair_offset;
    Row_819A0DB8_S_func_819A0DB8_0 *object = object_data;

    phase_index = (s16)(object->unk_3A - 3);
    (*(s16 *)D_800261B0) = 1;
    switch (phase_index) {
    case 3:
    case 7:
        object->unk_92 -= 0x60;
        object->unk_9E -= 0x60;
        object->unk_93 += 0x20;
        object->unk_9F += 0x20;
        break;
    case 4:
    case 6:
    case 8:
    case 9:
        object->unk_92 += 0x20;
        object->unk_9E += 0x20;
        object->unk_8C -= 1;
        object->unk_98 += 1;
        break;
    case 2:
        object->unk_95 = 24;
        do {
            object->unk_A1 = 24;
        } while (0);
        pair_offset = -12;
        object->unk_8D = pair_offset;
        object->unk_99 = pair_offset;
        object->unk_92 += 0x20;
        object->unk_9E += 0x20;
        break;
    case 0:
        object->unk_95 = 16;
        do {
            object->unk_A1 = 16;
        } while (0);
        pair_offset = -8;
        object->unk_8D = pair_offset;
        object->unk_99 = pair_offset;
    case 1:
    case 5:
    case 10:
        object->unk_92 += 0x20;
        object->unk_9E += 0x20;
        break;
    }
    {
        u16 remaining_steps = object->unk_3A - 1;
        object->unk_3A = remaining_steps;
        if ((s16)remaining_steps <= 0) {
            *(u16 *)((u8 *)object - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }
}
