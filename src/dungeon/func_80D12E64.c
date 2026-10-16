#include "modules/dungeon_ovl_7f43f800_p04.h"

void func_80172664(T_80172664_State *state, s32 unused, T_80172664_Context *context, T_80172664_IndexSource *source)
{
    state->unk9A = 0x10;
    state->unk9B = 0;
    state->unk9E = 2;
    context->unk2C = D_80174EA0;
    func_80047784(context, D_80174EA0[((gameWork.view.viewAngle + source->unk2A + 0x100) >> 9) & 7], 0);
}
