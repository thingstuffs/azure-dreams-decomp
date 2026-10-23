#include "shared/sprite_frame_state.h"
#include "dungeon/monster/noise/settle_actor_after_movement.h"
#include "shared/sprite_frame_state.h"

/*
 * Sets action state 0x10, clears its tick, sets field 0x9E to two, and selects a camera-relative
 * eight-way entry from D_80174EA0.
 */
void settle_actor_after_movement(T_80172664_State *state, s32 unused, SpriteFrameState *context, T_80172664_IndexSource *source)
{
    state->unk9A = 0x10;
    state->unk9B = 0;
    state->unk9E = 2;
    context->frameTable = D_80174EA0;
    select_sprite_entry(context, D_80174EA0[((g_game_work.view.camera_rotation.parts.viewAngle + source->unk2A + 0x100) >> 9) & 7], 0);
}
