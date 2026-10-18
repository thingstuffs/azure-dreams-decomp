#include "modules/dungeon_ovl_cc5000.h"

void func_8015FF58(CL_CC5000_80171F58_S_80171F58_0 *state, void *unused_position, CL_CC5000_80171F58_S_80171F58_1 *render_state, CL_CC5000_80171F58_S_80171F58_2 *entity) {
    state->action = 0x10;
    state->action_tick = 0;
    render_state->unk_2C = D_801632C4;
    func_80047784(render_state, *((((s32) (g_game_work.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7) + D_801632C4), 0);
}
