#include "modules/dungeon_ovl_9950e8.h"

void createDirectionalTemplateEffect(void *unused, S_80975244_5 *source_pos, void *sprite_template, S_80975244_3 *facing_source) {
    S_80975244_2 *sprite;
    void *effect;
    S_80975244_0 *effect_state;
    S_80975244_4 *effect_pos;
    void *template_data;
    Block16 *src;
    Block16 *dst;
    Block16 *end;

    effect = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    template_data = sprite_template;
    if (effect != NULL) {
        effect_state = effect + 0x20;
        effect_state->unk_96 = 7;
        effect_state->unk_AA = 7;
        ((S_80975244_1 *)effect)->unk_10 = advanceAndFadeTransformedEffect;
        effect_state->unk_B0 = source_pos;
        sprite = ((S_80975244_1 *)effect)->unk_0C;
        src = (Block16 *)template_data;
        dst = (Block16 *)sprite;
        end = src + 3;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0x50;
        sprite->unk_0D = 0x50;
        sprite->unk_0C = 0x50;
        sprite->unk_10 = 0x20;
        sprite->unk_12 = 0xFF80;
        sprite->unk_22 = 0xFFF1;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        func_8004491C(effect, func_80045340);
        sprite->unk_2C = &D_80174128;
        func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + facing_source->unk_2A + 0x100) >> 9) & 7)
            + D_80174128), 0);
        effect_pos = ((S_80975244_1 *)effect)->unk_08;
        effect_pos->unk_02 = (u16) source_pos->unk_02;
        effect_pos->unk_06 = (u16) source_pos->unk_06;
        effect_pos->unk_0A = (u16) source_pos->unk_0A;
    }
}
