#include "modules/dungeon_ovl_7e6e1800.h"

void create_randomized_radial_effect(Rec_func_800247B8_arg0 *source, Rec_func_800247B8_arg1 *origin, void *unused_sprite)
{
    s32 elevation;
    s32 planar_radius;
    s32 azimuth;
    s32 random_value;
    void *effect;
    Row_81922FB8_S_800247B8_0 *state;
    Row_81922FB8_S_800247B8_2 *sprite;
    Row_81922FB8_S_800247B8_4 *position;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        state = effect + 0x20;
        state->unk_5A = 10;
        state->unk_5C = 10;
        random_value = project_and_queue_visible_shaded_quad(8);
        state->unk_18.at00.v = 0x303030;
        if (random_value & 1) {
            state->unk_18.at00u.v = 0x90;
        }
        if (random_value & 2) {
            state->unk_18.at01.v = 0x90;
        }
        if (random_value & 4) {
            state->unk_18.at02.v = 0x90;
        }
        state->unk_10 = 0;
        state->unk_14 = 0;
        state->unk_1C = state->unk_18.at00.v;
        ((Row_81922FB8_S_800247B8_1 *)effect)->unk_20 = state->unk_10;
        state->unk_04 = state->unk_14;
        state->unk_08 = state->unk_18.at00.v;
        state->unk_0C = state->unk_1C;
        ((Row_81922FB8_S_800247B8_1 *)effect)->unk_10 = D_800246C4;
        func_8004491C(effect, D_80024670);

        sprite = ((Row_81922FB8_S_800247B8_1 *)effect)->unk_0C;
        sprite->unk_10 = 0x20;
        sprite->unk_14 |= 0xC;
        elevation = rand() & 0xFFF;
        planar_radius = (source->unk_56 * func_80064584(elevation)) >> 12;
        state->unk_24.s = (source->unk_56 * func_800644B8(elevation)) >> 12;
        azimuth = rand() & 0xFFF;
        state->unk_20.s = ((s16)planar_radius * func_80064584(azimuth)) >> 12;
        state->unk_22.s = ((s16)planar_radius * func_800644B8(azimuth)) >> 12;

        state->unk_26 = state->unk_20.u + project_and_queue_visible_shaded_quad(0x10) - 8;
        state->unk_28 = state->unk_22.u + project_and_queue_visible_shaded_quad(0x10) - 8;
        random_value = project_and_queue_visible_shaded_quad(0x10);
        state->unk_36 = 0;
        state->unk_34 = 0;
        state->unk_32 = 0;
        state->unk_30 = 0;
        state->unk_2E = 0;
        state->unk_2C = 0;
        state->unk_2A = state->unk_24.u + random_value - 8;

        position = ((Row_81922FB8_S_800247B8_1 *)effect)->unk_08;
        position->unk_02 = origin->unk_02;
        position->unk_06 = origin->unk_06;
        position->unk_0A = origin->unk_0A;

        sprite = ((Row_81922FB8_S_800247B8_1 *)effect)->unk_0C;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
    }
}
