#include "modules/dungeon_ovl_cb9000.h"

void func_8016BF58(CL_CB9000_80171F58_S_80171F58_0 *state, void *unused_position, CL_CB9000_80171F58_S_80171F58_1 *render_state, CL_CB9000_80171F58_S_80171F58_2 *entity) {
    state->action = 0x10;
    state->action_tick = 0;
    render_state->unk_2C = D_8016F2C4;
    func_80047784(render_state, *((((s32) (gameWork.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7) + D_8016F2C4), 0);
}
