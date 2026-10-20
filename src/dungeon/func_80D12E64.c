#include "dungeon/monster/noise/settle_actor_after_movement.h"

void settle_actor_after_movement(T_80172664_State *state, s32 unused, T_80172664_Context *context, T_80172664_IndexSource *source)
{
    state->unk9A = 0x10;
    state->unk9B = 0;
    state->unk9E = 2;
    context->unk2C = D_80174EA0;
    select_sprite_entry(context, D_80174EA0[((g_game_work.view.viewAngle + source->unk2A + 0x100) >> 9) & 7], 0);
}
