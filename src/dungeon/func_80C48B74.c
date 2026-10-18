/* Relink of matched dungeon/func_80C42B74; every changed retail word is a paired relocation. */
#define update_orbit_height_and_fade_effect D_8016E1A0
#include "modules/dungeon_ovl_7f511800_p04.h"
extern s32 rand(void);
extern s32 func_800644B8(s32);

/* Creates a yellow effect at an angular offset from the supplied position. */
void func_8016E374(void *unused_context, Rec_func_80173CFC_arg1 *origin, s32 unused_param_2, s32 unused_param_3,
    s16 angle, u16 height_offset) {
    void *effect;
    T_80174374_S_80174374_0 *effect_state;
    void *sprite;
    void *position;
    s16 wrapped_angle;

    effect = func_8003FC64(0x212);
    wrapped_angle = angle;
    if (effect != 0) {
        effect_state = (u8 *)effect + 0x20;
        effect_state->unk_1A = 0x14;
        effect_state->unk_1E = angle;
        ((T_80174374_S_80174374_1 *)effect)->unk_10 = &update_orbit_height_and_fade_effect;
        func_8004491C(effect, func_80045340);

        sprite = ((T_80174374_S_80174374_1 *)effect)->unk_0C;
        ((T_80174374_S_80174374_2 *)sprite)->unk_10 = 0x20;
        ((T_80174374_S_80174374_2 *)sprite)->unk_14 |= 0xC;

        position = ((T_80174374_S_80174374_1 *)effect)->unk_08;
        effect_state->unk_40 = origin->unk_00.at00_s32.v;
        effect_state->unk_44 = origin->unk_04.at00_s32.v;

        while (wrapped_angle >= 0x1001) {
            wrapped_angle -= 0x1000;
        }

        ((T_80174374_S_80174374_4 *)position)->unk_00 = effect_state->unk_40 + func_80064584(wrapped_angle) * 0x280;
        ((T_80174374_S_80174374_4 *)position)->unk_04 = effect_state->unk_44 + func_800644B8(wrapped_angle) * 0x280;
        ((T_80174374_S_80174374_4 *)position)->unk_0A = origin->unk_0A + height_offset;

        sprite = ((T_80174374_S_80174374_1 *)effect)->unk_0C;
        ((T_80174374_S_80174374_2 *)sprite)->unk_1E = 0x400;
        ((T_80174374_S_80174374_2 *)sprite)->unk_1C = 0x400;
        ((T_80174374_S_80174374_2 *)sprite)->unk_0E = 0x60;
        ((T_80174374_S_80174374_2 *)sprite)->unk_0D = 0xFF;
        ((T_80174374_S_80174374_2 *)sprite)->unk_0C = 0xFF;
        effect_state->unk_00 = 0xFF;
        effect_state->unk_01 = ((T_80174374_S_80174374_2 *)sprite)->unk_0D;
        effect_state->unk_02 = ((T_80174374_S_80174374_2 *)sprite)->unk_0E;

        func_8003DB94(sprite, &D_800DEC00, rand() & 1);
        ((T_80174374_S_80174374_2 *)sprite)->unk_12 = 0x7DCF;
        ((T_80174374_S_80174374_2 *)sprite)->unk_14 |= 0x100;
    }
}
