#include "modules/dungeon_ovl_18d0850.h"

void advance_height_offset_and_placement(ovl_18d0850_818B0AE0_S_800242E0_0 *state, ovl_18d0850_818B0AE0_S_800242E0_2 *position, Rec_D_80082E80 *object) {
    s32 angle;
    u16 height_offset;
    ovl_18d0850_818B0AE0_S_800242E0_1 *counter;

    counter = state->unk_00;
    counter->unk_14 = (u16)(counter->unk_14 + 1);
    height_offset = state->unk_04 + state->unk_06;
    state->unk_04 = height_offset;
    if ((s16)height_offset < -0x80) {
        angle = rand() % 0x1000;
        position->unk_02 = (s16)(state->unk_08 + ((func_800644B8(angle) * 2) >> 8));
        position->unk_06 = (s16)(state->unk_0A + ((func_80064584(angle) * 2) >> 8));
        state->unk_04 = (u16)(state->unk_04 + 0x80);
        state->unk_06 = (u16)(-6 - (rand() % 5));
    }
    position->unk_0A = (s16)(state->unk_0C + state->unk_04);
    func_800478B8(object);
    if (object->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94(object, D_800DEC70, 0);
    }
}
