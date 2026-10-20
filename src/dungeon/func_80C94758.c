#include "modules/dungeon_ovl_cb3000.h"

void func_80171F58(CB_80171F58_S_80171F58_0 *state, void *unused_position, CB_80171F58_S_80171F58_1 *render_state, CB_80171F58_S_80171F58_2 *entity) {
    state->action = 0x10;
    state->action_tick = 0;
    render_state->unk_2C = D_801752C4;
    select_sprite_entry(render_state, *((((s32) (g_game_work.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7) + D_801752C4), 0);
}
