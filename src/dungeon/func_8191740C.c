#include "modules/dungeon_ovl_1936800.h"

void advance_radial_effect_state(void *motion, void *position, void *effect) {
    s32 direction_scale;
    s32 sin_a;
    s32 sin_b;
    s32 sin_c;
    s32 target_x;
    s32 current_x;
    s32 next_x;
    s32 next_distance;
    s16 past_target;
    u16 size;
    u8 intensity;
    void *object;
    ObjectFlagBlock *global_flags;
    s16 state;

    object = ((Row_8191740C_S_80024C0C_0 *)motion)->unk_00;
    ((Row_8191740C_S_80024C0C_1 *)object)->unk_14++;
    state = ((Row_8191740C_S_80024C0C_0 *)motion)->unk_04.s;
    switch (state) {
    case 0:
        ((Rec_D_80082E80 *)effect)->unk_1A.as_u16 += 0x200;
        sin_a = func_800644B8(((Row_8191740C_S_80024C0C_0 *)motion)->unk_0E);
        direction_scale = (sin_a >> 4) * (func_800644B8(((Row_8191740C_S_80024C0C_0 *)motion)->unk_10) >> 4);
        ((Rec_func_80024600_arg1 *)position)->unk_00 += direction_scale * 0x1C;
        sin_b = func_800644B8(((Row_8191740C_S_80024C0C_0 *)motion)->unk_0E);
        direction_scale = (sin_b >> 4) * (func_80064584(((Row_8191740C_S_80024C0C_0 *)motion)->unk_10) >> 4);
        ((Rec_func_80024600_arg1 *)position)->unk_04 += direction_scale * 0x1C;
        ((Rec_func_80024600_arg1 *)position)->unk_08 += (func_80064584(((Row_8191740C_S_80024C0C_0 *)motion)->unk_0E) >> 4) * 0x1C00;
        sin_c = func_800644B8(((Row_8191740C_S_80024C0C_0 *)motion)->unk_0E);
        direction_scale = (sin_c >> 4) * (func_800644B8(((Row_8191740C_S_80024C0C_0 *)motion)->unk_10) >> 4);
        current_x = ((Rec_func_80024600_arg1 *)position)->unk_00;
        state = ((Row_8191740C_S_80024C0C_0 *)motion)->unk_12;
        next_x = current_x + direction_scale * 0x1C;
        if (state != 0) {
            target_x = ((Rec_func_80024600_arg1 *)position)->unk_0C;
            past_target = target_x < current_x;
        } else {
            target_x = ((Rec_func_80024600_arg1 *)position)->unk_0C;
            past_target = current_x < target_x;
        }
        if (past_target) {
            s32 distance;

            distance = current_x - target_x;
            distance = abs(distance);
            next_distance = next_x - target_x;
            next_distance = abs(next_distance);
            if (next_distance < distance) {
                return;
            }
        }
        initialize_the_s_visual_state_apply_random_spherical_position_offset(motion, position, effect);
        ((Row_8191740C_S_80024C0C_0 *)motion)->unk_04.u++;
        break;
    case 1:
        if (((Rec_D_80082E80 *)effect)->unk_0C.at00_u8.v != 0) {
            intensity = ((Rec_D_80082E80 *)effect)->unk_0C.at02_u8.v - 0x20;
            ((Rec_D_80082E80 *)effect)->unk_0C.at02_u8.v = intensity;
            ((Rec_D_80082E80 *)effect)->unk_0C.at01_u8.v = intensity;
            ((Rec_D_80082E80 *)effect)->unk_0C.at00_u8.v = intensity;
        }
        size = ((Rec_D_80082E80 *)effect)->unk_1C.at02_u16.v + 0x400;
        ((Rec_D_80082E80 *)effect)->unk_1C.at02_u16.v = size;
        ((Rec_D_80082E80 *)effect)->unk_1C.at00_u16.v = size;
        func_800478B8(effect);
        func_800478B8(effect);
        if (((Rec_D_80082E80 *)effect)->unk_14.at00_u16.v & 0x6000) {
            object = ((Row_8191740C_S_80024C0C_0 *)motion)->unk_00;
            ((Row_8191740C_S_80024C0C_1 *)object)->unk_16++;
            global_flags = &object_flag_block;
            (*(u16 *)((u8 *)motion + (-2))) |= 0x8000;
            global_flags->flags |= 0x8000;
        }
        break;
    }
}
