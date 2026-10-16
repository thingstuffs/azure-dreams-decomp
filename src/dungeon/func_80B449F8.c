#include "modules/dungeon_resource12_slot0.h"

void func_801721F8(R12_801721F8_S_801724A8_0 *state, s32 context, s32 source, s32 target) {
    if (func_800AB1C0(state, context, source, target) != 0) {
        func_800AD594(target, 4);
        func_800A4ACC(target);
        if ((func_800AD9B4(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = ((void *)func_80170E70);
        state->unk_90.at00.v = 0;
    }
    if (dungeonStatus.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}
