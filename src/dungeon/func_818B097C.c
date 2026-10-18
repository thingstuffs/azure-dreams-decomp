#include "modules/dungeon_ovl_18d0850.h"

void advance_owner_effect_counter(ovl_18d0850_818B097C_EffectOwner *owner, void *unused, ovl_18d0850_818B097C_EffectCounter *state) {
    owner->parent->flags++;
    func_800478B8(state);
    if (state->flags & 0x6000) {
        *(u16 *)((u8 *)owner - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
