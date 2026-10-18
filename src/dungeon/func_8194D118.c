#include "modules/dungeon_ovl_7e6b7800.h"

void advance_object_motion_and_animation(void *object) {
    s16 next_tick;
    s32 velocity_y;
    s32 velocity_z;
    s32 position_y;
    void *state;

    state = ((Row_8194D118_S_80024918_0 *)object)->unk_00;
    ((Row_8194D118_S_80024918_1 *)state)->unk_1A = ((Row_8194D118_S_80024918_1 *)state)->unk_1A + 1;
    ((Row_8194D118_S_80024918_0 *)object)->unk_78 = ((u32)func_800644B8(((Row_8194D118_S_80024918_0 *)object)->unk_74 << 8)) >> 6;
    velocity_y = ((Row_8194D118_S_80024918_0 *)object)->unk_44;
    ((Row_8194D118_S_80024918_0 *)object)->unk_34 += ((Row_8194D118_S_80024918_0 *)object)->unk_40;
    position_y = ((Row_8194D118_S_80024918_0 *)object)->unk_38;
    velocity_z = ((Row_8194D118_S_80024918_0 *)object)->unk_48;
    ((Row_8194D118_S_80024918_0 *)object)->unk_38 = position_y + velocity_y;
    ((Row_8194D118_S_80024918_0 *)object)->unk_3C += velocity_z;
    create_textured_offset_object(object);
    next_tick = (s16)((Row_8194D118_S_80024918_0 *)object)->unk_74 + 1;
    ((Row_8194D118_S_80024918_0 *)object)->unk_74 = next_tick;
    if (next_tick >= 9) {
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
