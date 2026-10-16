#include "modules/dungeon_ovl_7e6e1800.h"

void func_80024D34(void *unused, Rec_func_800247B8_arg1 *origin, void *unused_sprite)
{
    s32 flags;
    Row_81923534_S_80024D34_2 *render_control;
    Row_81923534_S_80024D34_5 *render_style;
    Row_81923534_S_80024D34_3 *position;
    void *effect;
    Row_81923534_S_80024D34_0 *effect_data;
    s32 random_value;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        effect_data = (u8 *)effect + 0x20;
        effect_data->unk_5A = 0xE;
        effect_data->unk_5C = 0xE;
        ((Row_81923534_S_80024D34_1 *)effect)->unk_10 = D_80024C0C;
        func_8004491C(effect, func_80045340);

        render_control = ((Row_81923534_S_80024D34_1 *)effect)->unk_0C;
        render_control->unk_14 |= 0xC;
        render_control->unk_10 = 0x60;
        render_control->unk_14 |= 2;

        position = ((Row_81923534_S_80024D34_1 *)effect)->unk_08;
        random_value = rand();
        position->unk_02 = origin->unk_02 + ((random_value & 0x1F) - 0x10);
        random_value = rand();
        position->unk_06 = origin->unk_06 + ((random_value & 0x1F) - 0x10);
        random_value = rand();
        position->unk_0A = origin->unk_0A + ((random_value & 0x1F) - 0x10);

        render_style = ((Row_81923534_S_80024D34_1 *)effect)->unk_0C;
        render_style->unk_1E = 0xC00;
        render_style->unk_1C = 0xC00;
        render_style->unk_0E = 0x80;
        render_style->unk_0D = 0x80;
        render_style->unk_0C = 0x80;
        render_style->unk_12 = 0x7DCF;
        render_style->unk_14 = render_style->unk_14 | 0x100;
        func_8003DB94(render_style, D_800DE870, 0);
    }
}

/* MECHANISM: Preserve the seed's exact 0x20 frame, s2/s1/s0 holds, and CFG.
   Unsigned byte fields keep the shared 0x80 store value as +128, matching
   retail's addiu before the three sb operations. */
