#include "modules/dungeon_ovl_188298c.h"

void advance_fading_effect(ovl_188298c_8186298C_Arg0Ent *state, void *unused, ovl_188298c_8186298C_Arg2Ent *effect)
{
    u16 size;
    u8 brightness;

    state->unk00->unk14++;
    size = effect->unk1E + 0x400;
    brightness = effect->unk0E - 4;
    effect->unk1E = size;
    effect->unk1C = size;
    effect->unk0E = brightness;
    effect->unk0D = brightness;
    effect->unk0C = brightness;
    func_800478B8(effect);

    if (effect->unk14 & 0x6000) {
        if (state->unk04 != 0) {
            *(u16 *)((u8 *)state - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
            return;
        } else {
            func_8003DB94(effect, D_800DEDB0, 4);
            state->unk04 = 1;
        }
    }
}
