#include "modules/dungeon_ovl_188898c.h"

void createRandomizedGrayscaleEffect(s32 user_data, ovl_188898c_81868A64_S_81868A64_3 *source_pos, u8 intensity) {
    ovl_188898c_81868A64_S_81868A64_1 *render_state;
    ovl_188898c_81868A64_S_81868A64_2 *effect_pos;
    ovl_188898c_81868A64_S_81868A64_0 *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        render_state = effect->unk_0C;
        effect->unk_10 = (void *)advanceFadingEffect;
        effect->unk_20 = user_data;
        render_state->unk_0E = intensity;
        render_state->unk_0D = intensity;
        render_state->unk_0C = intensity;
        func_8003DB94(render_state, &D_800DEDB0, 0);
        render_state->unk_1E = 0x1800;
        render_state->unk_1C = 0x1800;
        render_state->unk_12 = 0x7E0B;
        render_state->unk_10 = (u16) (render_state->unk_10 | 0x60);
        render_state->unk_14 = (u16) (render_state->unk_14 | 0x10C);
        func_8004491C(effect, func_80045340);
        effect_pos = effect->unk_08;
        effect_pos->unk_02 = (u16) source_pos->unk_02;
        effect_pos->unk_06 = (u16) source_pos->unk_06;
        effect_pos->unk_0A = (s16) ((source_pos->unk_0A + (rand() % 17)) - 8);
    }
}
