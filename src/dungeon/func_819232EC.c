#include "modules/dungeon_ovl_7e6e1800.h"

void create_positioned_render_effect(Row_819232EC_S_80024AEC_1 *source, Rec_func_800247B8_arg1 *position, void *unused_sprite) {
    Row_819232EC_S_80024AEC_3 *render_state;
    void *effect;
    Row_819232EC_S_80024AEC_0 *effect_state;
    Row_819232EC_S_80024AEC_4 *effect_position;

    effect = func_8003FC64(0x12);
    effect_state = effect + 0x20;
    if (effect != NULL) {
        effect_state->unk_5A = 0x3C;
        effect_state->unk_5C = 0x3C;
        effect_state->unk_88 = (s32) source->unk_88;
        ((Row_819232EC_S_80024AEC_2 *)effect)->unk_10 = &D_800249FC;
        func_8004491C(effect, func_80045340);
        render_state = ((Row_819232EC_S_80024AEC_2 *)effect)->unk_0C;
        render_state->unk_10 = 0x40;
        render_state->unk_06 = 0xA;
        render_state->unk_14 = (u16) (render_state->unk_14 | 0xC);
        effect_position = ((Row_819232EC_S_80024AEC_2 *)effect)->unk_08;
        effect_position->unk_02 = (u16) position->unk_02;
        effect_position->unk_06 = (u16) position->unk_06;
        effect_position->unk_0A = (u16) position->unk_0A;
        render_state = ((Row_819232EC_S_80024AEC_2 *)effect)->unk_0C;
        render_state->unk_0E = 0x50;
        render_state->unk_0D = 0x50;
        render_state->unk_0C = 0x50;
        render_state->unk_1E = 0;
        render_state->unk_1C = 0;
        *(Row_819232EC_U12 *)((u8 *)effect + 0x96) = *(Row_819232EC_U12 *)&D_80025B48;
        render_state->unk_08 = (void *) (effect + 0x96);
    }
}
