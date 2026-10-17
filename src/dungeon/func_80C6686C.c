/* Relink of matched dungeon/func_80C4286C; every changed retail word is a paired relocation. */
#define advanceRecordStateAndSetCompletionFlags D_8014FFF4
#include "modules/dungeon_ovl_7f511800_p04.h"
extern s32 rand(void);

/* Create a tinted sprite effect at the supplied position with a random variant. */
void func_8015006C(void *unused, void *position_data, void *unused_primitive) {
    T_8017406C_S_8017406C_0 *effect_state;
    T_8017406C_S_8017406C_2 *sprite;
    void *effect;
    T_8017406C_S_8017406C_3 *source_pos = position_data;
    T_8017406C_S_8017406C_4 *effect_pos;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        effect_state = effect + 0x20;
        effect_state->unk_1A = 0xF;
        ((T_8017406C_S_8017406C_1 *)effect)->unk_10 = &advanceRecordStateAndSetCompletionFlags;
        func_8004491C(effect, func_80045340);
        sprite = ((T_8017406C_S_8017406C_1 *)effect)->unk_0C;
        sprite->unk_10 = 0x20;
        sprite->unk_14 = (u16)(sprite->unk_14 | 0xC);
        effect_pos = ((T_8017406C_S_8017406C_1 *)effect)->unk_08;
        effect_state->unk_40 = (s32)source_pos->unk_00.at00.v;
        effect_state->unk_44 = (s32)source_pos->unk_04.at00.v;
        effect_pos->unk_02 = (u16)source_pos->unk_00.at02.v;
        effect_pos->unk_06 = (u16)source_pos->unk_04.at02.v;
        effect_pos->unk_0A = (u16)source_pos->unk_0A;
        sprite = ((T_8017406C_S_8017406C_1 *)effect)->unk_0C;
        sprite->unk_1E = 0x800;
        sprite->unk_1C = 0x800;
        sprite->unk_0E = 0x60U;
        sprite->unk_0D = 0xFFU;
        sprite->unk_0C = 0xFFU;
        ((T_8017406C_S_8017406C_1 *)effect)->unk_20 = 0xFFU;
        effect_state->unk_01 = (u8)sprite->unk_0D;
        effect_state->unk_02 = (u8)sprite->unk_0E;
        func_8003DB94(sprite, &D_800DEC70, rand() & 1);
        sprite->unk_12 = 0x7DCF;
        sprite->unk_14 = (u16)(sprite->unk_14 | 0x100);
    }
}
