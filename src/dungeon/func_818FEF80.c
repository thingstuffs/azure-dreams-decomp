#include "modules/dungeon_ovl_191eef8.h"

void func_80024780(void *state, void *position, void *visual) {
    void *object;
    void *linked_visual;
    s16 ticks_left;

    object = ((Row_818FEF80_S_818FEF80_0 *)state)->unk_30;
    (*(s16 *)D_80025E80) = 1;
    if ((u32)(((Row_818FEF80_S_818FEF80_1 *)object)->unk_13 - 0x33) < 4U) {
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }

    ((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.s--;
    if (((Row_818FEF80_S_818FEF80_0 *)state)->unk_0A.s == 0) {
        ((Row_818FEF80_S_818FEF80_0 *)state)->unk_0A.u = 1;
        ((Row_818FEF80_S_818FEF80_2 *)position)->unk_08.u += -0x20000;
    } else {
        ((Row_818FEF80_S_818FEF80_0 *)state)->unk_0A.s = 0;
        ((Row_818FEF80_S_818FEF80_2 *)position)->unk_08.u += 0x20000;
    }
    object = ((Row_818FEF80_S_818FEF80_0 *)state)->unk_30;
    linked_visual = ((Row_818FEF80_S_818FEF80_1_pre *)object)[-1].unk_00;
    ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_14 &= 0xFF7F;
    ((Row_818FEF80_S_818FEF80_4 *)linked_visual)->unk_14 |= 0x80;

    ticks_left = ((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u;
    if (ticks_left < 0x3C) {
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0E = (((0x3C - ticks_left) << 6) / 60) + 0x40;
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0D = (((0x3C - ((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u) << 6) / 60) + 0x40;
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0C = (((0x3C - ((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u) << 6) / 60) + 0x40;
    } else {
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0E = (((ticks_left - 0x3C) << 6) / 60) + 0x40;
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0D = (((((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u - 0x3C) << 6) / 60) + 0x40;
        ((Row_818FEF80_S_818FEF80_3 *)visual)->unk_0C = (((((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u - 0x3C) << 6) / 60) + 0x40;
    }

    if (((Row_818FEF80_S_818FEF80_0 *)state)->unk_02.u <= 0) {
        u16 linked_flags;

        ((Row_818FEF80_S_818FEF80_0_pre *)state)[-1].unk_00 |= 0x8000;
        linked_flags = ((Row_818FEF80_S_818FEF80_4 *)linked_visual)->unk_14;
        objectFlagBlock.flags |= 0x8000;
        ((Row_818FEF80_S_818FEF80_4 *)linked_visual)->unk_14 = linked_flags & 0xFF7F;
    }
}
