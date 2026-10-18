#include "modules/dungeon_ovl_1936800.h"

void *create_an_oriented_effect_between_position_owner(void *owner, Rec_func_80024E80_arg1 *start_pos) {
    void *effect;
    Row_81917680_S_80024E80_2 *state;
    Row_81917680_S_80024E80_3 *render;
    Row_81917680_S_80024E80_4 *endpoints;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 slot_index;
    u8 *slot_ptr;
    s32 random_angle;

    effect = func_8003FD64(0x212, (u8 *)owner - 0x20);
    if (effect != 0) {
        ((Row_81917680_S_80024E80_0 *)effect)->unk_10 = D_80024C0C;
        state = (u8 *)effect + 0x20;
        ((Row_81917680_S_80024E80_0 *)effect)->unk_20 = ((Row_81917680_S_80024E80_1 *)owner)->unk_00;
        state->unk_04 = 0;

        render = ((Row_81917680_S_80024E80_0 *)effect)->unk_0C;
        render->unk_0E = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;
        render->unk_12 = 0x7DCF;
        render->unk_08 = D_800DE39C;
        render->unk_14 |= 0x100;

        random_angle = rand();
        render->unk_1A = random_angle % 0x1000;
        render->unk_1E = 0x400;
        render->unk_1C = 0x400;

        func_8004491C(effect, func_80045340);

        endpoints = ((Row_81917680_S_80024E80_0 *)effect)->unk_08;
        *(Row_81917680_SixWords *)endpoints = *(Row_81917680_SixWords *)start_pos;
        endpoints->unk_0C = ((Row_81917680_S_80024E80_1 *)owner)->unk_20;
        endpoints->unk_10 = ((Row_81917680_S_80024E80_1 *)owner)->unk_24;
        endpoints->unk_14 = ((Row_81917680_S_80024E80_1 *)owner)->unk_28;

        dx = ((Row_81917680_S_80024E80_1 *)owner)->unk_20 - start_pos->unk_00.at00_s32.v;
        dy = ((Row_81917680_S_80024E80_1 *)owner)->unk_24 - start_pos->unk_04.at00_s32.v;
        dz = ((Row_81917680_S_80024E80_1 *)owner)->unk_28 - start_pos->unk_08.at00_s32.v;

        state->unk_0E = func_80065F90(
            func_800647A0((((dx >> 12) * (dx >> 12)) +
                           ((dy >> 12) * (dy >> 12))) << 4),
            dz >> 4);
        state->unk_10 = func_80065F90(dx >> 4, dy >> 4);

        if (dx < 0) {
            state->unk_12 = 1;
        }

        slot_index = 0;
        slot_ptr = state;
        do {
            ((Row_81917680_S_80024E80_6 *)slot_ptr)->unk_14 = create_radial_effect_from_source(state, endpoints, (s16)slot_index);
            slot_index++;
            slot_ptr += 4;
        } while (slot_index < 3);

        return effect;
    }
    return 0;
}
