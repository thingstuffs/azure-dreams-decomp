#include "modules/dungeon_ovl_1829800.h"

void dungeonSetNegatedCoordinateScratch(s32 call_value, s32 call_option, s16 call_mode, s32 call_extra)
{
    s16 *scratch = (s16 *)0x1F800000;
    GameWork *g = &gameWork;

    scratch[0x104 / 2] = 0;
    scratch[0x100 / 2] = -((u16)g->view.unk_0AC);
    scratch[0x102 / 2] = -((u16)g->view.unk_0AE);
    func_800BC4D4(call_value, call_option, call_mode, call_extra);
}

