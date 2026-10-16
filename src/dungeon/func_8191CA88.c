#include "modules/dungeon_ovl_193c848.h"

void func_80024288(void *object, Row_8191CA88_S_8191CA88_3 *motion, Row_8191CA88_S_8191CA88_2 *effect) {
    s32 state;
    u16 state_unsigned;
    s32 timer;
    u16 old_timer;
    s32 move_timer;
    s32 move_duration;
    s32 moving;
    s32 signed_timer;
    s32 wait_duration;
    s32 waiting;
    u8 *global_base;
    s32 x_position;
    s32 x_velocity;
    s16 next_state;
    s32 y_velocity;
    s32 z_velocity;
    u16 phase;
    Row_8191CA88_S_8191CA88_1 *inner;

    inner = ((Row_8191CA88_S_8191CA88_0 *)object)->unk_00;
    inner->unk_14 = inner->unk_14 + 1;
    phase = effect->unk_1A;
    effect->unk_1A = phase + 0x300;
    old_timer = ((Row_8191CA88_S_8191CA88_0 *)object)->unk_10.s;
    state = ((Row_8191CA88_S_8191CA88_0 *)object)->unk_0E.s;
    state_unsigned = ((Row_8191CA88_S_8191CA88_0 *)object)->unk_0E.u;
    timer = old_timer + 1;
    ((Row_8191CA88_S_8191CA88_0 *)object)->unk_10.u = timer;

    switch (state) {
    case 0:
        x_position = motion->unk_00;
        x_velocity = motion->unk_0C;
        y_velocity = motion->unk_10;
        z_velocity = motion->unk_14;
        motion->unk_00 = x_position + x_velocity;
        motion->unk_04 += y_velocity;
        motion->unk_08 += z_velocity;
        move_timer = ((Row_8191CA88_S_8191CA88_0 *)object)->unk_10.p;
        move_duration = ((Row_8191CA88_S_8191CA88_0 *)object)->unk_14;
        if (move_timer < move_duration)
            return;
        next_state = ((Row_8191CA88_S_8191CA88_0 *)object)->unk_0E.p + 1;
        ((Row_8191CA88_S_8191CA88_0 *)object)->unk_10.u = 0;
        ((Row_8191CA88_S_8191CA88_0 *)object)->unk_0E.p = next_state;
        return;

    case 1:
        signed_timer = timer << 16;
        wait_duration = ((Row_8191CA88_S_8191CA88_0 *)object)->unk_16;
        signed_timer >>= 16;
        waiting = signed_timer < wait_duration;
        if (waiting != 0) {
            return;
        }
        ((Row_8191CA88_S_8191CA88_0 *)object)->unk_0E.s = state_unsigned + 1;
        ((Row_8191CA88_S_8191CA88_0 *)object)->unk_10.u = 0;
        return;

    case 2:
        motion->unk_08 -= timer << 16;
        if (((Row_8191CA88_S_8191CA88_0 *)object)->unk_10.p < 0x18) {
            return;
        }
        next_state = ((Row_8191CA88_S_8191CA88_0 *)object)->unk_0E.p + 1;
        ((Row_8191CA88_S_8191CA88_0 *)object)->unk_10.u = 0;
        ((Row_8191CA88_S_8191CA88_0 *)object)->unk_0E.p = next_state;
        return;

    case 3:
        ((Row_8191CA88_S_8191CA88_0_pre *)object)[-1].unk_00 |= 0x8000;
        global_base = (u8 *)0x80080000;
        ((Row_8191CA88_S_8191CA88_4 *)global_base)->unk_14A0 |= 0x8000;

        return;
    default:
        return;
    }
}
