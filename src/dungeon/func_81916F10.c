#include "modules/dungeon_ovl_1936800.h"

void func_80024710(Row_81916F10_S_80024710_0 *object, Row_81916F10_S_80024710_2 *position) {
    s32 angle_scale_x;
    s32 angle_scale_y;
    Row_81916F10_S_80024710_1 *state;

    state = object->unk_00;
    state->unk_14 = (u16) (state->unk_14 + 1);
    angle_scale_x = func_800644B8(object->unk_0E);
    position->unk_00 = (s32) (position->unk_00 + ((angle_scale_x >> 4) * (func_800644B8(object->unk_10) >> 4) * 0x1C));
    angle_scale_y = func_800644B8(object->unk_0E);
    position->unk_04 = (s32) (position->unk_04 + ((angle_scale_y >> 4) * (func_80064584(object->unk_10) >> 4) * 0x1C));
    position->unk_08 = (s32) (position->unk_08 + ((func_80064584(object->unk_0E) >> 4) * 0x1C00));
}
